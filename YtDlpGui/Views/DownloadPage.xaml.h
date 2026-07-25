#pragma once

#include "DownloadPage.xaml.g.h"
#include "../ViewModels/DownloadViewModel.h"

namespace winrt::YtDlpGui::Views::implementation
{
    struct DownloadPage : DownloadPageT<DownloadPage>
    {
        DownloadPage();

        winrt::YtDlpGui::ViewModels::DownloadViewModel ViewModel() const { return m_viewModel; }

        void UrlTextBox_KeyDown(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);

        void ShowAdvancedFlags_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        winrt::YtDlpGui::ViewModels::DownloadViewModel m_viewModel{ nullptr };
    };
}

namespace winrt::YtDlpGui::Views::factory_implementation
{
    struct DownloadPage : DownloadPageT<DownloadPage, implementation::DownloadPage>
    {
    };
}
