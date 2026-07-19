#pragma once

#include "CookieDialog.xaml.g.h"

namespace winrt::YtDlpGui::Views::implementation
{
    struct CookieDialog : CookieDialogT<CookieDialog>
    {
        CookieDialog();

        winrt::Windows::Foundation::IAsyncAction ShowDialogAsync(
            winrt::Microsoft::UI::Xaml::Window const& parentWindow);

        winrt::hstring ImportedCookieText() const { return m_importedCookieText; }

    private:
        void ImportBrowserBtn_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void UpdatePanels();
        void OnPrimary();

        winrt::hstring m_importedCookieText;
    };
}

namespace winrt::YtDlpGui::Views::factory_implementation
{
    struct CookieDialog : CookieDialogT<CookieDialog, implementation::CookieDialog>
    {
    };
}
