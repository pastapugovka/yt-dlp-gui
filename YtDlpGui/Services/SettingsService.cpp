#include "pch.h"
#include "SettingsService.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <winrt/Windows.Data.Json.h>

namespace winrt::YtDlpGui::Services
{
    using namespace winrt::Windows::Data::Json;
    SettingsService::SettingsService()
    {
        PWSTR localAppData = nullptr;
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &localAppData)) && localAppData)
        {
            m_dataPath = std::wstring(localAppData) + L"\\YtDlpGui\\";
            CoTaskMemFree(localAppData);
        }
        else
        {
            wchar_t exePath[MAX_PATH];
            GetModuleFileNameW(nullptr, exePath, MAX_PATH);
            std::wstring path(exePath);
            auto pos = path.find_last_of(L"\\");
            m_dataPath = (pos != std::wstring::npos) ? path.substr(0, pos + 1) : L".\\";
        }

        std::filesystem::create_directories(m_dataPath + L"config");
        Load();
    }

    void SettingsService::Save()
    {
        JsonObject obj;
        for (auto const& [key, value] : m_settings)
        {
            obj.Insert(key, JsonValue::CreateStringValue(value));
        }

        std::wofstream file(m_dataPath + L"config\\settings.json");
        if (!file.is_open())
            return;

        std::wstring content = std::wstring(obj.Stringify());
        std::string utf8 = winrt::to_string(content);
        file.write(utf8.data(), static_cast<std::streamsize>(utf8.size()));
        file.close();
    }

    void SettingsService::Load()
    {
        std::wifstream file(m_dataPath + L"config\\settings.json");
        if (!file.is_open())
            return;

        std::wstringstream buffer;
        buffer << file.rdbuf();
        std::wstring content = buffer.str();

        try
        {
            auto json = winrt::Windows::Data::Json::JsonObject::Parse(content);
            auto iter = json.First();
            while (iter.HasCurrent())
            {
                auto key = iter.Current().Key();
                auto val = iter.Current().Value();
                if (val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                    m_settings[key] = val.GetString();
                iter.MoveNext();
            }
        }
        catch (...) {}
    }

    std::wstring SettingsService::GetString(const std::wstring& key, const std::wstring& defaultVal) const
    {
        auto it = m_settings.find(key);
        return it != m_settings.end() ? it->second : defaultVal;
    }

    void SettingsService::SetString(const std::wstring& key, const std::wstring& value)
    {
        m_settings[key] = value;
    }

    int SettingsService::GetInt(const std::wstring& key, int defaultVal) const
    {
        auto val = GetString(key);
        if (val.empty()) return defaultVal;
        return std::stoi(val);
    }

    void SettingsService::SetInt(const std::wstring& key, int value)
    {
        m_settings[key] = std::to_wstring(value);
    }

    bool SettingsService::GetBool(const std::wstring& key, bool defaultVal) const
    {
        auto val = GetString(key);
        if (val.empty()) return defaultVal;
        return val == L"true" || val == L"1";
    }

    void SettingsService::SetBool(const std::wstring& key, bool value)
    {
        m_settings[key] = value ? L"true" : L"false";
    }

    double SettingsService::GetDouble(const std::wstring& key, double defaultVal) const
    {
        auto val = GetString(key);
        if (val.empty()) return defaultVal;
        return std::stod(val);
    }

    void SettingsService::SetDouble(const std::wstring& key, double value)
    {
        std::wostringstream ss;
        ss << value;
        m_settings[key] = ss.str();
    }

    std::wstring SettingsService::GetDataPath() const
    {
        return m_dataPath;
    }
}
