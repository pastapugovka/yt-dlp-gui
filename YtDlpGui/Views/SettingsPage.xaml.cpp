#include "pch.h"
#include "SettingsPage.xaml.h"

namespace winrt::YtDlpGui::Views::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();
        m_viewModel = winrt::make<winrt::YtDlpGui::ViewModels::SettingsViewModel>();
        m_viewModel.Initialize(DispatcherQueue());
    }
}
