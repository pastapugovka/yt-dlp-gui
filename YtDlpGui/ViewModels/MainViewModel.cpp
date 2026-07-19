#include "pch.h"
#include "MainViewModel.h"

namespace winrt::YtDlpGui::ViewModels
{
    MainViewModel::MainViewModel()
    {
        m_showSettingsCommand = winrt::make<RelayCommand>([this](auto&&) { CurrentTabIndex(2); });
    }

    void MainViewModel::CurrentTabIndex(int value)
    {
        if (m_currentTabIndex != value)
        {
            m_currentTabIndex = value;
            RaisePropertyChanged(L"CurrentTabIndex");
        }
    }
}
