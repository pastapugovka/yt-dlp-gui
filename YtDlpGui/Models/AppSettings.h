#pragma once

#include <string>
#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::Models
{
    struct AppSettings
    {
        winrt::hstring YtDlpPath{ L"yt-dlp.exe" };
        winrt::hstring FfmpegPath{ L"ffmpeg.exe" };
        winrt::hstring OutputDir{ L"" };
        winrt::hstring FileNameTemplate{ L"%(title)s [%(id)s].%(ext)s" };
        winrt::hstring Proxy;
        winrt::hstring UserAgent;
        winrt::hstring Cookies;
        winrt::hstring CookieBrowser;
        winrt::hstring Theme{ L"Default" };
        int MaxConcurrentDownloads{ 3 };
        bool OverwriteFiles{ false };
        bool WriteMetadata{ true };
        bool EmbedThumbnail{ false };
        bool EmbedSubtitles{ false };
        bool AudioOnly{ false };
        bool VideoOnly{ false };
        bool SeparateAudio{ false };
        bool CreatePlaylistDir{ true };
        bool NumberFiles{ true };
        bool DownloadSubtitles{ false };
        bool AutoUpdateYtDlp{ false };
        winrt::hstring VideoCodec{ L"best" };
        winrt::hstring AudioCodec{ L"best" };
        winrt::hstring AudioBitrate{ L"192" };
        winrt::hstring Resolution{ L"best" };
        bool UseCookiesFromClipboard{ false };
        bool EncryptCookies{ false };
        winrt::hstring AdvancedFlags;
        winrt::hstring PreferredLanguage{ L"ru" };
    };
}
