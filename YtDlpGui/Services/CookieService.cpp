#include "pch.h"
#include "CookieService.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdlib>

namespace winrt::YtDlpGui::Services
{
    CookieService::CookieService()
    {
        wchar_t appData[MAX_PATH];
        if (SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, appData) == S_OK)
        {
            m_cookieFilePath = std::wstring(appData) + L"\\YtDlpGui\\cookies.txt";
        }
    }

    bool CookieService::ImportFromFile(const std::wstring& filePath, CookieFormat format)
    {
        std::wifstream file(filePath);
        if (!file.is_open())
            return false;

        std::wstringstream buffer;
        buffer << file.rdbuf();
        std::wstring content = buffer.str();

        switch (format)
        {
        case CookieFormat::Netscape:
            return ParseNetscapeFormat(content);
        case CookieFormat::JSON:
            return ParseJsonFormat(content);
        case CookieFormat::Header:
            return ParseHeaderFormat(content);
        }
        return false;
    }

    bool CookieService::ImportFromBrowser(const std::wstring& browserName)
    {
        std::wstring cookiePath = GetBrowserCookiePath(browserName);
        if (cookiePath.empty())
            return false;

        return ImportFromFile(cookiePath, CookieFormat::Netscape);
    }

    bool CookieService::ImportFromClipboard(const std::wstring& text)
    {
        if (text.empty())
            return false;

        if (text.find(L"{") != std::wstring::npos &&
            text.find(L"\"cookies\"") != std::wstring::npos)
        {
            return ParseJsonFormat(text);
        }

        if (text.find(L"# Netscape HTTP Cookie File") != std::wstring::npos)
        {
            return ParseNetscapeFormat(text);
        }

        if (text.find(L"Cookie:") != std::wstring::npos ||
            text.find(L"Set-Cookie:") != std::wstring::npos)
        {
            return ParseHeaderFormat(text);
        }

        if (text.find(L"=") != std::wstring::npos && text.find(L"\t") != std::wstring::npos)
        {
            return ParseNetscapeFormat(text);
        }

        return ParseHeaderFormat(text);
    }

    bool CookieService::ImportFromText(const std::wstring& text)
    {
        return ImportFromClipboard(text);
    }

    bool CookieService::ParseNetscapeFormat(const std::wstring& content)
    {
        std::wstring netscapeHeader = L"# Netscape HTTP Cookie File\n";
        std::wstring fileContent = content;
        if (fileContent.find(netscapeHeader) == std::wstring::npos)
        {
            fileContent = netscapeHeader + fileContent;
        }
        SaveCookieFile(fileContent);
        return true;
    }

    bool CookieService::ParseJsonFormat(const std::wstring& content)
    {
        try
        {
            auto json = winrt::Windows::Data::Json::JsonObject::Parse(content);
            if (!json.HasKey(L"cookies"))
                return false;

            auto cookies = json.GetNamedArray(L"cookies");
            std::wstring netscape = L"# Netscape HTTP Cookie File\n";

            for (auto const& cookieVal : cookies)
            {
                auto cookie = cookieVal.GetObject();
                std::wstring domain, name, value, path;
                bool secure = false;
                int64_t expiry = 0;

                if (cookie.HasKey(L"domain"))
                    domain = cookie.GetNamedString(L"domain");
                if (cookie.HasKey(L"name"))
                    name = cookie.GetNamedString(L"name");
                if (cookie.HasKey(L"value"))
                    value = cookie.GetNamedString(L"value");
                if (cookie.HasKey(L"path"))
                    path = cookie.GetNamedString(L"path");
                if (cookie.HasKey(L"secure"))
                    secure = cookie.GetNamedBoolean(L"secure");
                if (cookie.HasKey(L"expirationDate"))
                    expiry = static_cast<int64_t>(cookie.GetNamedNumber(L"expirationDate"));

                netscape += domain + L"\tTRUE\t" + path + L"\t" +
                            (secure ? L"TRUE" : L"FALSE") + L"\t" +
                            std::to_wstring(expiry) + L"\t" +
                            name + L"\t" + value + L"\n";
            }

            SaveCookieFile(netscape);
            return true;
        }
        catch (...) { return false; }
    }

    bool CookieService::ParseHeaderFormat(const std::wstring& content)
    {
        std::wstring netscape = L"# Netscape HTTP Cookie File\n";
        std::wistringstream stream(content);
        std::wstring line;

        while (std::getline(stream, line))
        {
            size_t pos = line.find(L"Cookie:");
            if (pos == std::wstring::npos)
                pos = line.find(L"Set-Cookie:");
            if (pos == std::wstring::npos)
                continue;

            std::wstring cookieStr = line.substr(pos);
            if (cookieStr.find(L"Cookie:") != std::wstring::npos)
                cookieStr = cookieStr.substr(8);
            else
                cookieStr = cookieStr.substr(11);

            std::wistringstream csStream(cookieStr);
            std::wstring pair;
            while (std::getline(csStream, pair, L';'))
            {
                auto eqPos = pair.find(L'=');
                if (eqPos != std::wstring::npos)
                {
                    std::wstring name = pair.substr(0, eqPos);
                    std::wstring value = pair.substr(eqPos + 1);
                    auto trimLeft = [](std::wstring& s) {
                        s.erase(0, s.find_first_not_of(L" \t"));
                    };
                    auto trimRight = [](std::wstring& s) {
                        s.erase(s.find_last_not_of(L" \t") + 1);
                    };
                    trimLeft(name);
                    trimRight(name);
                    trimLeft(value);
                    trimRight(value);

                    netscape += L".youtube.com\tTRUE\t/\tFALSE\t0\t" + name + L"\t" + value + L"\n";
                }
            }
        }

        if (netscape.size() > 40)
        {
            SaveCookieFile(netscape);
            return true;
        }
        return false;
    }

    void CookieService::SaveCookieFile(const std::wstring& content)
    {
        std::filesystem::path path(m_cookieFilePath);
        std::filesystem::create_directories(path.parent_path());

        std::wofstream file(m_cookieFilePath);
        if (file.is_open())
        {
            file << content;
            file.close();
        }
    }

    void CookieService::ClearCookies()
    {
        if (!m_cookieFilePath.empty() && std::filesystem::exists(m_cookieFilePath))
        {
            std::filesystem::remove(m_cookieFilePath);
        }
        m_cookieText.clear();
    }

    std::wstring CookieService::GetCookiesAsText() const
    {
        if (m_cookieFilePath.empty())
            return L"";
        std::wifstream file(m_cookieFilePath);
        std::wstringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    std::wstring CookieService::GetCookieFilePathForYtDlp() const
    {
        return m_cookieFilePath;
    }

    std::wstring CookieService::GetBrowserCookiePath(const std::wstring& browserName)
    {
        wchar_t localAppData[MAX_PATH];
        SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, localAppData);

        if (browserName == L"Chrome")
            return std::wstring(localAppData) + L"\\Google\\Chrome\\User Data\\Default\\Network\\Cookies";
        else if (browserName == L"Edge")
            return std::wstring(localAppData) + L"\\Microsoft\\Edge\\User Data\\Default\\Network\\Cookies";
        else if (browserName == L"Firefox")
        {
            std::wstring firefoxDir = std::wstring(localAppData) + L"\\Mozilla\\Firefox\\Profiles";
            if (std::filesystem::exists(firefoxDir))
            {
                for (auto& entry : std::filesystem::directory_iterator(firefoxDir))
                {
                    if (entry.is_directory())
                    {
                        std::wstring cookiesPath = entry.path().wstring() + L"\\cookies.sqlite";
                        if (std::filesystem::exists(cookiesPath))
                            return cookiesPath;
                    }
                }
            }
            return L"";
        }
        else if (browserName == L"Opera")
            return std::wstring(localAppData) + L"\\Opera Software\\Opera Stable\\Network\\Cookies";
        else if (browserName == L"Opera GX")
            return std::wstring(localAppData) + L"\\Opera Software\\Opera GX Stable\\Network\\Cookies";

        return L"";
    }
}
