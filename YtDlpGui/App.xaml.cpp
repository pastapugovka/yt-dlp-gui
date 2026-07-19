#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include <mddbootstrap.h>

namespace winrt::YtDlpGui::implementation
{
    App::App()
    {
        InitializeComponent();

        UnhandledException([](IInspectable const&, Microsoft::UI::Xaml::UnhandledExceptionEventArgs const& e)
        {
            std::wstring msg = L"Unhandled exception: " + std::wstring(e.Message());
            ::OutputDebugStringW(msg.c_str());
            e.Handled(true);
        });
    }

    void App::OnLaunched(IInspectable const&, Microsoft::UI::Xaml::LaunchActivatedEventArgs const&)
    {
        m_window = make<MainWindow>();
        m_window->Activate();
    }
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    const UINT32 majorMinorVersion{ 10005 };
    PCWSTR version{ L"1.5.240802000" };
    PACKAGE_VERSION minVersion{};
    minVersion.Major = 1;
    minVersion.Minor = 5;
    minVersion.Build = 2408;
    minVersion.Revision = 0;

    HRESULT hr = MddBootstrapInitialize(majorMinorVersion, version, minVersion);
    if (FAILED(hr))
    {
        ::OutputDebugStringW(L"WindowsAppSDK bootstrap failed.\n");
        return 1;
    }

    winrt::Microsoft::UI::Xaml::Application::Start([](auto const&) {});

    MddBootstrapShutdown();
    return 0;
}
