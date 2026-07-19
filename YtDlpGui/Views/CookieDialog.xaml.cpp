#include "pch.h"
#include "CookieDialog.xaml.h"
#include "../Services/CookieService.h"
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.Storage.Pickers.h>

namespace winrt::YtDlpGui::Views::implementation
{
    CookieDialog::CookieDialog()
    {
        InitializeComponent();
    }

    winrt::Windows::Foundation::IAsyncAction CookieDialog::ShowDialogAsync(
        winrt::Microsoft::UI::Xaml::Window const& parentWindow)
    {
        UpdatePanels();

        auto self = get_strong();
        FileRadio().Checked([this, self](auto&&, auto&&) { UpdatePanels(); });
        BrowserRadio().Checked([this, self](auto&&, auto&&) { UpdatePanels(); });
        ClipboardRadio().Checked([this, self](auto&&, auto&&) { UpdatePanels(); });

        PrimaryButtonClick([this, self](auto&& sender, auto&& args)
        {
            args.Cancel(true);
            auto action = OnPrimaryAsync();
            action.Completed([action](auto&&, auto&&) {});
        });

        co_await ShowAsync();
    }

    void CookieDialog::UpdatePanels()
    {
        bool file = FileRadio() && FileRadio().IsChecked().GetBoolean();
        bool browser = BrowserRadio() && BrowserRadio().IsChecked().GetBoolean();
        bool clipboard = ClipboardRadio() && ClipboardRadio().IsChecked().GetBoolean();
        if (BrowserPanel()) BrowserPanel().Visibility(browser ? winrt::Microsoft::UI::Xaml::Visibility::Visible : winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        if (ManualPanel()) ManualPanel().Visibility((file || clipboard) ? winrt::Microsoft::UI::Xaml::Visibility::Visible : winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    winrt::Windows::Foundation::IAsyncAction CookieDialog::OnPrimaryAsync()
    {
        auto service = std::make_shared<Services::CookieService>();
        bool ok = false;
        std::wstring message;

        if (FileRadio() && FileRadio().IsChecked().GetBoolean())
        {
            auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
            picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
            picker.FileTypeFilter().Append(L".txt");
            picker.FileTypeFilter().Append(L".json");
            picker.FileTypeFilter().Append(L".cookie");

            HWND hwnd = GetActiveWindow();
            if (hwnd)
            {
                if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                    init.Initialize(hwnd);
            }

            auto file = co_await picker.PickSingleFileAsync();
            if (file)
            {
                std::wstring path = std::wstring(file.Path());
                auto format = path.size() >= 5 && path.substr(path.size() - 5) == L".json"
                    ? Services::CookieService::CookieFormat::JSON
                    : Services::CookieService::CookieFormat::Netscape;
                ok = service->ImportFromFile(path, format);
                message = ok ? L"Куки импортированы из файла" : L"Не удалось импортировать куки из файла";
                if (ok) m_importedCookieText = path;
            }
            else
            {
                message = L"Файл не выбран";
            }
        }
        else if (ClipboardRadio() && ClipboardRadio().IsChecked().GetBoolean())
        {
            if (CookieTextBox())
            {
                std::wstring text = std::wstring(CookieTextBox().Text());
                if (!text.empty())
                {
                    ok = service->ImportFromText(text);
                    message = ok ? L"Куки импортированы из буфера" : L"Не удалось импортировать куки";
                    if (ok) m_importedCookieText = text;
                }
                else
                {
                    message = L"Вставьте текст кук";
                }
            }
        }
        else if (BrowserRadio() && BrowserRadio().IsChecked().GetBoolean())
        {
            std::wstring browser = L"Chrome";
            if (BrowserCombo())
            {
                if (auto item = BrowserCombo().SelectedItem().try_as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>())
                    browser = std::wstring(item.Content().as<winrt::hstring>());
            }
            ok = service->ImportFromBrowser(browser);
            message = ok ? L"Куки импортированы из " + browser : L"Не удалось импортировать куки из " + browser;
            if (ok) m_importedCookieText = service->GetCookieFilePathForYtDlp();
        }
        if (CookieInfoBar())
        {
            CookieInfoBar().IsOpen(true);
            CookieInfoBar().Severity(ok ? winrt::Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success
                                        : winrt::Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
            CookieInfoBar().Message(winrt::box_value(winrt::hstring(message)));
        }
        if (ok)
        {
            Hide();
        }
    }

}
