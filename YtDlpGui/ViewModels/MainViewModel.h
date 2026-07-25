#pragma once

#include "../ViewModels/ViewModelBase.h"
#include "../ViewModels/RelayCommand.h"
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::ViewModels
{
    struct MainViewModel : MainViewModelT<MainViewModel>, ViewModelBase
    {
        using ViewModelBase::PropertyChanged;

        MainViewModel();

        winrt::hstring AppTitle() const { return m_appTitle; }
        int CurrentTabIndex() const { return m_currentTabIndex; }
        void CurrentTabIndex(int value);

        winrt::Microsoft::UI::Xaml::Input::ICommand ShowSettingsCommand() { return m_showSettingsCommand; }

    private:
        winrt::hstring m_appTitle{ L"YtDlp GUI" };
        int m_currentTabIndex{ 0 };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_showSettingsCommand{ nullptr };
    };
}

namespace winrt::YtDlpGui::ViewModels::factory_implementation
{
    struct MainViewModel : MainViewModelT<MainViewModel, implementation::MainViewModel>
    {
    };
}
