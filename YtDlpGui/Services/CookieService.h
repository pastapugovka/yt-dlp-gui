#pragma once

#include <string>
#include <functional>

namespace winrt::YtDlpGui::Services
{
    class CookieService
    {
    public:
        enum class CookieFormat
        {
            Netscape,
            JSON,
            Header
        };

        CookieService();

        bool ImportFromFile(const std::wstring& filePath, CookieFormat format);
        bool ImportFromBrowser(const std::wstring& browserName);
        bool ImportFromClipboard(const std::wstring& text);
        bool ImportFromText(const std::wstring& text);

        std::wstring GetCookieFilePath() const { return m_cookieFilePath; }
        bool HasCookies() const { return !m_cookieFilePath.empty(); }
        void ClearCookies();
        std::wstring GetCookiesAsText() const;

        std::wstring GetCookieFilePathForYtDlp() const;

        static std::wstring GetBrowserCookiePath(const std::wstring& browserName);

    private:
        bool ParseNetscapeFormat(const std::wstring& content);
        bool ParseJsonFormat(const std::wstring& content);
        bool ParseHeaderFormat(const std::wstring& content);
        void SaveCookieFile(const std::wstring& content);

        std::wstring m_cookieFilePath;
        std::wstring m_cookieText;
    };
}
