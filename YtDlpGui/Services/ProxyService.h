#pragma once

#include <string>
#include <functional>

namespace winrt::YtDlpGui::Services
{
    class ProxyService
    {
    public:
        ProxyService();

        void SetProxy(const std::wstring& proxyUrl);
        std::wstring GetProxy() const { return m_proxyUrl; }
        bool HasProxy() const { return !m_proxyUrl.empty(); }

        std::wstring BuildProxyArgs() const;
        static std::vector<std::wstring> GetSupportedProxyTypes();
        static bool ValidateProxy(const std::wstring& proxy);

    private:
        std::wstring m_proxyUrl;
    };
}
