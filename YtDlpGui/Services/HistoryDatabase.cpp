#include "pch.h"
#include "HistoryDatabase.h"
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <fstream>
#include <sstream>

namespace winrt::YtDlpGui::Services
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Data::Json;
    using namespace winrt::Windows::Storage;

    static std::wstring StatusToString(Models::HistoryStatus status)
    {
        switch (status)
        {
        case Models::HistoryStatus::Completed: return L"Completed";
        case Models::HistoryStatus::Failed: return L"Failed";
        case Models::HistoryStatus::Cancelled: return L"Cancelled";
        }
        return L"Completed";
    }

    static Models::HistoryStatus StatusFromString(std::wstring const& s)
    {
        if (s == L"Failed") return Models::HistoryStatus::Failed;
        if (s == L"Cancelled") return Models::HistoryStatus::Cancelled;
        return Models::HistoryStatus::Completed;
    }

    static JsonObject EntryToJson(Models::HistoryEntryData const& e)
    {
        JsonObject obj;
        obj.Insert(L"Id", JsonValue::CreateNumberValue(static_cast<double>(e.Id)));
        obj.Insert(L"Url", JsonValue::CreateStringValue(e.Url));
        obj.Insert(L"Title", JsonValue::CreateStringValue(e.Title));
        obj.Insert(L"Uploader", JsonValue::CreateStringValue(e.Uploader));
        obj.Insert(L"FilePath", JsonValue::CreateStringValue(e.FilePath));
        obj.Insert(L"FileName", JsonValue::CreateStringValue(e.FileName));
        obj.Insert(L"OutputDir", JsonValue::CreateStringValue(e.OutputDir));
        obj.Insert(L"Status", JsonValue::CreateStringValue(StatusToString(e.Status)));
        obj.Insert(L"Format", JsonValue::CreateStringValue(e.Format));
        obj.Insert(L"Quality", JsonValue::CreateStringValue(e.Quality));
        obj.Insert(L"Duration", JsonValue::CreateNumberValue(e.Duration));
        obj.Insert(L"FileSize", JsonValue::CreateNumberValue(e.FileSize));
        obj.Insert(L"Platform", JsonValue::CreateStringValue(e.Platform));
        obj.Insert(L"DateCompleted", JsonValue::CreateStringValue(e.DateCompleted));
        obj.Insert(L"IsStarred", JsonValue::CreateBooleanValue(e.IsStarred));
        obj.Insert(L"ThumbnailUrl", JsonValue::CreateStringValue(e.ThumbnailUrl));
        obj.Insert(L"ErrorMessage", JsonValue::CreateStringValue(e.ErrorMessage));
        return obj;
    }

    static Models::HistoryEntryData JsonToEntry(JsonObject const& obj)
    {
        Models::HistoryEntryData e;
        if (obj.HasKey(L"Id")) e.Id = static_cast<int64_t>(obj.GetNamedNumber(L"Id"));
        if (obj.HasKey(L"Url")) e.Url = obj.GetNamedString(L"Url");
        if (obj.HasKey(L"Title")) e.Title = obj.GetNamedString(L"Title");
        if (obj.HasKey(L"Uploader")) e.Uploader = obj.GetNamedString(L"Uploader");
        if (obj.HasKey(L"FilePath")) e.FilePath = obj.GetNamedString(L"FilePath");
        if (obj.HasKey(L"FileName")) e.FileName = obj.GetNamedString(L"FileName");
        if (obj.HasKey(L"OutputDir")) e.OutputDir = obj.GetNamedString(L"OutputDir");
        if (obj.HasKey(L"Status")) e.Status = StatusFromString(std::wstring(obj.GetNamedString(L"Status")));
        if (obj.HasKey(L"Format")) e.Format = obj.GetNamedString(L"Format");
        if (obj.HasKey(L"Quality")) e.Quality = obj.GetNamedString(L"Quality");
        if (obj.HasKey(L"Duration")) e.Duration = obj.GetNamedNumber(L"Duration");
        if (obj.HasKey(L"FileSize")) e.FileSize = obj.GetNamedNumber(L"FileSize");
        if (obj.HasKey(L"Platform")) e.Platform = obj.GetNamedString(L"Platform");
        if (obj.HasKey(L"DateCompleted")) e.DateCompleted = obj.GetNamedString(L"DateCompleted");
        if (obj.HasKey(L"IsStarred")) e.IsStarred = obj.GetNamedBoolean(L"IsStarred");
        if (obj.HasKey(L"ThumbnailUrl")) e.ThumbnailUrl = obj.GetNamedString(L"ThumbnailUrl");
        if (obj.HasKey(L"ErrorMessage")) e.ErrorMessage = obj.GetNamedString(L"ErrorMessage");
        return e;
    }

    HistoryDatabase::HistoryDatabase()
    {
        wchar_t appData[MAX_PATH];
        if (SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, appData) == S_OK)
        {
            m_dbPath = std::wstring(appData) + L"\\YtDlpGui\\history.json";
            std::filesystem::create_directories(std::filesystem::path(m_dbPath).parent_path());
        }
    }

    HistoryDatabase::~HistoryDatabase()
    {
    }

    bool HistoryDatabase::Initialize()
    {
        LoadEntries();
        return true;
    }

    void HistoryDatabase::LoadEntries()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_entries.clear();
        m_nextId = 1;
        std::ifstream in(m_dbPath, std::ios::binary);
        if (!in.is_open())
            return;
        std::stringstream ss;
        ss << in.rdbuf();
        std::string content = ss.str();
        if (content.empty())
            return;

        try
        {
            winrt::hstring hcontent = winrt::to_hstring(content);
            if (JsonObject::TryParse(hcontent, m_loadedRoot))
            {
                if (m_loadedRoot.HasKey(L"NextId"))
                    m_nextId = static_cast<int64_t>(m_loadedRoot.GetNamedNumber(L"NextId"));
                if (m_loadedRoot.HasKey(L"Entries") &&
                    m_loadedRoot.GetNamedValue(L"Entries").ValueType() == JsonValueType::Array)
                {
                    auto arr = m_loadedRoot.GetNamedArray(L"Entries");
                    for (uint32_t i = 0; i < arr.Size(); ++i)
                    {
                        auto val = arr.GetAt(i);
                        if (val.ValueType() == JsonValueType::Object)
                        {
                            m_entries.push_back(JsonToEntry(val.GetObject()));
                            if (m_entries.back().Id >= m_nextId)
                                m_nextId = m_entries.back().Id + 1;
                        }
                    }
                }
            }
        }
        catch (...)
        {
        }
    }

