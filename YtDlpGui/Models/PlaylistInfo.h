#pragma once

#include "VideoInfo.h"
#include <vector>
#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::Models
{
    struct PlaylistItem
    {
        winrt::hstring Url;
        winrt::hstring Title;
        winrt::hstring Uploader;
        double Duration{ 0 };
        int Index{ 0 };
        bool Selected{ true };
        winrt::hstring ThumbnailUrl;
    };

    struct PlaylistInfo
    {
        winrt::hstring Title;
        winrt::hstring Uploader;
        std::vector<PlaylistItem> Items;
        int TotalCount{ 0 };
        double TotalDuration{ 0 };
        winrt::hstring ThumbnailUrl;
    };
}
