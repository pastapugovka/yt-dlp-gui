#pragma once

#include "../ViewModels/ViewModelBase.h"
#include "../ViewModels/RelayCommand.h"
#include "../Models/Models.h"
#include "../Services/YtDlpService.h"
#include "../Services/CookieService.h"
#include "../Services/SettingsService.h"
#include "../Services/DownloadService.h"
#include "../Services/FileDownloader.h"
#include "../Services/HistoryDatabase.h"
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt::YtDlpGui::ViewModels
{
    struct DownloadViewModel : DownloadViewModelT<DownloadViewModel>, ViewModelBase
    {
        using ViewModelBase::PropertyChanged;

        DownloadViewModel();

        void Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher);

        winrt::hstring Url() const { return m_url; }
        void Url(winrt::hstring const& value);

        winrt::hstring Title() const { return m_title; }
        void Title(winrt::hstring const& value);

        winrt::hstring Uploader() const { return m_uploader; }
        void Uploader(winrt::hstring const& value);

        winrt::hstring ThumbnailUrl() const { return m_thumbnailUrl; }
        void ThumbnailUrl(winrt::hstring const& value);

        winrt::hstring VideoCodec() const { return m_videoCodec; }
        void VideoCodec(winrt::hstring const& value);

        winrt::hstring AudioCodec() const { return m_audioCodec; }
        void AudioCodec(winrt::hstring const& value);

        winrt::hstring AudioBitrate() const { return m_audioBitrate; }
        void AudioBitrate(winrt::hstring const& value);

        winrt::hstring Resolution() const { return m_resolution; }
        void Resolution(winrt::hstring const& value);

        winrt::hstring OutputDir() const { return m_outputDir; }
        void OutputDir(winrt::hstring const& value);

        winrt::hstring FileNameTemplate() const { return m_fileNameTemplate; }
        void FileNameTemplate(winrt::hstring const& value);

        winrt::hstring LogText() const { return m_logText; }
        void LogText(winrt::hstring const& value);

        winrt::hstring AdvancedFlags() const { return m_advancedFlags; }
        void AdvancedFlags(winrt::hstring const& value);

        winrt::hstring StatusText() const { return m_statusText; }
        void StatusText(winrt::hstring const& value);

        winrt::hstring CurrentFileText() const { return m_currentFileText; }

        bool IsAnalyzing() const { return m_isAnalyzing; }
        bool IsDownloading() const { return m_isDownloading; }
        bool HasVideoInfo() const { return m_hasVideoInfo; }
        bool IsPlaylist() const { return m_isPlaylist; }
        bool AudioOnly() const { return m_audioOnly; }
        void AudioOnly(bool value);
        bool VideoOnly() const { return m_videoOnly; }
        void VideoOnly(bool value);
        bool SeparateAudio() const { return m_separateAudio; }
        void SeparateAudio(bool value);
        bool IsIndeterminate() const { return m_isIndeterminate; }
        double ProgressValue() const { return m_progressValue; }

        winrt::Windows::Foundation::IInspectable VideoInfoPanel() const { return m_videoInfoPanel; }

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> AvailableCodecs() const;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> AvailableResolutions() const;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> AvailableAudioCodecs() const;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> AvailableBitrates() const;

        winrt::Microsoft::UI::Xaml::Input::ICommand AnalyzeCommand() { return m_analyzeCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand DownloadCommand() { return m_downloadCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand CancelCommand() { return m_cancelCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand PasteFromClipboardCommand() { return m_pasteCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand OpenOutputDirCommand() { return m_openOutputDirCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ClearLogCommand() { return m_clearLogCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand OpenCookieDialogCommand() { return m_openCookieDialogCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand PasteCookiesCommand() { return m_pasteCookiesCommand; }

        void AppendLog(const std::wstring& message, int level);
        void ClearLog();
        void UpdateProgress(double percent, const std::wstring& speed, const std::wstring& eta);

        winrt::event_token DownloadStarted(winrt::Windows::Foundation::TypedEventHandler<IInspectable, IInspectable> const& handler) { return m_downloadStarted.add(handler); }
        void DownloadStarted(winrt::event_token const& token) noexcept { m_downloadStarted.remove(token); }
        winrt::event_token DownloadCompleted(winrt::Windows::Foundation::TypedEventHandler<IInspectable, bool> const& handler) { return m_downloadCompleted.add(handler); }
        void DownloadCompleted(winrt::event_token const& token) noexcept { m_downloadCompleted.remove(token); }

        winrt::event_token ShowCookieDialogRequested(winrt::Windows::Foundation::TypedEventHandler<IInspectable, IInspectable> const& handler) { return m_showCookieDialog.add(handler); }
        void ShowCookieDialogRequested(winrt::event_token const& token) noexcept { m_showCookieDialog.remove(token); }

    private:
        void OnAnalyze();
        void OnDownload();
        void OnCancel();
        void OnPasteFromClipboard();
        void OnOpenOutputDir();
        void OnClearLog();
        void OnOpenCookieDialog();
        void OnPasteCookies();
        void ProcessAnalysisResult(const std::string& json);
        void RecordHistory(bool success, const std::wstring& error);
        void RecordHistoryCancelled();
        std::wstring BuildOutputPath();
        std::wstring GetFormatString();

        winrt::hstring m_url;
        winrt::hstring m_title;
        winrt::hstring m_uploader;
        winrt::hstring m_thumbnailUrl;
        winrt::hstring m_videoCodec{ L"best" };
        winrt::hstring m_audioCodec{ L"best" };
        winrt::hstring m_audioBitrate{ L"192" };
        winrt::hstring m_resolution{ L"best" };
        winrt::hstring m_outputDir;
        winrt::hstring m_fileNameTemplate{ L"%(title)s [%(id)s].%(ext)s" };
        winrt::hstring m_logText;
        winrt::hstring m_advancedFlags;
        winrt::hstring m_statusText{ L"Готово" };
        winrt::hstring m_currentFileText;
        winrt::hstring m_cookieText;

        bool m_isAnalyzing{ false };
        bool m_isDownloading{ false };
        bool m_cancelRequested{ false };
        bool m_hasVideoInfo{ false };
        bool m_isPlaylist{ false };
        bool m_audioOnly{ false };
        bool m_videoOnly{ false };
        bool m_separateAudio{ false };
        bool m_isIndeterminate{ false };
        double m_progressValue{ 0 };

        winrt::Windows::Foundation::IInspectable m_videoInfoPanel{ nullptr };

        std::shared_ptr<Services::YtDlpService> m_ytdlpService;
        std::shared_ptr<Services::CookieService> m_cookieService;
        std::shared_ptr<Services::SettingsService> m_settingsService;
        std::shared_ptr<Services::HistoryDatabase> m_historyDatabase;
        Services::ProcessRunner m_processRunner;

        winrt::Microsoft::UI::Xaml::Input::ICommand m_analyzeCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_downloadCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_cancelCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_pasteCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_openOutputDirCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_clearLogCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_openCookieDialogCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_pasteCookiesCommand{ nullptr };

        winrt::event<winrt::Windows::Foundation::TypedEventHandler<IInspectable, IInspectable>> m_downloadStarted;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<IInspectable, bool>> m_downloadCompleted;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<IInspectable, IInspectable>> m_showCookieDialog;

        Models::VideoInfo m_currentVideoInfo;
        Models::PlaylistInfo m_currentPlaylistInfo;

        mutable winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> m_availableCodecs{ nullptr };
        mutable winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> m_availableResolutions{ nullptr };
        mutable winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> m_availableAudioCodecs{ nullptr };
        mutable winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> m_availableBitrates{ nullptr };
    };
}

namespace winrt::YtDlpGui::ViewModels::factory_implementation
{
    struct DownloadViewModel : DownloadViewModelT<DownloadViewModel, implementation::DownloadViewModel>
    {
    };
}
