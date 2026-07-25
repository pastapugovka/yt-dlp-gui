#pragma once

#include <string>
#include <functional>
#include <memory>
#include <atomic>
#include <windows.h>
#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::Services
{
    struct ProcessOutput
    {
        int ExitCode{ -1 };
        std::string StdOut;
        std::string StdErr;
    };

    using OutputCallback = std::function<void(const std::string& line)>;
    using ProgressCallback = std::function<void(double percent, const std::string& speed, const std::string& eta)>;

    struct RunState
    {
        HANDLE hProcess{ nullptr };
        HANDLE hStdOutRead{ nullptr };
        HANDLE hStdErrRead{ nullptr };
        HANDLE hStdInWrite{ nullptr };
        std::atomic<bool> Cancelled{ false };
        std::atomic<bool> Done{ false };
        OutputCallback OutputCallback;
        ProgressCallback ProgressCallback;
        std::function<void(int)> OnComplete;

        ~RunState()
        {
            if (hProcess) { CloseHandle(hProcess); hProcess = nullptr; }
            if (hStdOutRead) { CloseHandle(hStdOutRead); hStdOutRead = nullptr; }
            if (hStdErrRead) { CloseHandle(hStdErrRead); hStdErrRead = nullptr; }
            if (hStdInWrite) { CloseHandle(hStdInWrite); hStdInWrite = nullptr; }
        }

        RunState(const RunState&) = delete;
        RunState& operator=(const RunState&) = delete;
        RunState() = default;
    };

    class ProcessRunner
    {
    public:
        ProcessRunner();
        ~ProcessRunner();

        static std::wstring QuoteArg(const std::wstring& arg);

        bool IsRunning() const { return m_state && !m_state->Done; }
        void Cancel();
        void SetOutputCallback(OutputCallback cb) { m_outputCallback = std::move(cb); }
        void SetProgressCallback(ProgressCallback cb) { m_progressCallback = std::move(cb); }

        ProcessOutput RunSync(const std::wstring& command, const std::wstring& args = L"");
        void RunAsync(const std::wstring& command, const std::wstring& args = L"",
                      std::function<void(int exitCode)> onComplete = nullptr);
        void SendInput(const std::string& input);

    private:
        static std::shared_ptr<RunState> CreateProcess(const std::wstring& command,
                                                        const std::wstring& args,
                                                        OutputCallback const& outputCb,
                                                        ProgressCallback const& progressCb);
        void WaitForPrevious();

        OutputCallback m_outputCallback;
        ProgressCallback m_progressCallback;
        std::shared_ptr<RunState> m_state;
        HANDLE m_hThread{ nullptr };
    };
}
