#include "pch.h"
#include "SettingsViewModel.h"

namespace winrt::YtDlpGui::ViewModels
{
    SettingsViewModel::SettingsViewModel()
    {
        m_settingsService = std::make_shared<Services::SettingsService>();
        m_cookieService = std::make_shared<Services::CookieService>();
        m_ytdlpService = std::make_shared<Services::YtDlpService>();

        m_browseYtDlpCommand = winrt::make<RelayCommand>([this](auto&&) { OnBrowseYtDlp(); });
        m_browseFfmpegCommand = winrt::make<RelayCommand>([this](auto&&) { OnBrowseFfmpeg(); });
        m_browseOutputDirCommand = winrt::make<RelayCommand>([this](auto&&) { OnBrowseOutputDir(); });
        m_saveCommand = winrt::make<RelayCommand>([this](auto&&) { OnSave(); });
        m_importCookiesCommand = winrt::make<RelayCommand>([this](auto&&) { OnImportCookies(); });
        m_importCookiesFromBrowserCommand = winrt::make<RelayCommand>([this](auto&&) { OnImportCookiesFromBrowser(); });
        m_checkUpdatesCommand = winrt::make<RelayCommand>([this](auto&&) { OnCheckUpdates(); });
        m_clearCookiesCommand = winrt::make<RelayCommand>([this](auto&&) { OnClearCookies(); });
    }

