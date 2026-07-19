#pragma once

#include "ConsolePage.xaml.g.h"
#include "../ViewModels/ConsoleViewModel.h"

namespace winrt::YtDlpGui::Views::implementation
{
    struct ConsolePage : ConsolePageT<ConsolePage>
    {
        ConsolePage();

        winrt::YtDlpGui::ViewModels::ConsoleViewModel ViewModel() const { return m_viewModel; }

        void InputBox_KeyDown(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);

    private:
        winrt::YtDlpGui::ViewModels::ConsoleViewModel m_viewModel{ nullptr };
    };
}

namespace winrt::YtDlpGui::Views::factory_implementation
{
    struct ConsolePage : ConsolePageT<ConsolePage, implementation::ConsolePage>
    {
    };
}
