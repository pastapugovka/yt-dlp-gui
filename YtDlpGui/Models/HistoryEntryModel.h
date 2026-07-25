#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Dispatching.h>

namespace winrt::YtDlpGui::Models
{
    struct HistoryEntry : HistoryEntryT<HistoryEntry>
    {
        HistoryEntry() = default;

        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

        int64_t Id() const { return m_id; }
        void Id(int64_t value);

        winrt::hstring Url() const { return m_url; }
        void Url(winrt::hstring const& value);

        winrt::hstring Title() const { return m_title; }
        void Title(winrt::hstring const& value);

        winrt::hstring Uploader() const { return m_uploader; }
        void Uploader(winrt::hstring const& value);

        winrt::hstring FilePath() const { return m_filePath; }
        void FilePath(winrt::hstring const& value);

        winrt::hstring FileName() const { return m_fileName; }
        void FileName(winrt::hstring const& value);

        winrt::hstring OutputDir() const { return m_outputDir; }
        void OutputDir(winrt::hstring const& value);

        winrt::hstring Status() const { return m_status; }
        void Status(winrt::hstring const& value);

        winrt::hstring Format() const { return m_format; }
        void Format(winrt::hstring const& value);

        winrt::hstring Quality() const { return m_quality; }
        void Quality(winrt::hstring const& value);

        double Duration() const { return m_duration; }
        void Duration(double value);

        double FileSize() const { return m_fileSize; }
        void FileSize(double value);

        winrt::hstring Platform() const { return m_platform; }
        void Platform(winrt::hstring const& value);

        winrt::hstring DateCompleted() const { return m_dateCompleted; }
        void DateCompleted(winrt::hstring const& value);

        bool IsStarred() const { return m_isStarred; }
        void IsStarred(bool value);

        winrt::hstring ThumbnailUrl() const { return m_thumbnailUrl; }
        void ThumbnailUrl(winrt::hstring const& value);

        winrt::hstring ErrorMessage() const { return m_errorMessage; }
        void ErrorMessage(winrt::hstring const& value);

    private:
        void RaisePropertyChanged(hstring_view const& name);

        int64_t m_id{ 0 };
        winrt::hstring m_url;
        winrt::hstring m_title;
        winrt::hstring m_uploader;
        winrt::hstring m_filePath;
        winrt::hstring m_fileName;
        winrt::hstring m_outputDir;
        winrt::hstring m_status;
        winrt::hstring m_format;
        winrt::hstring m_quality;
        double m_duration{ 0 };
        double m_fileSize{ 0 };
        winrt::hstring m_platform;
        winrt::hstring m_dateCompleted;
        bool m_isStarred{ false };
        winrt::hstring m_thumbnailUrl;
        winrt::hstring m_errorMessage;

        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::YtDlpGui::Models::factory_implementation
{
    struct HistoryEntry : HistoryEntryT<HistoryEntry, implementation::HistoryEntry>
    {
    };
}
