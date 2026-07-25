#pragma once

#include <string>
#include <functional>
#include <memory>
#include <atomic>

namespace winrt::YtDlpGui::Services
{
    struct DownloadProgress
    {
        double Percent{ 0 };
        double TotalSize{ 0 };
        double DownloadedSize{ 0 };
        double Speed{ 0 };
        std::string ETA;
        std::string StatusText;
    };

    using ProgressCallback = std::function<void(const DownloadProgress&)>;

    class DownloadService
    {
    public:
        DownloadService();
        ~DownloadService();

        void SetLogCallback(std::function<void(const std::string&, int)> cb) { m_logCallback = std::move(cb); }
        void SetProgressCallback(ProgressCallback cb) { m_progressCallback = std::move(cb); }

        void StartDownload(const std::wstring& url, const std::wstring& outputTemplate,
                          const std::wstring& formatStr, const std::wstring& extraArgs,
                          std::function<void(int exitCode)> onComplete);
        void CancelDownload();

        bool IsDownloading() const { return m_downloading; }

    private:
        std::unique_ptr<class ProcessRunner> m_runner;
        std::atomic<bool> m_downloading{ false };
        std::function<void(const std::string&, int)> m_logCallback;
        ProgressCallback m_progressCallback;
    };
}
