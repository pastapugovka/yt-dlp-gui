#pragma once

#include <string>
#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::Models
{
    enum class DownloadStatus
    {
        Pending,
        Downloading,
        Merging,
        Paused,
        Completed,
        Failed,
        Cancelled
    };

    struct DownloadItem
    {
        int Id{ 0 };
        winrt::hstring Url;
        winrt::hstring Title;
        winrt::hstring FilePath;
        winrt::hstring FileName;
        winrt::hstring OutputDir;
        DownloadStatus Status{ DownloadStatus::Pending };
        double Progress{ 0 };
        double TotalSize{ 0 };
        double DownloadedSize{ 0 };
        double Speed{ 0 };
        winrt::hstring ETA;
        winrt::hstring Format;
        winrt::hstring Quality;
        winrt::hstring ErrorMessage;
        winrt::hstring Platform;
        double Duration{ 0 };
        bool IsPlaylist{ false };
        int PlaylistIndex{ 0 };
        bool IsStarred{ false };
        winrt::hstring DateAdded;
        winrt::hstring DateCompleted;
    };
}
