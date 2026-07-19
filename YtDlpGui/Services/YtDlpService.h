#pragma once

#include "ProcessRunner.h"
#include "../Models/VideoInfo.h"
#include "../Models/PlaylistInfo.h"
#include "../Models/AppSettings.h"
#include <string>
#include <functional>
#include <memory>

namespace winrt::YtDlpGui::Services
{
    using AnalysisCompleteCallback = std::function<void(bool success, const std::string& jsonData)>;
    using LogCallback = std::function<void(const std::string& message, int level)>;

    class YtDlpService
    {
    public:
        YtDlpService();
        ~YtDlpService();

        void SetYtDlpPath(const std::wstring& path) { m_ytdlpPath = path; }
        void SetFfmpegPath(const std::wstring& path) { m_ffmpegPath = path; }
        void SetProxy(const std::wstring& proxy) { m_proxy = proxy; }
        void SetUserAgent(const std::wstring& ua) { m_userAgent = ua; }
        void SetCookies(const std::wstring& cookies) { m_cookies = cookies; }
        void SetOutputDir(const std::wstring& dir) { m_outputDir = dir; }
        void SetLogCallback(LogCallback cb) { m_logCallback = std::move(cb); }

        void AnalyzeUrl(const std::wstring& url);
        void DownloadVideo(const std::wstring& url, const std::wstring& outputTemplate,
                           const std::wstring& formatStr, const std::wstring& extraArgs);
        void DownloadPlaylist(const std::wstring& url, const std::wstring& outputTemplate,
                              const std::wstring& formatStr, int start, int end,
                              const std::wstring& extraArgs);
        void CancelCurrentOperation();
        bool IsRunning() const { return m_runner && m_runner->IsRunning(); }

        std::wstring BuildFormatString(const std::wstring& videoCodec,
                                        const std::wstring& resolution,
                                        const std::wstring& audioCodec,
                                        const std::wstring& audioBitrate,
                                        bool audioOnly, bool videoOnly);
        std::wstring BuildCommonArgs(const AppSettings& settings);

        Models::VideoInfo ParseVideoInfo(const std::string& json);
        std::vector<Models::PlaylistItem> ParsePlaylistEntries(const std::string& json);

        void CheckForUpdates();

    private:
        std::wstring GetExecutablePath();

        std::wstring m_ytdlpPath{ L"yt-dlp.exe" };
        std::wstring m_ffmpegPath{ L"ffmpeg.exe" };
        std::wstring m_proxy;
        std::wstring m_userAgent;
        std::wstring m_cookies;
        std::wstring m_outputDir;

        LogCallback m_logCallback;
        std::unique_ptr<ProcessRunner> m_runner;
    };
}
