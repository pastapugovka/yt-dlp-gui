#pragma once

#include <string>
#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::Models
{
    enum class HistoryStatus
    {
        Completed,
        Failed,
        Cancelled
    };

    struct HistoryEntry
    {
        int64_t Id{ 0 };
        winrt::hstring Url;
        winrt::hstring Title;
        winrt::hstring Uploader;
        winrt::hstring FilePath;
        winrt::hstring FileName;
        winrt::hstring OutputDir;
        HistoryStatus Status{ HistoryStatus::Completed };
        winrt::hstring Format;
        winrt::hstring Quality;
        double Duration{ 0 };
        double FileSize{ 0 };
        winrt::hstring Platform;
        winrt::hstring DateCompleted;
        bool IsStarred{ false };
        winrt::hstring ThumbnailUrl;
        winrt::hstring ErrorMessage;
    };
}
