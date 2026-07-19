#include "pch.h"
#include "ConsolePage.xaml.h"

namespace winrt::YtDlpGui::Views::implementation
{
    ConsolePage::ConsolePage()
    {
        InitializeComponent();
        m_viewModel = winrt::make<winrt::YtDlpGui::ViewModels::ConsoleViewModel>();
        m_viewModel.Initialize(DispatcherQueue());
    }

    void ConsolePage::InputBox_KeyDown(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args)
    {
        if (args.Key() == winrt::Windows::System::VirtualKey::Enter)
        {
            m_viewModel.ExecuteCommand().Execute(nullptr);
        }
    }
}