void HistoryDatabase::WriteAtomic(const std::wstring& content)
{
    std::error_code ec;
    std::filesystem::create_directories(std::filesystem::path(m_dbPath).parent_path(), ec);

    std::string utf8 = winrt::to_string(content);
    std::wstring tmpPath = m_dbPath + L".tmp";
    {
        std::ofstream out(tmpPath, std::ios::binary | std::ios::trunc);
        if (!out.is_open())
            return;
        out.write(utf8.data(), static_cast<std::streamsize>(utf8.size()));
    }
    std::filesystem::rename(tmpPath, m_dbPath, ec);
    if (ec)
    {
        std::ofstream out(m_dbPath, std::ios::binary | std::ios::trunc);
        if (out.is_open())
        {
            out.write(utf8.data(), static_cast<std::streamsize>(utf8.size()));
            out.close();
        }
    }
}

    void HistoryDatabase::SaveEntries()
    {
        JsonObject root;
        root.Insert(L"NextId", JsonValue::CreateNumberValue(static_cast<double>(m_nextId)));
        JsonArray arr;
        for (auto const& e : m_entries)
            arr.Append(EntryToJson(e));
        root.Insert(L"Entries", arr);

        WriteAtomic(std::wstring(root.Stringify()));
    }

    bool HistoryDatabase::AddEntryUnlocked(Models::HistoryEntryData& e)
    {
        e.Id = m_nextId++;
        m_entries.push_back(e);
        SaveEntries();
        return true;
    }

    bool HistoryDatabase::AddEntry(const Models::HistoryEntryData& entry)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        Models::HistoryEntryData e = entry;
        return AddEntryUnlocked(e);
    }

    bool HistoryDatabase::UpdateEntry(const Models::HistoryEntryData& entry)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& e : m_entries)
        {
            if (e.Id == entry.Id)
            {
                e = entry;
                SaveEntries();
                return true;
            }
        }
            Models::HistoryEntryData e = entry;
        return AddEntryUnlocked(e);
    }

    bool HistoryDatabase::DeleteEntry(int64_t id)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = std::find_if(m_entries.begin(), m_entries.end(),
            [id](Models::HistoryEntryData const& e) { return e.Id == id; });
        if (it != m_entries.end())
        {
            m_entries.erase(it);
            SaveEntries();
            return true;
        }
        return false;
    }

    bool HistoryDatabase::DeleteAllEntries()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_entries.clear();
        SaveEntries();
        return true;
    }

    bool HistoryDatabase::ToggleStar(int64_t id)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& e : m_entries)
        {
            if (e.Id == id)
            {
                e.IsStarred = !e.IsStarred;
                SaveEntries();
                return true;
            }
        }
        return false;
    }

    std::vector<Models::HistoryEntryData> HistoryDatabase::GetAllEntries()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_entries;
    }

    std::vector<Models::HistoryEntryData> HistoryDatabase::SearchEntries(const std::wstring& query)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::vector<Models::HistoryEntryData> result;
        std::wstring q = query;
        std::transform(q.begin(), q.end(), q.begin(), ::towlower);
        for (auto const& e : m_entries)
        {
            std::wstring title = e.Title;
            std::transform(title.begin(), title.end(), title.begin(), ::towlower);
            if (title.find(q) != std::wstring::npos)
                result.push_back(e);
        }
        return result;
    }

    std::vector<Models::HistoryEntryData> HistoryDatabase::FilterEntries(const std::wstring& status,
                                                                           const std::wstring& platform)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::vector<Models::HistoryEntryData> result;
        for (auto const& e : m_entries)
        {
            if (!status.empty() && status != L"Все" && StatusToString(e.Status) != status)
                continue;
            if (!platform.empty() && platform != L"Все" && e.Platform != platform)
                continue;
            result.push_back(e);
        }
        return result;
    }

    int64_t HistoryDatabase::GetEntryCount()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return static_cast<int64_t>(m_entries.size());
    }

    bool HistoryDatabase::ExportToCsv(const std::wstring& filePath)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        try
        {
            auto csvField = [](const std::wstring& v) -> std::wstring
            {
                if (v.find(L',') == std::wstring::npos &&
                    v.find(L'"') == std::wstring::npos &&
                    v.find(L'\n') == std::wstring::npos &&
                    v.find(L'\r') == std::wstring::npos)
                {
                    return v;
                }
                std::wstring escaped;
                escaped.reserve(v.size() + 2);
                escaped += L'"';
                for (wchar_t ch : v)
                {
                    if (ch == L'"') escaped += L'"';
                    escaped += ch;
                }
                escaped += L'"';
                return escaped;
            };

            std::wostringstream lineBuffer;
            lineBuffer << L"Id,Title,Uploader,Platform,Status,Format,Quality,Duration,FileSize,DateCompleted,Url\n";
            for (auto const& e : m_entries)
            {
                lineBuffer << e.Id << L","
                    << csvField(e.Title) << L","
                    << csvField(e.Uploader) << L","
                    << csvField(e.Platform) << L","
                    << StatusToString(e.Status) << L","
                    << csvField(e.Format) << L","
                    << csvField(e.Quality) << L","
                    << e.Duration << L","
                    << e.FileSize << L","
                    << csvField(e.DateCompleted) << L","
                    << csvField(e.Url) << L"\n";
            }
            std::string utf8 = winrt::to_string(lineBuffer.str());
            std::ofstream out(filePath, std::ios::binary);
            if (!out.is_open())
                return false;
            out.write(utf8.data(), static_cast<std::streamsize>(utf8.size()));
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool HistoryDatabase::ExportToJson(const std::wstring& filePath)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        try
        {
            JsonObject root;
            root.Insert(L"NextId", JsonValue::CreateNumberValue(static_cast<double>(m_nextId)));
            JsonArray arr;
            for (auto const& e : m_entries)
                arr.Append(EntryToJson(e));
            root.Insert(L"Entries", arr);
            std::wstring content = std::wstring(root.Stringify());
            std::string utf8 = winrt::to_string(content);
            std::ofstream out(filePath, std::ios::binary);
            if (!out.is_open())
                return false;
            out.write(utf8.data(), static_cast<std::streamsize>(utf8.size()));
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
}
