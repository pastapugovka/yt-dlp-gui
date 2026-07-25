#pragma once

#include "SettingsPage.xaml.g.h"
#include "../ViewModels/SettingsViewModel.h"

namespace winrt::YtDlpGui::Views::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();

        winrt::YtDlpGui::ViewModels::SettingsViewModel ViewModel() const { return m_viewModel; }

    private:
        winrt::YtDlpGui::ViewModels::SettingsViewModel m_viewModel{ nullptr };
    };
}

namespace winrt::YtDlpGui::Views::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
