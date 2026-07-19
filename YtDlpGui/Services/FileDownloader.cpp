#include "pch.h"
#include "FileDownloader.h"
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Storage.Streams.h>

namespace winrt::YtDlpGui::Services
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Storage;
    using namespace winrt::Windows::Web::Http;

    FileDownloader::FileDownloader() {}

    void FileDownloader::DownloadFile(const std::wstring& url, const std::wstring& destPath,
                                        std::function<void(bool, const std::wstring&)> callback)
    {
        DownloadFileAsync(url, destPath, callback);
    }

    winrt::Windows::Foundation::IAsyncAction FileDownloader::DownloadFileAsync(
        const std::wstring& url, const std::wstring& destPath,
        std::function<void(bool, const std::wstring&)> callback)
    {
        try
        {
            std::error_code ec;
            std::filesystem::create_directories(std::filesystem::path(destPath).parent_path(), ec);

            HttpClient http;
            auto response = co_await http.GetAsync(Uri(url));
            response.EnsureSuccessStatusCode();
            auto buffer = co_await response.Content().ReadAsBufferAsync();
            auto folder = Windows::Storage::StorageFolder::GetFolderFromPathAsync(
                std::filesystem::path(destPath).parent_path().wstring()).get();
            auto file = co_await folder.CreateFileAsync(
                std::filesystem::path(destPath).filename().wstring(),
                CreationCollisionOption::ReplaceExisting);
            co_await FileIO().WriteBufferAsync(file, buffer);
            if (callback) callback(true, L"");
        }
        catch (winrt::hresult_error const& ex)
        {
            if (callback) callback(false, std::wstring(ex.message()));
        }
        catch (...)
        {
            if (callback) callback(false, L"Unknown download error");
        }
    }

    bool FileDownloader::DownloadFileSync(const std::wstring& url, const std::wstring& destPath)
    {
        try
        {
            std::error_code ec;
            std::filesystem::create_directories(std::filesystem::path(destPath).parent_path(), ec);

            HttpClient http;
            auto response = http.GetAsync(Uri(url)).get();
            response.EnsureSuccessStatusCode();
            auto buffer = response.Content().ReadAsBufferAsync().get();
            auto folder = Windows::Storage::StorageFolder::GetFolderFromPathAsync(
                std::filesystem::path(destPath).parent_path().wstring()).get();
            auto file = folder.CreateFileAsync(
                std::filesystem::path(destPath).filename().wstring(),
                CreationCollisionOption::ReplaceExisting).get();
            FileIO().WriteBufferAsync(file, buffer).get();
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::wstring FileDownloader::DownloadToString(const std::wstring& url)
    {
        try
        {
            HttpClient http;
            auto response = http.GetAsync(Uri(url)).get();
            response.EnsureSuccessStatusCode();
            return response.Content().ReadAsStringAsync().get();
        }
        catch (...)
        {
            return L"";
        }
    }
}
