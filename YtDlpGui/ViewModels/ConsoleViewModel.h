#pragma once

#include "../ViewModels/ViewModelBase.h"
#include "../ViewModels/RelayCommand.h"
#include "../Services/ProcessRunner.h"
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <string>
#include <memory>

namespace winrt::YtDlpGui::ViewModels
{
    struct ConsoleViewModel : ConsoleViewModelT<ConsoleViewModel>, ViewModelBase
    {
        using ViewModelBase::PropertyChanged;

        ConsoleViewModel();

        void Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher);

        winrt::hstring ConsoleOutput() const { return m_consoleOutput; }
        winrt::hstring InputText() const { return m_inputText; }
        void InputText(winrt::hstring const& value);
        winrt::hstring CommandHistory() const { return m_commandHistory; }
        bool IsRunning() const { return m_isRunning; }

        winrt::Microsoft::UI::Xaml::Input::ICommand ExecuteCommand() { return m_executeCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ClearCommand() { return m_clearCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand StopCommand() { return m_stopCommand; }

    private:
        void OnExecute();
        void OnClear();
        void OnStop();
        void AppendOutput(const std::wstring& text, int level);

        winrt::hstring m_consoleOutput;
        winrt::hstring m_inputText;
        winrt::hstring m_commandHistory;
        bool m_isRunning{ false };

        std::unique_ptr<Services::ProcessRunner> m_runner;
        std::vector<std::wstring> m_history;
        int m_historyIndex{ -1 };

        winrt::Microsoft::UI::Xaml::Input::ICommand m_executeCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_clearCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_stopCommand{ nullptr };
    };
}

namespace winrt::YtDlpGui::ViewModels::factory_implementation
{
    struct ConsoleViewModel : ConsoleViewModelT<ConsoleViewModel, implementation::ConsoleViewModel>
    {
    };
}
