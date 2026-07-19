#include "pch.h"
#include "DownloadPage.xaml.h"

namespace winrt::YtDlpGui::Views::implementation
{
    DownloadPage::DownloadPage()
    {
        InitializeComponent();
        m_viewModel = winrt::make<winrt::YtDlpGui::ViewModels::DownloadViewModel>();
        m_viewModel.Initialize(DispatcherQueue());
    }

    void DownloadPage::UrlTextBox_KeyDown(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args)
    {
        if (args.Key() == winrt::Windows::System::VirtualKey::Enter)
        {
            m_viewModel.AnalyzeCommand().Execute(nullptr);
        }
    }

    void DownloadPage::ShowAdvancedFlags_Click(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        if (AdvancedFlagsPanel().Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Visible)
            AdvancedFlagsPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        else
            AdvancedFlagsPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
    }
}
