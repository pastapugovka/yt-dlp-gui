#include "pch.h"
#include "ConsoleViewModel.h"

namespace winrt::YtDlpGui::ViewModels
{
    ConsoleViewModel::ConsoleViewModel()
    {
        m_runner = std::make_unique<Services::ProcessRunner>();

        m_executeCommand = winrt::make<RelayCommand>([this](auto&&) { OnExecute(); });
        m_clearCommand = winrt::make<RelayCommand>([this](auto&&) { OnClear(); });
        m_stopCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnStop(); },
            [this](auto&&) -> bool { return m_isRunning; });
    }

    void ConsoleViewModel::Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher)
    {
        SetDispatcher(dispatcher);
        AppendOutput(L"YtDlp Console - готов к работе\n", 0);
        AppendOutput(L"Введите команду yt-dlp или 'help' для справки\n\n", 1);
    }

    void ConsoleViewModel::InputText(winrt::hstring const& value)
    {
        if (m_inputText != value)
        {
            m_inputText = value;
            RaisePropertyChanged(L"InputText");
        }
    }

    void ConsoleViewModel::OnExecute()
    {
        if (m_inputText.empty())
            return;

        std::wstring cmd = std::wstring(m_inputText);

        if (cmd == L"help")
        {
            AppendOutput(L"Доступные команды:\n", 1);
            AppendOutput(L"  help          - показать справку\n", 0);
            AppendOutput(L"  clear         - очистить консоль\n", 0);
            AppendOutput(L"  yt-dlp ...    - выполнить команду yt-dlp\n\n", 0);
            AppendOutput(L"Введите любую команду yt-dlp для выполнения.\n\n", 1);
            InputText(L"");
            return;
        }

        if (cmd == L"clear")
        {
            OnClear();
            InputText(L"");
            return;
        }

        m_history.push_back(cmd);
        m_historyIndex = static_cast<int>(m_history.size());

        AppendOutput(L"> " + cmd + L"\n", 3);

        m_isRunning = true;
        RaisePropertyChanged(L"IsRunning");
        auto stopCmd = m_stopCommand.as<RelayCommand>();
        stopCmd->RaiseCanExecuteChanged();

        auto strong = get_strong();
        m_runner->SetOutputCallback([strong](const std::string& line)
        {
            strong->RunOnUI([strong, line]()
            {
                strong->AppendOutput(winrt::to_hstring(line) + L"\n", 0);
            });
        });

        std::wstring args;
        auto spacePos = cmd.find(L' ');
        if (spacePos != std::wstring::npos)
            args = cmd.substr(spacePos + 1);

        std::wstring exeName = L"yt-dlp.exe";
        if (spacePos != std::wstring::npos)
            exeName = cmd.substr(0, spacePos);

        m_runner->RunAsync(exeName, args,
            [strong](int exitCode)
            {
                strong->RunOnUI([strong, exitCode]()
                {
                    strong->m_isRunning = false;
                    strong->RaisePropertyChanged(L"IsRunning");
                    auto stopCmd = strong->m_stopCommand.as<RelayCommand>();
                    stopCmd->RaiseCanExecuteChanged();

                    if (exitCode == 0)
                        strong->AppendOutput(L"\n[OK] Команда выполнена успешно\n\n", 1);
                    else
                        strong->AppendOutput(L"\n[ERR] Код возврата: " + std::to_wstring(exitCode) + L"\n\n", 2);
                });
            });

        InputText(L"");
    }

    void ConsoleViewModel::OnClear()
    {
        m_consoleOutput = L"";
        RaisePropertyChanged(L"ConsoleOutput");
    }

    void ConsoleViewModel::OnStop()
    {
        if (m_runner)
            m_runner->Cancel();
        AppendOutput(L"\n[!] Процесс остановлен\n\n", 2);
    }

    void ConsoleViewModel::AppendOutput(const std::wstring& text, int level)
    {
        m_consoleOutput = m_consoleOutput + text;
        const size_t MaxLog = 200000;
        if (m_consoleOutput.size() > MaxLog)
            m_consoleOutput = m_consoleOutput.substr(m_consoleOutput.size() - MaxLog);
        RaisePropertyChanged(L"ConsoleOutput");
    }
}
