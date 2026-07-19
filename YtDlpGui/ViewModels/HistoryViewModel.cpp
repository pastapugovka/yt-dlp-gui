#include "pch.h"
#include "HistoryViewModel.h"

namespace winrt::YtDlpGui::ViewModels
{
    HistoryViewModel::HistoryViewModel()
    {
        m_database = std::make_shared<Services::HistoryDatabase>();
        m_settingsService = std::make_shared<Services::SettingsService>();
        m_cookieService = std::make_shared<Services::CookieService>();

        m_deleteCommand = winrt::make<RelayCommand>(
            [this](auto&& param) { OnDelete(param); });
        m_deleteAllCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnDeleteAll(); });
        m_refreshCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnRefresh(); });
        m_exportCsvCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnExportCsv(); });
        m_exportJsonCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnExportJson(); });
        m_openFolderCommand = winrt::make<RelayCommand>(
            [this](auto&& param) { OnOpenFolder(param); });
        m_toggleStarCommand = winrt::make<RelayCommand>(
            [this](auto&& param) { OnToggleStar(param); });
        m_redownloadCommand = winrt::make<RelayCommand>(
            [this](auto&& param) { OnRedownload(param); });
    }

    void HistoryViewModel::Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher)
    {
        SetDispatcher(dispatcher);
        m_database->Initialize();
        RefreshEntries();
    }

    void HistoryViewModel::SearchText(winrt::hstring const& value)
    {
        if (m_searchText != value)
        {
            m_searchText = value;
            RaisePropertyChanged(L"SearchText");
            RefreshEntries();
        }
    }

    void HistoryViewModel::StatusFilter(winrt::hstring const& value)
    {
        if (m_statusFilter != value)
        {
            m_statusFilter = value;
            RaisePropertyChanged(L"StatusFilter");
            RefreshEntries();
        }
    }

    void HistoryViewModel::PlatformFilter(winrt::hstring const& value)
    {
        if (m_platformFilter != value)
        {
            m_platformFilter = value;
            RaisePropertyChanged(L"PlatformFilter");
            RefreshEntries();
        }
    }

    void HistoryViewModel::RefreshEntries()
    {
        m_entries.Clear();

        std::wstring status = (m_statusFilter.empty() || m_statusFilter == L"Все" || m_statusFilter == L"All")
            ? L"Все" : std::wstring(m_statusFilter);
        std::wstring platform = (m_platformFilter.empty() || m_platformFilter == L"Все" || m_platformFilter == L"All")
            ? L"Все" : std::wstring(m_platformFilter);

        std::vector<Models::HistoryEntryData> entries = m_database->FilterEntries(status, platform);

        if (!m_searchText.empty())
            entries = m_database->SearchEntries(std::wstring(m_searchText));

        m_totalCount = static_cast<int>(entries.size());

        for (auto const& entry : entries)
        {
            auto item = winrt::make<Models::HistoryEntry>();
            item.Id(entry.Id);
            item.Url(entry.Url);
            item.Title(entry.Title);
            item.Uploader(entry.Uploader);
            item.FilePath(entry.FilePath);
            item.FileName(entry.FileName);
            item.OutputDir(entry.OutputDir);
            switch (entry.Status)
            {
            case Models::HistoryStatus::Completed: item.Status(L"Completed"); break;
            case Models::HistoryStatus::Failed: item.Status(L"Failed"); break;
            case Models::HistoryStatus::Cancelled: item.Status(L"Cancelled"); break;
            }
            item.Format(entry.Format);
            item.Quality(entry.Quality);
            item.Duration(entry.Duration);
            item.FileSize(entry.FileSize);
            item.Platform(entry.Platform);
            item.DateCompleted(entry.DateCompleted);
            item.IsStarred(entry.IsStarred);
            item.ThumbnailUrl(entry.ThumbnailUrl);
            item.ErrorMessage(entry.ErrorMessage);
            m_entries.Append(item);
        }

        RaisePropertyChanged(L"TotalCount");
        RaisePropertyChanged(L"Entries");
    }

    void HistoryViewModel::OnDelete(winrt::Windows::Foundation::IInspectable const& param)
    {
        if (auto entry = param.try_as<Models::HistoryEntry>())
        {
            m_database->DeleteEntry(entry.Id());
            RefreshEntries();
        }
    }

    void HistoryViewModel::OnDeleteAll()
    {
        m_database->DeleteAllEntries();
        RefreshEntries();
    }

    void HistoryViewModel::OnRefresh()
    {
        RefreshEntries();
    }

    winrt::Windows::Foundation::IAsyncAction HistoryViewModel::OnExportCsv()
    {
        auto picker = winrt::Windows::Storage::Pickers::FileSavePicker();
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
        picker.FileTypeChoices().Insert(L"CSV", winrt::single_threaded_vector<winrt::hstring>({ L".csv" }));
        picker.SuggestedFileName(L"yt-dlp-history");

        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                init.Initialize(hwnd);
        }

        auto file = co_await picker.PickSaveFileAsync();
        if (file)
        {
            m_database->ExportToCsv(std::wstring(file.Path()));
        }
    }

    winrt::Windows::Foundation::IAsyncAction HistoryViewModel::OnExportJson()
    {
        auto picker = winrt::Windows::Storage::Pickers::FileSavePicker();
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
        picker.FileTypeChoices().Insert(L"JSON", winrt::single_threaded_vector<winrt::hstring>({ L".json" }));
        picker.SuggestedFileName(L"yt-dlp-history");

        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                init.Initialize(hwnd);
        }

        auto file = co_await picker.PickSaveFileAsync();
        if (file)
        {
            m_database->ExportToJson(std::wstring(file.Path()));
        }
    }

    void HistoryViewModel::OnOpenFolder(winrt::Windows::Foundation::IInspectable const& param)
    {
        if (auto entry = param.try_as<Models::HistoryEntry>())
        {
            auto dir = std::wstring(entry.OutputDir());
            if (!dir.empty())
            {
                auto result = reinterpret_cast<INT_PTR>(ShellExecuteW(nullptr, L"open", dir.c_str(), nullptr, nullptr, SW_SHOW));
                if (result <= 32)
                {
                    m_statusMessage = L"Не удалось открыть папку: " + winrt::to_hstring(dir);
                    RaisePropertyChanged(L"StatusMessage");
                }
            }
        }
    }

    void HistoryViewModel::OnToggleStar(winrt::Windows::Foundation::IInspectable const& param)
    {
        if (auto entry = param.try_as<Models::HistoryEntry>())
        {
            m_database->ToggleStar(entry.Id());
            RefreshEntries();
        }
    }

    void HistoryViewModel::OnRedownload(winrt::Windows::Foundation::IInspectable const& param)
    {
        auto entry = param.try_as<Models::HistoryEntry>();
        if (!entry)
            return;

        auto url = std::wstring(entry.Url());
        if (url.empty())
            return;

        auto settings = m_settingsService;
        auto cookieService = m_cookieService;
        auto db = m_database;
        auto id = entry.Id();
        auto title = std::wstring(entry.Title());

        auto strong = get_strong();
        std::thread([url, settings, cookieService, db, id, title, strong]()
        {
            auto runner = std::make_shared<Services::ProcessRunner>();
            auto dataPath = settings->GetDataPath();
            auto ytdlp = dataPath + L"yt-dlp.exe";
            auto outDir = dataPath + L"downloads";
            std::filesystem::create_directories(outDir);

            std::wstring args = Services::ProcessRunner::QuoteArg(url)
                + L" -o " + Services::ProcessRunner::QuoteArg(outDir + L"\\%(title)s.%(ext)s");
            auto cookieFile = cookieService->GetCookieFilePathForYtDlp();
            if (!cookieFile.empty())
                args += L" --cookies " + Services::ProcessRunner::QuoteArg(cookieFile);

            runner->RunSync(ytdlp, args);

            Models::HistoryEntryData updated;
            updated.Id = id;
            updated.Title = winrt::to_hstring(title);
            updated.Url = winrt::to_hstring(url);

            strong->RunOnUI([db, updated]()
            {
                db->UpdateEntry(updated);
            });
        }).detach();
    }
}
