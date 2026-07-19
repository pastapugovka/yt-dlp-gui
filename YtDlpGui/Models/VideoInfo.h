#pragma once

#include <string>
#include <vector>
#include <winrt/Windows.Foundation.h>
#include "FormatInfo.h"

namespace winrt::YtDlpGui::Models
{
    struct VideoInfo
    {
        winrt::hstring Url;
        winrt::hstring Title;
        winrt::hstring Uploader;
        winrt::hstring ThumbnailUrl;
        winrt::hstring Description;
        double Duration{ 0 };
        double ViewCount{ 0 };
        double LikeCount{ 0 };
        bool IsLive{ false };
        bool IsPlaylist{ false };
        winrt::hstring UploadDate;
        winrt::hstring Platform;
        std::vector<FormatInfo> Formats;
        winrt::hstring JsonData;
        winrt::hstring Id;
        winrt::hstring WebpageUrl;
    };
}
