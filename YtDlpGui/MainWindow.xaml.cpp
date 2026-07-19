#include "pch.h"
#include "MainWindow.xaml.h"
#include "Views/DownloadPage.xaml.h"
#include "Views/HistoryPage.xaml.h"
#include "Views/SettingsPage.xaml.h"
#include "Views/ConsolePage.xaml.h"
#include "../Services/SettingsService.h"

namespace winrt::YtDlpGui::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        ApplyTheme();

        auto downloadItem = winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem();
        downloadItem.Content(winrt::box_value(L"Загрузка"));
        downloadItem.Icon(winrt::make<winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource>(
            winrt::Microsoft::UI::Xaml::Controls::Symbol::Download));
        downloadItem.Tag(winrt::box_value(L"Download"));
        m_navMenuItems.Append(downloadItem);

        auto historyItem = winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem();
        historyItem.Content(winrt::box_value(L"История"));
        historyItem.Icon(winrt::make<winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource>(
            winrt::Microsoft::UI::Xaml::Controls::Symbol::Clock));
        historyItem.Tag(winrt::box_value(L"History"));
        m_navMenuItems.Append(historyItem);

        auto consoleItem = winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem();
        consoleItem.Content(winrt::box_value(L"Терминал"));
        consoleItem.Icon(winrt::make<winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource>(
            winrt::Microsoft::UI::Xaml::Controls::Symbol::Terminal));
        consoleItem.Tag(winrt::box_value(L"Console"));
        m_navMenuItems.Append(consoleItem);
    }

    void MainWindow::NavView_Loaded(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ContentFrame().Navigate(winrt::xaml_typename<YtDlpGui::Views::DownloadPage>());
    }

    void MainWindow::NavView_SelectionChanged(
        Microsoft::UI::Xaml::Controls::NavigationView const&,
        Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const&)
    {
        if (NavView().IsSettingsSelected())
        {
            ContentFrame().Navigate(winrt::xaml_typename<YtDlpGui::Views::SettingsPage>());
            return;
        }

        auto item = NavView().SelectedItem();
        if (auto nvi = item.try_as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>())
        {
            auto tag = winrt::unbox_value<winrt::hstring>(nvi.Tag());
            if (tag == L"Download")
            {
                ContentFrame().Navigate(winrt::xaml_typename<YtDlpGui::Views::DownloadPage>());
            }
            else if (tag == L"History")
            {
                ContentFrame().Navigate(winrt::xaml_typename<YtDlpGui::Views::HistoryPage>());
            }
            else if (tag == L"Console")
            {
                ContentFrame().Navigate(winrt::xaml_typename<YtDlpGui::Views::ConsolePage>());
            }
        }
    }

    void MainWindow::ApplyTheme()
    {
        try
        {
            Services::SettingsService settings;
            auto theme = settings.GetString(L"Theme", L"Default");
            auto app = winrt::Microsoft::UI::Xaml::Application::Current();
            if (theme == L"Light")
                app.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Light);
            else if (theme == L"Dark")
                app.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Dark);
            else
                app.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Default);
        }
        catch (...) {}
    }
}
