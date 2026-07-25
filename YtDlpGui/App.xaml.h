#pragma once

#include "App.xaml.g.h"

namespace winrt::YtDlpGui::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(
            [[maybe_unused]] Windows::Foundation::IInspectable const& sender,
            [[maybe_unused]] Microsoft::UI::Xaml::LaunchActivatedEventArgs const& args);

    private:
        winrt::Microsoft::UI::Xaml::Window m_window{ nullptr };
    };
}
