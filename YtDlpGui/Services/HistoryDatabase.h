#pragma once

#include "../Models/HistoryEntry.h"
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <mutex>
#include <winrt/Windows.Data.Json.h>

namespace winrt::YtDlpGui::Services
{
    class HistoryDatabase
    {
    public:
        HistoryDatabase();
        ~HistoryDatabase();

        bool Initialize();
        bool AddEntry(const Models::HistoryEntry& entry);
        bool UpdateEntry(const Models::HistoryEntry& entry);
        bool DeleteEntry(int64_t id);
        bool DeleteAllEntries();
        bool ToggleStar(int64_t id);
        std::vector<Models::HistoryEntry> GetAllEntries();
        std::vector<Models::HistoryEntry> SearchEntries(const std::wstring& query);
        std::vector<Models::HistoryEntry> FilterEntries(const std::wstring& status,
                                                        const std::wstring& platform);
        int64_t GetEntryCount();
        bool ExportToCsv(const std::wstring& filePath);
        bool ExportToJson(const std::wstring& filePath);

    private:
        void LoadEntries();
        void SaveEntries();
        void WriteAtomic(const std::wstring& content);

        std::wstring m_dbPath;
        std::vector<Models::HistoryEntry> m_entries;
        int64_t m_nextId{ 1 };
        winrt::Windows::Data::Json::JsonObject m_loadedRoot{ nullptr };
        std::mutex m_mutex;
    };
}