    void SettingsViewModel::Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher)
    {
        SetDispatcher(dispatcher);
        LoadSettings();
    }

    void SettingsViewModel::YtDlpPath(winrt::hstring const& value)
    {
        if (m_ytDlpPath != value)
        {
            m_ytDlpPath = value;
            RaisePropertyChanged(L"YtDlpPath");
        }
    }

    void SettingsViewModel::FfmpegPath(winrt::hstring const& value)
    {
        if (m_ffmpegPath != value)
        {
            m_ffmpegPath = value;
            RaisePropertyChanged(L"FfmpegPath");
        }
    }

    void SettingsViewModel::ProxyUrl(winrt::hstring const& value)
    {
        if (m_proxyUrl != value)
        {
            m_proxyUrl = value;
            RaisePropertyChanged(L"ProxyUrl");
        }
    }

    void SettingsViewModel::UserAgent(winrt::hstring const& value)
    {
        if (m_userAgent != value)
        {
            m_userAgent = value;
            RaisePropertyChanged(L"UserAgent");
        }
    }

    void SettingsViewModel::OutputDir(winrt::hstring const& value)
    {
        if (m_outputDir != value)
        {
            m_outputDir = value;
            RaisePropertyChanged(L"OutputDir");
        }
    }

    void SettingsViewModel::FileNameTemplate(winrt::hstring const& value)
    {
        if (m_fileNameTemplate != value)
        {
            m_fileNameTemplate = value;
            RaisePropertyChanged(L"FileNameTemplate");
        }
    }

    void SettingsViewModel::Theme(winrt::hstring const& value)
    {
        if (m_theme != value)
        {
            m_theme = value;
            RaisePropertyChanged(L"Theme");
            ApplyTheme();
        }
    }

    void SettingsViewModel::ApplyTheme()
    {
        try
        {
            auto app = winrt::Microsoft::UI::Xaml::Application::Current();
            if (m_theme == L"Light")
                app.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Light);
            else if (m_theme == L"Dark")
                app.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Dark);
            else
                app.RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme::Default);
        }
        catch (...) {}
    }

    void SettingsViewModel::PreferredLanguage(winrt::hstring const& value)
    {
        if (m_preferredLanguage != value)
        {
            m_preferredLanguage = value;
            RaisePropertyChanged(L"PreferredLanguage");
        }
    }

    void SettingsViewModel::MaxConcurrentDownloads(int value)
    {
        if (m_maxConcurrentDownloads != value)
        {
            m_maxConcurrentDownloads = value;
            RaisePropertyChanged(L"MaxConcurrentDownloads");
        }
    }

    void SettingsViewModel::EmbedThumbnail(bool value)
    {
        if (m_embedThumbnail != value)
        {
            m_embedThumbnail = value;
            RaisePropertyChanged(L"EmbedThumbnail");
        }
    }

    void SettingsViewModel::WriteMetadata(bool value)
    {
        if (m_writeMetadata != value)
        {
            m_writeMetadata = value;
            RaisePropertyChanged(L"WriteMetadata");
        }
    }

    void SettingsViewModel::EmbedSubtitles(bool value)
    {
        if (m_embedSubtitles != value)
        {
            m_embedSubtitles = value;
            RaisePropertyChanged(L"EmbedSubtitles");
        }
    }

    void SettingsViewModel::AutoUpdate(bool value)
    {
        if (m_autoUpdate != value)
        {
            m_autoUpdate = value;
            RaisePropertyChanged(L"AutoUpdate");
        }
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>
    SettingsViewModel::AvailableBrowsers() const
    {
        auto vec = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
        vec.Append(winrt::box_value(L"Chrome"));
        vec.Append(winrt::box_value(L"Edge"));
        vec.Append(winrt::box_value(L"Firefox"));
        vec.Append(winrt::box_value(L"Opera"));
        vec.Append(winrt::box_value(L"Opera GX"));
        return vec;
    }

    void SettingsViewModel::LoadSettings()
    {
        auto svc = m_settingsService.get();
        m_ytDlpPath = svc->GetString(L"YtDlpPath", L"yt-dlp.exe");
        m_ffmpegPath = svc->GetString(L"FfmpegPath", L"ffmpeg.exe");
        m_outputDir = svc->GetString(L"OutputDir", L"");
        m_fileNameTemplate = svc->GetString(L"FileNameTemplate", L"%(title)s [%(id)s].%(ext)s");
        m_proxyUrl = svc->GetString(L"Proxy");
        m_userAgent = svc->GetString(L"UserAgent");
        m_theme = svc->GetString(L"Theme", L"Default");
        m_preferredLanguage = svc->GetString(L"PreferredLanguage", L"ru");
        m_maxConcurrentDownloads = svc->GetInt(L"MaxConcurrentDownloads", 3);
        m_embedThumbnail = svc->GetBool(L"EmbedThumbnail");
        m_writeMetadata = svc->GetBool(L"WriteMetadata", true);
        m_embedSubtitles = svc->GetBool(L"EmbedSubtitles");
        m_autoUpdate = svc->GetBool(L"AutoUpdate");

        RaisePropertyChanged(L"");
    }

    void SettingsViewModel::ApplySettings()
    {
        auto svc = m_settingsService.get();
        svc->SetString(L"YtDlpPath", std::wstring(m_ytDlpPath));
        svc->SetString(L"FfmpegPath", std::wstring(m_ffmpegPath));
        svc->SetString(L"OutputDir", std::wstring(m_outputDir));
        svc->SetString(L"FileNameTemplate", std::wstring(m_fileNameTemplate));
        svc->SetString(L"Proxy", std::wstring(m_proxyUrl));
        svc->SetString(L"UserAgent", std::wstring(m_userAgent));
        svc->SetString(L"Theme", std::wstring(m_theme));
        svc->SetString(L"PreferredLanguage", std::wstring(m_preferredLanguage));
        svc->SetInt(L"MaxConcurrentDownloads", m_maxConcurrentDownloads);
        svc->SetBool(L"EmbedThumbnail", m_embedThumbnail);
        svc->SetBool(L"WriteMetadata", m_writeMetadata);
        svc->SetBool(L"EmbedSubtitles", m_embedSubtitles);
        svc->SetBool(L"AutoUpdate", m_autoUpdate);
        svc->Save();
    }

    void SettingsViewModel::OnBrowseYtDlp()
    {
        auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::ComputerFolder);
        picker.FileTypeFilter().Append(L".exe");
        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                init.Initialize(hwnd);
        }
        auto file = picker.PickSingleFileAsync().get();
        if (file)
        {
            YtDlpPath(file.Path());
            ApplySettings();
            m_statusMessage = L"Путь к yt-dlp обновлён";
            RaisePropertyChanged(L"StatusMessage");
        }
    }

    void SettingsViewModel::OnBrowseFfmpeg()
    {
        auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::ComputerFolder);
        picker.FileTypeFilter().Append(L".exe");
        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                init.Initialize(hwnd);
        }
        auto file = picker.PickSingleFileAsync().get();
        if (file)
        {
            FfmpegPath(file.Path());
            ApplySettings();
            m_statusMessage = L"Путь к ffmpeg обновлён";
            RaisePropertyChanged(L"StatusMessage");
        }
    }

    void SettingsViewModel::OnBrowseOutputDir()
    {
        auto picker = winrt::Windows::Storage::Pickers::FolderPicker();
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::Downloads);
        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                init.Initialize(hwnd);
        }
        auto folder = picker.PickSingleFolderAsync().get();
        if (folder)
        {
            OutputDir(folder.Path());
            ApplySettings();
            m_statusMessage = L"Папка загрузок обновлена";
            RaisePropertyChanged(L"StatusMessage");
        }
    }

    void SettingsViewModel::OnSave()
    {
        ApplySettings();
        m_statusMessage = L"Настройки сохранены";
        RaisePropertyChanged(L"StatusMessage");
    }

    void SettingsViewModel::OnImportCookies()
    {
        auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
        picker.FileTypeFilter().Append(L".txt");
        picker.FileTypeFilter().Append(L".json");
        picker.FileTypeFilter().Append(L".sqlite");
        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                init.Initialize(hwnd);
        }
        auto file = picker.PickSingleFileAsync().get();
        if (!file)
            return;

        bool ok = false;
        auto path = std::wstring(file.Path());
        std::wifstream in(path);
        if (in.is_open())
        {
            std::wstringstream buf;
            buf << in.rdbuf();
            std::wstring content = buf.str();
            if (content.find(L'{') != std::wstring::npos &&
                content.find(L"\"cookies\"") != std::wstring::npos)
                ok = m_cookieService->ImportFromFile(path, Services::CookieService::CookieFormat::JSON);
            else
                ok = m_cookieService->ImportFromFile(path, Services::CookieService::CookieFormat::Netscape);
        }

        if (ok)
        {
            m_statusMessage = L"Куки импортированы из файла";
        }
        else
        {
            m_statusMessage = L"Не удалось импортировать куки";
        }
        RaisePropertyChanged(L"StatusMessage");
    }

    void SettingsViewModel::OnImportCookiesFromBrowser()
    {
        auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::ComputerFolder);
        picker.FileTypeFilter().Append(L".sqlite");
        HWND hwnd = GetActiveWindow();
        if (hwnd)
        {
            if (auto init = picker.try_as<winrt::Windows::Storage::Pickers::IInitializeWithWindow>())
                init.Initialize(hwnd);
        }
        auto file = picker.PickSingleFileAsync().get();
        if (file)
        {
            bool ok = m_cookieService->ImportFromFile(
                std::wstring(file.Path()), Services::CookieService::CookieFormat::Netscape);
            m_statusMessage = ok ? L"Куки импортированы из браузера" : L"Не удалось импортировать куки";
            RaisePropertyChanged(L"StatusMessage");
        }
    }

    void SettingsViewModel::OnCheckUpdates()
    {
        m_ytdlpService->SetYtDlpPath(std::wstring(m_ytDlpPath));
        auto self = get_strong();
        m_ytdlpService->SetLogCallback([this, self](const std::string& line, int)
        {
            RunOnUI([this, line]()
            {
                std::wstring msg = L"Обновление: " + winrt::to_hstring(line);
                if (msg.size() > 200) msg = msg.substr(0, 200);
                m_statusMessage = msg;
                RaisePropertyChanged(L"StatusMessage");
            });
        });
        m_ytdlpService->CheckForUpdates();
        m_statusMessage = L"Проверка обновлений...";
        RaisePropertyChanged(L"StatusMessage");
    }

    void SettingsViewModel::OnClearCookies()
    {
        m_cookieService->ClearCookies();
        m_statusMessage = L"Куки очищены";
        RaisePropertyChanged(L"StatusMessage");
    }
}
