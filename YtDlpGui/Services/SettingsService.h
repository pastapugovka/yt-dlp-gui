#pragma once

#include <string>
#include <functional>

namespace winrt::YtDlpGui::Services
{
    class SettingsService
    {
    public:
        SettingsService();

        void Save();
        void Load();

        std::wstring GetString(const std::wstring& key, const std::wstring& defaultVal = L"") const;
        void SetString(const std::wstring& key, const std::wstring& value);
        int GetInt(const std::wstring& key, int defaultVal = 0) const;
        void SetInt(const std::wstring& key, int value);
        bool GetBool(const std::wstring& key, bool defaultVal = false) const;
        void SetBool(const std::wstring& key, bool value);
        double GetDouble(const std::wstring& key, double defaultVal = 0.0) const;
        void SetDouble(const std::wstring& key, double value);

        std::wstring GetDataPath() const;

    private:
        std::wstring m_dataPath;
        std::map<std::wstring, std::wstring> m_settings;
    };
}
