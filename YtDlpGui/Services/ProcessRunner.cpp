#include "pch.h"
#include "ProcessRunner.h"
#include <sstream>
#include <thread>

namespace winrt::YtDlpGui::Services
{
    std::wstring ProcessRunner::QuoteArg(const std::wstring& arg)
    {
        if (arg.empty())
            return L"\"\"";

        std::wstring result = L"\"";
        size_t i = 0;
        while (i < arg.size())
        {
            if (arg[i] == L'\\')
            {
                size_t backslashes = 0;
                while (i < arg.size() && arg[i] == L'\\')
                {
                    ++backslashes;
                    ++i;
                }
                if (i < arg.size() && arg[i] == L'"')
                {
                    result.append(backslashes * 2, L'\\');
                    result += L"\"\"";
                    ++i;
                }
                else
                {
                    result.append(backslashes, L'\\');
                }
            }
            else if (arg[i] == L'"')
            {
                result += L"\"\"";
                ++i;
            }
            else
            {
                result += arg[i];
                ++i;
            }
        }
        result += L"\"";
        return result;
    }

    ProcessRunner::ProcessRunner() {}

    ProcessRunner::~ProcessRunner()
    {
        Cancel();
    }

    void ProcessRunner::WaitForPrevious()
    {
        if (m_hThread)
        {
            WaitForSingleObject(m_hThread, INFINITE);
            CloseHandle(m_hThread);
            m_hThread = nullptr;
        }
        m_state = nullptr;
    }

    void ProcessRunner::Cancel()
    {
        auto state = m_state;
        if (state && !state->Done)
        {
            state->Cancelled = true;
            if (state->hProcess)
                TerminateProcess(state->hProcess, 1);
        }
        WaitForPrevious();
    }

    std::shared_ptr<RunState> ProcessRunner::CreateProcess(const std::wstring& command,
                                                            const std::wstring& args,
                                                            OutputCallback const& outputCb,
                                                            ProgressCallback const& progressCb)
    {
        auto state = std::make_shared<RunState>();
        state->OutputCallback = outputCb;
        state->ProgressCallback = progressCb;

        SECURITY_ATTRIBUTES sa{ sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };
        HANDLE hStdOutWrite = nullptr, hStdErrWrite = nullptr, hStdInRead = nullptr;
        bool success = true;
        success &= CreatePipe(&state->hStdOutRead, &hStdOutWrite, &sa, 0);
        success &= CreatePipe(&state->hStdErrRead, &hStdErrWrite, &sa, 0);
        success &= CreatePipe(&hStdInRead, &state->hStdInWrite, &sa, 0);
        if (!success)
        {
            if (hStdOutWrite) CloseHandle(hStdOutWrite);
            if (hStdErrWrite) CloseHandle(hStdErrWrite);
            if (hStdInRead) CloseHandle(hStdInRead);
            if (state->hStdOutRead) CloseHandle(state->hStdOutRead);
            if (state->hStdErrRead) CloseHandle(state->hStdErrRead);
            if (state->hStdInWrite) CloseHandle(state->hStdInWrite);
            state->hStdOutRead = nullptr;
            state->hStdErrRead = nullptr;
            state->hStdInWrite = nullptr;
            state->Done = true;
            return nullptr;
        }
        SetHandleInformation(state->hStdOutRead, HANDLE_FLAG_INHERIT, 0);
        SetHandleInformation(state->hStdErrRead, HANDLE_FLAG_INHERIT, 0);
        SetHandleInformation(state->hStdInWrite, HANDLE_FLAG_INHERIT, 0);

    std::wstring cmdLine = QuoteArg(command);
    if (!args.empty())
        cmdLine += L" " + args;

    PROCESS_INFORMATION pi{};
    STARTUPINFOW si{ sizeof(STARTUPINFOW) };
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdOutput = hStdOutWrite;
    si.hStdError = hStdErrWrite;
    si.hStdInput = hStdInRead;

    if (!::CreateProcessW(nullptr, cmdLine.data(), nullptr, nullptr, TRUE,
                          CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
    {
        if (hStdOutWrite) CloseHandle(hStdOutWrite);
        if (hStdErrWrite) CloseHandle(hStdErrWrite);
        if (hStdInRead) CloseHandle(hStdInRead);
        state->Done = true;
        return nullptr;
    }

    state->hProcess = pi.hProcess;
    CloseHandle(pi.hThread);
    CloseHandle(hStdOutWrite);
    CloseHandle(hStdErrWrite);
    CloseHandle(hStdInRead);
    return state;
    }

    static void DrainPipe(HANDLE hPipe, OutputCallback const& cb)
    {
        char buffer[4096];
        DWORD bytesRead;
        while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr) && bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            if (cb)
                cb(std::string(buffer, bytesRead));
        }
    }

    ProcessOutput ProcessRunner::RunSync(const std::wstring& command, const std::wstring& args)
    {
        ProcessOutput result;
        WaitForPrevious();

        auto state = CreateProcess(command, args, m_outputCallback, m_progressCallback);
        if (!state)
            return result;

        m_state = state;

        std::thread errThread(DrainPipe, state->hStdErrRead, state->OutputCallback);
        DrainPipe(state->hStdOutRead, state->OutputCallback);
        errThread.join();

        WaitForSingleObject(state->hProcess, INFINITE);
        DWORD exitCode;
        if (!GetExitCodeProcess(state->hProcess, &exitCode))
        {
            exitCode = static_cast<DWORD>(-1);
        }
        result.ExitCode = static_cast<int>(exitCode);

        state->Done = true;
        WaitForPrevious();
        return result;
    }

    void ProcessRunner::RunAsync(const std::wstring& command, const std::wstring& args,
                                  std::function<void(int exitCode)> onComplete)
    {
        WaitForPrevious();

        auto state = CreateProcess(command, args, m_outputCallback, m_progressCallback);
        if (!state)
        {
            if (onComplete) onComplete(-1);
            return;
        }

        state->OnComplete = onComplete;
        m_state = state;

        auto param = new std::shared_ptr<RunState>(state);
        m_hThread = CreateThread(nullptr, 0,
            [](LPVOID param) -> DWORD
            {
                auto state = *reinterpret_cast<std::shared_ptr<RunState>*>(param);
                delete reinterpret_cast<std::shared_ptr<RunState>*>(param);

                std::thread errThread(DrainPipe, state->hStdErrRead, state->OutputCallback);
                DrainPipe(state->hStdOutRead, state->OutputCallback);
                errThread.join();

                if (!state->Cancelled)
                    WaitForSingleObject(state->hProcess, INFINITE);
                DWORD exitCode = 1;
                if (!state->Cancelled)
                    GetExitCodeProcess(state->hProcess, &exitCode);

                state->Done = true;
                if (state->OnComplete)
                    state->OnComplete(static_cast<int>(exitCode));
                return 0;
            },
            param, 0, nullptr);

        if (!m_hThread)
        {
            delete param;
            state->Done = true;
            if (onComplete) onComplete(-1);
        }
    }

    void ProcessRunner::SendInput(const std::string& input)
    {
        auto state = m_state;
        if (state && state->hStdInWrite)
        {
            DWORD written;
            WriteFile(state->hStdInWrite, input.c_str(), static_cast<DWORD>(input.size()), &written, nullptr);
        }
    }
}
