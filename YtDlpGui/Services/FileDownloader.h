#pragma once

#include <string>
#include <functional>
#include <memory>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Web.Http.h>

namespace winrt::YtDlpGui::Services
{
    class FileDownloader
    {
    public:
        FileDownloader();
        ~FileDownloader();

        void DownloadFile(const std::wstring& url, const std::wstring& destPath,
                         std::function<void(bool success, const std::wstring& error)> callback);
        bool DownloadFileSync(const std::wstring& url, const std::wstring& destPath);
        std::wstring DownloadToString(const std::wstring& url);

    private:
        winrt::Windows::Foundation::IAsyncAction DownloadFileAsync(
            const std::wstring& url, const std::wstring& destPath,
            std::function<void(bool, const std::wstring&)> callback);

        std::unique_ptr<winrt::Windows::Web::Http::HttpClient> m_httpClient;
    };
}
