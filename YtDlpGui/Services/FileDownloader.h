#pragma once

#include <string>
#include <functional>
#include <winrt/Windows.Storage.h>

namespace winrt::YtDlpGui::Services
{
    class FileDownloader
    {
    public:
        FileDownloader();

        void DownloadFile(const std::wstring& url, const std::wstring& destPath,
                         std::function<void(bool success, const std::wstring& error)> callback);
        bool DownloadFileSync(const std::wstring& url, const std::wstring& destPath);
        std::wstring DownloadToString(const std::wstring& url);

    private:
        winrt::Windows::Foundation::IAsyncAction DownloadFileAsync(
            const std::wstring& url, const std::wstring& destPath,
            std::function<void(bool, const std::wstring&)> callback);
    };
}
