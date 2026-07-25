#pragma once

#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::Models
{
    struct FormatInfo
    {
        winrt::hstring FormatId;
        winrt::hstring Extension;
        winrt::hstring Resolution;
        winrt::hstring VideoCodec;
        winrt::hstring AudioCodec;
        double FileSize{ 0 };
        double Bitrate{ 0 };
        int FPS{ 0 };
        bool HasVideo{ false };
        bool HasAudio{ false };
        winrt::hstring QualityNote;
        winrt::hstring FormatNote;
    };
}
