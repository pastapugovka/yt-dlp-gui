#include "pch.h"
#include "DownloadService.h"
#include "ProcessRunner.h"

namespace winrt::YtDlpGui::Services
{
    DownloadService::DownloadService()
        : m_runner(std::make_unique<ProcessRunner>())
    {
    }

    DownloadService::~DownloadService()
    {
        CancelDownload();
    }

    void DownloadService::StartDownload(const std::wstring& url, const std::wstring& outputTemplate,
                                         const std::wstring& formatStr, const std::wstring& extraArgs,
                                         std::function<void(int exitCode)> onComplete)
    {
        if (m_downloading)
            CancelDownload();

        m_downloading = true;

        m_runner->SetOutputCallback([this](const std::string& line)
        {
            if (m_logCallback)
                m_logCallback(line, 0);
        });

        std::wstring args;
        args += L" --newline --no-warnings";
        args += L" -o " + ProcessRunner::QuoteArg(outputTemplate);
        args += L" -f " + ProcessRunner::QuoteArg(formatStr);
        if (!extraArgs.empty())
            args += L" " + extraArgs;
        args += L" " + ProcessRunner::QuoteArg(url);

        m_runner->RunAsync(L"yt-dlp.exe", args,
            [this, onComplete](int exitCode)
            {
                m_downloading = false;
                if (onComplete) onComplete(exitCode);
            });
    }

    void DownloadService::CancelDownload()
    {
        if (m_runner)
            m_runner->Cancel();
        m_downloading = false;
    }
}
