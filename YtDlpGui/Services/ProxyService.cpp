#include "pch.h"
#include "ProxyService.h"

namespace winrt::YtDlpGui::Services
{
    ProxyService::ProxyService() {}

    void ProxyService::SetProxy(const std::wstring& proxyUrl)
    {
        m_proxyUrl = proxyUrl;
    }

    std::wstring ProxyService::BuildProxyArgs() const
    {
        if (m_proxyUrl.empty())
            return L"";
        return L" --proxy \"" + m_proxyUrl + L"\"";
    }

    std::vector<std::wstring> ProxyService::GetSupportedProxyTypes()
    {
        return { L"HTTP", L"HTTPS", L"SOCKS4", L"SOCKS5", L"Hysteria" };
    }

    bool ProxyService::ValidateProxy(const std::wstring& proxy)
    {
        if (proxy.empty())
            return true;

        auto pos = proxy.find(L"://");
        if (pos == std::wstring::npos)
            return false;

        std::wstring scheme = proxy.substr(0, pos);
        return scheme == L"http" || scheme == L"https" || scheme == L"socks4" ||
               scheme == L"socks5" || scheme == L"hysteria";
    }
}
