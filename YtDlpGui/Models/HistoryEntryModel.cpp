#include "pch.h"
#include "HistoryEntryModel.h"

namespace winrt::YtDlpGui::Models
{
    winrt::event_token HistoryEntry::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void HistoryEntry::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

    void HistoryEntry::RaisePropertyChanged(std::wstring const& name)
    {
        m_propertyChanged(nullptr, Windows::UI::Xaml::Data::PropertyChangedEventArgs(name));
    }

    void HistoryEntry::Id(int64_t value)
    {
        if (m_id != value) { m_id = value; RaisePropertyChanged(L"Id"); }
    }

    void HistoryEntry::Url(winrt::hstring const& value)
    {
        if (m_url != value) { m_url = value; RaisePropertyChanged(L"Url"); }
    }

    void HistoryEntry::Title(winrt::hstring const& value)
    {
        if (m_title != value) { m_title = value; RaisePropertyChanged(L"Title"); }
    }

    void HistoryEntry::Uploader(winrt::hstring const& value)
    {
        if (m_uploader != value) { m_uploader = value; RaisePropertyChanged(L"Uploader"); }
    }

    void HistoryEntry::FilePath(winrt::hstring const& value)
    {
        if (m_filePath != value) { m_filePath = value; RaisePropertyChanged(L"FilePath"); }
    }

    void HistoryEntry::FileName(winrt::hstring const& value)
    {
        if (m_fileName != value) { m_fileName = value; RaisePropertyChanged(L"FileName"); }
    }

    void HistoryEntry::OutputDir(winrt::hstring const& value)
    {
        if (m_outputDir != value) { m_outputDir = value; RaisePropertyChanged(L"OutputDir"); }
    }

    void HistoryEntry::Status(winrt::hstring const& value)
    {
        if (m_status != value) { m_status = value; RaisePropertyChanged(L"Status"); }
    }

    void HistoryEntry::Format(winrt::hstring const& value)
    {
        if (m_format != value) { m_format = value; RaisePropertyChanged(L"Format"); }
    }

    void HistoryEntry::Quality(winrt::hstring const& value)
    {
        if (m_quality != value) { m_quality = value; RaisePropertyChanged(L"Quality"); }
    }

    void HistoryEntry::Duration(double value)
    {
        if (m_duration != value) { m_duration = value; RaisePropertyChanged(L"Duration"); }
    }

    void HistoryEntry::FileSize(double value)
    {
        if (m_fileSize != value) { m_fileSize = value; RaisePropertyChanged(L"FileSize"); }
    }

    void HistoryEntry::Platform(winrt::hstring const& value)
    {
        if (m_platform != value) { m_platform = value; RaisePropertyChanged(L"Platform"); }
    }

    void HistoryEntry::DateCompleted(winrt::hstring const& value)
    {
        if (m_dateCompleted != value) { m_dateCompleted = value; RaisePropertyChanged(L"DateCompleted"); }
    }

    void HistoryEntry::IsStarred(bool value)
    {
        if (m_isStarred != value) { m_isStarred = value; RaisePropertyChanged(L"IsStarred"); }
    }

    void HistoryEntry::ThumbnailUrl(winrt::hstring const& value)
    {
        if (m_thumbnailUrl != value) { m_thumbnailUrl = value; RaisePropertyChanged(L"ThumbnailUrl"); }
    }

    void HistoryEntry::ErrorMessage(winrt::hstring const& value)
    {
        if (m_errorMessage != value) { m_errorMessage = value; RaisePropertyChanged(L"ErrorMessage"); }
    }
}
