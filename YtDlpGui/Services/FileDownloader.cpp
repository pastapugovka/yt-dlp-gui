#include "pch.h"
#include "FileDownloader.h"
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h>

namespace winrt::YtDlpGui::Services
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Storage;
    using namespace winrt::Windows::Web::Http;
    using namespace winrt::Windows::Web::Http::Headers;

    FileDownloader::FileDownloader() : m_httpClient(std::make_unique<HttpClient>())
    {
        m_httpClient->DefaultRequestHeaders().UserAgent().ParseAdd(L"yt-dlp-gui/1.0");
    }

    FileDownloader::~FileDownloader() = default;

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

            auto response = co_await m_httpClient->GetAsync(Uri(url), HttpCompletionOption::ResponseHeadersRead);
            response.EnsureSuccessStatusCode();

            auto content = response.Content();
            auto folder = co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(
                std::filesystem::path(destPath).parent_path().wstring());
            auto file = co_await folder.CreateFileAsync(
                std::filesystem::path(destPath).filename().wstring(),
                CreationCollisionOption::ReplaceExisting);

            auto inputStream = co_await content.GetInputStreamAsync();
            auto outputStream = co_await file.OpenAsync(FileAccessMode::ReadWrite);
            co_await RandomAccessStream::CopyAsync(inputStream, outputStream);
            co_await outputStream.FlushAsync();

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
            std::filesystem::path parentPath = std::filesystem::path(destPath).parent_path();
            std::filesystem::create_directories(parentPath, ec);

            auto response = m_httpClient->GetAsync(Uri(url), HttpCompletionOption::ResponseHeadersRead).get();
            response.EnsureSuccessStatusCode();

            auto content = response.Content();
            auto folder = Windows::Storage::StorageFolder::GetFolderFromPathAsync(
                parentPath.wstring()).get();
            auto file = folder.CreateFileAsync(
                std::filesystem::path(destPath).filename().wstring(),
                CreationCollisionOption::ReplaceExisting).get();

            auto inputStream = content.GetInputStreamAsync().get();
            auto outputStream = file.OpenAsync(FileAccessMode::ReadWrite).get();
            RandomAccessStream::CopyAsync(inputStream, outputStream).get();
            outputStream.FlushAsync().get();

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
            auto response = m_httpClient->GetAsync(Uri(url)).get();
            response.EnsureSuccessStatusCode();
            return response.Content().ReadAsStringAsync().get();
        }
        catch (...)
        {
            return L"";
        }
    }
}
