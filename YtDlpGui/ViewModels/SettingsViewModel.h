#pragma once

#include "../ViewModels/ViewModelBase.h"
#include "../ViewModels/RelayCommand.h"
#include "../Models/AppSettings.h"
#include "../Services/SettingsService.h"
#include "../Services/CookieService.h"
#include "../Services/YtDlpService.h"
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt::YtDlpGui::ViewModels
{
    struct SettingsViewModel : SettingsViewModelT<SettingsViewModel>, ViewModelBase
    {
        using ViewModelBase::PropertyChanged;

        SettingsViewModel();

        void Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher);

        winrt::hstring YtDlpPath() const { return m_ytDlpPath; }
        void YtDlpPath(winrt::hstring const& value);

        winrt::hstring FfmpegPath() const { return m_ffmpegPath; }
        void FfmpegPath(winrt::hstring const& value);

        winrt::hstring ProxyUrl() const { return m_proxyUrl; }
        void ProxyUrl(winrt::hstring const& value);

        winrt::hstring UserAgent() const { return m_userAgent; }
        void UserAgent(winrt::hstring const& value);

        winrt::hstring OutputDir() const { return m_outputDir; }
        void OutputDir(winrt::hstring const& value);

        winrt::hstring FileNameTemplate() const { return m_fileNameTemplate; }
        void FileNameTemplate(winrt::hstring const& value);

        winrt::hstring Theme() const { return m_theme; }
        void Theme(winrt::hstring const& value);

        winrt::hstring PreferredLanguage() const { return m_preferredLanguage; }
        void PreferredLanguage(winrt::hstring const& value);

        int MaxConcurrentDownloads() const { return m_maxConcurrentDownloads; }
        void MaxConcurrentDownloads(int value);

        bool EmbedThumbnail() const { return m_embedThumbnail; }
        void EmbedThumbnail(bool value);
        bool WriteMetadata() const { return m_writeMetadata; }
        void WriteMetadata(bool value);
        bool EmbedSubtitles() const { return m_embedSubtitles; }
        void EmbedSubtitles(bool value);
        bool AutoUpdate() const { return m_autoUpdate; }
        void AutoUpdate(bool value);

        winrt::hstring StatusMessage() const { return m_statusMessage; }

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> AvailableBrowsers() const;

        winrt::Microsoft::UI::Xaml::Input::ICommand BrowseYtDlpCommand() { return m_browseYtDlpCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand BrowseFfmpegCommand() { return m_browseFfmpegCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand BrowseOutputDirCommand() { return m_browseOutputDirCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand SaveCommand() { return m_saveCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ImportCookiesCommand() { return m_importCookiesCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ImportCookiesFromBrowserCommand() { return m_importCookiesFromBrowserCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand CheckUpdatesCommand() { return m_checkUpdatesCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ClearCookiesCommand() { return m_clearCookiesCommand; }

    private:
        winrt::Windows::Foundation::IAsyncAction OnBrowseYtDlp();
        winrt::Windows::Foundation::IAsyncAction OnBrowseFfmpeg();
        winrt::Windows::Foundation::IAsyncAction OnBrowseOutputDir();
        void OnSave();
        winrt::Windows::Foundation::IAsyncAction OnImportCookies();
        winrt::Windows::Foundation::IAsyncAction OnImportCookiesFromBrowser();
        void OnCheckUpdates();
        void OnClearCookies();
        void ApplyTheme();
        void LoadSettings();
        void ApplySettings();

        winrt::hstring m_ytDlpPath{ L"yt-dlp.exe" };
        winrt::hstring m_ffmpegPath{ L"ffmpeg.exe" };
        winrt::hstring m_proxyUrl;
        winrt::hstring m_userAgent;
        winrt::hstring m_outputDir;
        winrt::hstring m_fileNameTemplate{ L"%(title)s [%(id)s].%(ext)s" };
        winrt::hstring m_theme{ L"Default" };
        winrt::hstring m_preferredLanguage{ L"ru" };
        winrt::hstring m_statusMessage;
        int m_maxConcurrentDownloads{ 3 };
        bool m_embedThumbnail{ false };
        bool m_writeMetadata{ true };
        bool m_embedSubtitles{ false };
        bool m_autoUpdate{ false };

        std::shared_ptr<Services::SettingsService> m_settingsService;
        std::shared_ptr<Services::CookieService> m_cookieService;
        std::shared_ptr<Services::YtDlpService> m_ytdlpService;

        winrt::Microsoft::UI::Xaml::Input::ICommand m_browseYtDlpCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_browseFfmpegCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_browseOutputDirCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_saveCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_importCookiesCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_importCookiesFromBrowserCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_checkUpdatesCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_clearCookiesCommand{ nullptr };

        mutable winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> m_availableBrowsers{ nullptr };
    };
}

namespace winrt::YtDlpGui::ViewModels::factory_implementation
{
    struct SettingsViewModel : SettingsViewModelT<SettingsViewModel, implementation::SettingsViewModel>
    {
    };
}
