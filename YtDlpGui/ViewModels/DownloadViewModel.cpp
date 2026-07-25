#include "pch.h"
#include "DownloadViewModel.h"
#include <sstream>
#include <filesystem>

namespace winrt::YtDlpGui::ViewModels
{
    DownloadViewModel::DownloadViewModel()
    {
        m_ytdlpService = std::make_shared<Services::YtDlpService>();
        m_cookieService = std::make_shared<Services::CookieService>();
        m_settingsService = std::make_shared<Services::SettingsService>();
        m_historyDatabase = std::make_shared<Services::HistoryDatabase>();
        m_historyDatabase->Initialize();

        m_analyzeCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnAnalyze(); });
        m_downloadCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnDownload(); },
            [this](auto&&) -> bool { return m_hasVideoInfo && !m_isDownloading && !m_isAnalyzing; });
        m_cancelCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnCancel(); },
            [this](auto&&) -> bool { return m_isDownloading; });
        m_pasteCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnPasteFromClipboard(); });
        m_openOutputDirCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnOpenOutputDir(); });
        m_clearLogCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnClearLog(); });
        m_openCookieDialogCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnOpenCookieDialog(); });
        m_pasteCookiesCommand = winrt::make<RelayCommand>(
            [this](auto&&) { OnPasteCookies(); });
    }

    void DownloadViewModel::Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher)
    {
        SetDispatcher(dispatcher);
        m_outputDir = winrt::to_hstring(m_settingsService->GetDataPath() + L"downloads");
        std::error_code ec;
        std::filesystem::create_directories(m_settingsService->GetDataPath() + L"downloads", ec);
    }

    void DownloadViewModel::Url(winrt::hstring const& value)
    {
        if (m_url != value)
        {
            m_url = value;
            RaisePropertyChanged(L"Url");
        }
    }

    void DownloadViewModel::Title(winrt::hstring const& value)
    {
        if (m_title != value)
        {
            m_title = value;
            RaisePropertyChanged(L"Title");
        }
    }

    void DownloadViewModel::Uploader(winrt::hstring const& value)
    {
        if (m_uploader != value)
        {
            m_uploader = value;
            RaisePropertyChanged(L"Uploader");
        }
    }

    void DownloadViewModel::ThumbnailUrl(winrt::hstring const& value)
    {
        if (m_thumbnailUrl != value)
        {
            m_thumbnailUrl = value;
            RaisePropertyChanged(L"ThumbnailUrl");
        }
    }

    void DownloadViewModel::VideoCodec(winrt::hstring const& value)
    {
        if (m_videoCodec != value)
        {
            m_videoCodec = value;
            RaisePropertyChanged(L"VideoCodec");
        }
    }

    void DownloadViewModel::AudioCodec(winrt::hstring const& value)
    {
        if (m_audioCodec != value)
        {
            m_audioCodec = value;
            RaisePropertyChanged(L"AudioCodec");
        }
    }

    void DownloadViewModel::AudioBitrate(winrt::hstring const& value)
    {
        if (m_audioBitrate != value)
        {
            m_audioBitrate = value;
            RaisePropertyChanged(L"AudioBitrate");
        }
    }

    void DownloadViewModel::Resolution(winrt::hstring const& value)
    {
        if (m_resolution != value)
        {
            m_resolution = value;
            RaisePropertyChanged(L"Resolution");
        }
    }

    void DownloadViewModel::OutputDir(winrt::hstring const& value)
    {
        if (m_outputDir != value)
        {
            m_outputDir = value;
            RaisePropertyChanged(L"OutputDir");
        }
    }

    void DownloadViewModel::FileNameTemplate(winrt::hstring const& value)
    {
        if (m_fileNameTemplate != value)
        {
            m_fileNameTemplate = value;
            RaisePropertyChanged(L"FileNameTemplate");
        }
    }

    void DownloadViewModel::LogText(winrt::hstring const& value)
    {
        m_logText = value;
        RaisePropertyChanged(L"LogText");
    }

    void DownloadViewModel::AdvancedFlags(winrt::hstring const& value)
    {
        if (m_advancedFlags != value)
        {
            m_advancedFlags = value;
            RaisePropertyChanged(L"AdvancedFlags");
        }
    }

    void DownloadViewModel::StatusText(winrt::hstring const& value)
    {
        if (m_statusText != value)
        {
            m_statusText = value;
            RaisePropertyChanged(L"StatusText");
        }
    }

    void DownloadViewModel::AudioOnly(bool value)
    {
        if (m_audioOnly != value)
        {
            m_audioOnly = value;
            RaisePropertyChanged(L"AudioOnly");
            if (value) VideoOnly(false);
        }
    }

    void DownloadViewModel::VideoOnly(bool value)
    {
        if (m_videoOnly != value)
        {
            m_videoOnly = value;
            RaisePropertyChanged(L"VideoOnly");
            if (value) AudioOnly(false);
        }
    }

    void DownloadViewModel::SeparateAudio(bool value)
    {
        if (m_separateAudio != value)
        {
            m_separateAudio = value;
            RaisePropertyChanged(L"SeparateAudio");
        }
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>
    DownloadViewModel::AvailableCodecs() const
    {
        if (m_availableCodecs) return m_availableCodecs;
        auto vec = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
        vec.Append(winrt::box_value(L"best"));
        vec.Append(winrt::box_value(L"H.264 (AVC)"));
        vec.Append(winrt::box_value(L"H.265 (HEVC)"));
        vec.Append(winrt::box_value(L"VP9"));
        vec.Append(winrt::box_value(L"AV1"));
        m_availableCodecs = vec;
        return m_availableCodecs;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>
    DownloadViewModel::AvailableResolutions() const
    {
        if (m_availableResolutions) return m_availableResolutions;
        auto vec = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
        vec.Append(winrt::box_value(L"best"));
        vec.Append(winrt::box_value(L"8K (4320p)"));
        vec.Append(winrt::box_value(L"4K (2160p)"));
        vec.Append(winrt::box_value(L"1440p"));
        vec.Append(winrt::box_value(L"1080p"));
        vec.Append(winrt::box_value(L"720p"));
        vec.Append(winrt::box_value(L"480p"));
        vec.Append(winrt::box_value(L"360p"));
        vec.Append(winrt::box_value(L"240p"));
        vec.Append(winrt::box_value(L"144p"));
        m_availableResolutions = vec;
        return m_availableResolutions;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>
    DownloadViewModel::AvailableAudioCodecs() const
    {
        if (m_availableAudioCodecs) return m_availableAudioCodecs;
        auto vec = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
        vec.Append(winrt::box_value(L"best"));
        vec.Append(winrt::box_value(L"AAC"));
        vec.Append(winrt::box_value(L"MP3"));
        vec.Append(winrt::box_value(L"Opus"));
        vec.Append(winrt::box_value(L"FLAC"));
        m_availableAudioCodecs = vec;
        return m_availableAudioCodecs;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>
    DownloadViewModel::AvailableBitrates() const
    {
        if (m_availableBitrates) return m_availableBitrates;
        auto vec = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
        vec.Append(winrt::box_value(L"128"));
        vec.Append(winrt::box_value(L"192"));
        vec.Append(winrt::box_value(L"256"));
        vec.Append(winrt::box_value(L"320"));
        m_availableBitrates = vec;
        return m_availableBitrates;
    }

    void DownloadViewModel::OnAnalyze()
    {
        if (m_url.empty() || m_isAnalyzing)
            return;

        m_cancelRequested = false;
        m_isAnalyzing = true;
        RaisePropertyChanged(L"IsAnalyzing");
        m_hasVideoInfo = false;
        StatusText(L"Анализ...");
        AppendLog(L"Начинаем анализ ссылки: " + std::wstring(m_url), 0);

        auto strong = get_strong();
        m_ytdlpService->SetLogCallback([strong](const std::string& line, int level)
        {
            strong->RunOnUI([strong, line, level]()
            {
                strong->AppendLog(winrt::to_hstring(line), level);
            });
        });

        std::wstring url = std::wstring(m_url);
        std::wstring args = L"--dump-json --no-warnings --no-playlist " + Services::ProcessRunner::QuoteArg(url);
        if (m_cookieService->HasCookies())
        {
            args += L" --cookies " + Services::ProcessRunner::QuoteArg(m_cookieService->GetCookieFilePathForYtDlp());
        }

        m_processRunner.SetOutputCallback([strong](const std::string& line)
        {
            strong->RunOnUI([strong, line]()
            {
                try
                {
                    strong->ProcessAnalysisResult(line);
                }
                catch (...) {}
            });
        });

        m_processRunner.RunAsync(L"yt-dlp.exe", args,
            [strong](int exitCode)
            {
                strong->RunOnUI([strong, exitCode]()
                {
                    strong->m_isAnalyzing = false;
                    strong->RaisePropertyChanged(L"IsAnalyzing");
                    if (exitCode == 0)
                    {
                        strong->StatusText(L"Анализ завершён");
                        strong->AppendLog(L"Анализ успешно завершён", 1);
                    }
                    else
                    {
                        strong->StatusText(L"Ошибка анализа");
                        strong->AppendLog(L"Ошибка при анализе (код: " + std::to_wstring(exitCode) + L")", 2);
                    }
                    auto cmd = strong->m_downloadCommand.as<RelayCommand>();
                    cmd->RaiseCanExecuteChanged();
                });
            });
    }

    void DownloadViewModel::OnDownload()
    {
        if (!m_hasVideoInfo || m_isDownloading)
            return;

        m_cancelRequested = false;
        m_isDownloading = true;
        m_progressValue = 0;
        StatusText(L"Загрузка...");
        AppendLog(L"Начинаем загрузку...", 0);

        m_downloadStarted(nullptr, nullptr);

        std::wstring outputTemplate = BuildOutputPath() + L"\\" + std::wstring(m_fileNameTemplate);
        std::wstring formatStr = GetFormatString();

        std::wstring args;
        args += L" --newline --no-warnings";
        args += L" -o " + Services::ProcessRunner::QuoteArg(outputTemplate);
        args += L" -f " + Services::ProcessRunner::QuoteArg(formatStr);
        if (m_cookieService->HasCookies())
            args += L" --cookies " + Services::ProcessRunner::QuoteArg(m_cookieService->GetCookieFilePathForYtDlp());
        if (m_separateAudio)
            args += L" -x --audio-format best";
        if (!m_advancedFlags.empty())
            args += L" " + std::wstring(m_advancedFlags);
        args += L" " + Services::ProcessRunner::QuoteArg(std::wstring(m_url));

        auto strong2 = get_strong();
        m_processRunner.SetOutputCallback([strong2](const std::string& line)
        {
            strong2->RunOnUI([strong2, line]()
            {
                if (line.find("[download]") != std::string::npos)
                {
                    auto pos = line.find("%");
                    if (pos != std::string::npos)
                    {
                        auto numStr = line.substr(line.find_last_of(' ', pos) + 1, pos - line.find_last_of(' ', pos) - 1);
                        try
                        {
                            double percent = std::stod(numStr);
                            strong2->m_progressValue = percent;
                            strong2->RaisePropertyChanged(L"ProgressValue");
                        }
                        catch (...) {}
                    }
                    if (line.find("Destination:") != std::string::npos)
                    {
                        auto dest = line.substr(line.find("Destination:") + 13);
                        strong2->m_currentFileText = winrt::to_hstring(dest);
                        strong2->RaisePropertyChanged(L"CurrentFileText");
                    }
                }
                strong2->AppendLog(winrt::to_hstring(line), 0);
            });
        });

        m_processRunner.RunAsync(L"yt-dlp.exe", args,
            [strong2](int exitCode)
            {
                strong2->RunOnUI([strong2, exitCode]()
                {
                    strong2->m_isDownloading = false;
                    strong2->m_progressValue = exitCode == 0 ? 100 : strong2->m_progressValue;
                    strong2->RaisePropertyChanged(L"ProgressValue");

                    if (exitCode == 0)
                    {
                        strong2->StatusText(L"Загрузка завершена");
                        strong2->AppendLog(L"Загрузка успешно завершена!", 1);
                        strong2->RecordHistory(true, L"");
                        strong2->m_downloadCompleted(nullptr, true);
                    }
                    else if (strong2->m_cancelRequested)
                    {
                        strong2->StatusText(L"Отменено");
                        strong2->AppendLog(L"Загрузка отменена пользователем", 2);
                        strong2->RecordHistoryCancelled();
                        strong2->m_downloadCompleted(nullptr, false);
                    }
                    else
                    {
                        strong2->StatusText(L"Ошибка загрузки");
                        strong2->AppendLog(L"Ошибка при загрузке (код: " + std::to_wstring(exitCode) + L")", 2);
                        strong2->RecordHistory(false, L"Код возврата: " + std::to_wstring(exitCode));
                        strong2->m_downloadCompleted(nullptr, false);
                    }
                    auto cmd = strong2->m_downloadCommand.as<RelayCommand>();
                    cmd->RaiseCanExecuteChanged();
                    auto cancelCmd = strong2->m_cancelCommand.as<RelayCommand>();
                    cancelCmd->RaiseCanExecuteChanged();
                });
            });

        auto cmd = m_downloadCommand.as<RelayCommand>();
        cmd->RaiseCanExecuteChanged();
        auto cancelCmd = m_cancelCommand.as<RelayCommand>();
        cancelCmd->RaiseCanExecuteChanged();
    }

    void DownloadViewModel::OnCancel()
    {
        m_cancelRequested = true;
        m_processRunner.Cancel();
        StatusText(L"Отменено");
        AppendLog(L"Загрузка отменена пользователем", 2);
        RaisePropertyChanged(L"IsDownloading");
        auto cmd = m_downloadCommand.as<RelayCommand>();
        cmd->RaiseCanExecuteChanged();
        auto cancelCmd = m_cancelCommand.as<RelayCommand>();
        cancelCmd->RaiseCanExecuteChanged();
    }

    void DownloadViewModel::OnPasteFromClipboard()
    {
        try
        {
            auto dataPackage = winrt::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();
            if (dataPackage.Contains(winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text()))
            {
                auto text = dataPackage.GetTextAsync().get();
                Url(text);
            }
        }
        catch (...) {}
    }

    void DownloadViewModel::OnOpenOutputDir()
    {
        auto result = reinterpret_cast<INT_PTR>(ShellExecuteW(nullptr, L"open", std::wstring(m_outputDir).c_str(), nullptr, nullptr, SW_SHOW));
        if (result <= 32)
        {
            StatusText(L"Не удалось открыть папку");
            AppendLog(L"Ошибка открытия папки: " + std::wstring(m_outputDir), 2);
        }
    }

    void DownloadViewModel::OnClearLog()
    {
        ClearLog();
    }

    void DownloadViewModel::OnOpenCookieDialog()
    {
        m_showCookieDialog(nullptr, nullptr);
    }

    void DownloadViewModel::OnPasteCookies()
    {
        try
        {
            auto dataPackage = winrt::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();
            if (dataPackage.Contains(winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text()))
            {
                auto text = dataPackage.GetTextAsync().get();
                if (m_cookieService->ImportFromClipboard(std::wstring(text)))
                {
                    m_ytdlpService->SetCookies(m_cookieService->GetCookieFilePathForYtDlp());
                    AppendLog(L"Куки успешно импортированы из буфера обмена", 1);
                    StatusText(L"Куки импортированы");
                }
                else
                {
                    AppendLog(L"Не удалось распознать формат кук в буфере обмена", 2);
                    StatusText(L"Ошибка импорта кук");
                }
            }
        }
        catch (...) {}
    }

    void DownloadViewModel::ProcessAnalysisResult(const std::string& json)
    {
        m_currentVideoInfo = m_ytdlpService->ParseVideoInfo(json);
        m_hasVideoInfo = true;
        m_isPlaylist = false;

        Title(m_currentVideoInfo.Title);
        Uploader(m_currentVideoInfo.Uploader);
        ThumbnailUrl(m_currentVideoInfo.ThumbnailUrl);

        RaisePropertyChanged(L"HasVideoInfo");
        RaisePropertyChanged(L"IsPlaylist");

        auto cmd = m_downloadCommand.as<RelayCommand>();
        cmd->RaiseCanExecuteChanged();
    }

    void DownloadViewModel::RecordHistory(bool success, const std::wstring& error)
    {
        if (!m_historyDatabase)
            return;
        Models::HistoryEntryData entry;
        entry.Url = m_url;
        entry.Title = m_title.empty() ? m_url : m_title;
        entry.Uploader = m_uploader;
        entry.OutputDir = m_outputDir;
        entry.FileName = m_fileNameTemplate;
        entry.Platform = m_currentVideoInfo.Platform;
        entry.Format = m_videoCodec + L"+" + m_audioCodec;
        entry.Quality = m_resolution;
        entry.Duration = m_currentVideoInfo.Duration;
        entry.ThumbnailUrl = m_thumbnailUrl;
        entry.Status = success ? Models::HistoryStatus::Completed : Models::HistoryStatus::Failed;
        entry.DateCompleted = winrt::to_hstring(
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        entry.ErrorMessage = error;
        m_historyDatabase->AddEntry(entry);
    }

    void DownloadViewModel::RecordHistoryCancelled()
    {
        if (!m_historyDatabase)
            return;
        Models::HistoryEntryData entry;
        entry.Url = m_url;
        entry.Title = m_title.empty() ? m_url : m_title;
        entry.Uploader = m_uploader;
        entry.OutputDir = m_outputDir;
        entry.FileName = m_fileNameTemplate;
        entry.Platform = m_currentVideoInfo.Platform;
        entry.Format = m_videoCodec + L"+" + m_audioCodec;
        entry.Quality = m_resolution;
        entry.Duration = m_currentVideoInfo.Duration;
        entry.ThumbnailUrl = m_thumbnailUrl;
        entry.Status = Models::HistoryStatus::Cancelled;
        entry.DateCompleted = winrt::to_hstring(
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        entry.ErrorMessage = L"Отменено пользователем";
        m_historyDatabase->AddEntry(entry);
        m_cancelRequested = false;
    }

    std::wstring DownloadViewModel::BuildOutputPath()
    {
        return std::wstring(m_outputDir);
    }

    std::wstring DownloadViewModel::GetFormatString()
    {
        return m_ytdlpService->BuildFormatString(
            std::wstring(m_videoCodec),
            std::wstring(m_resolution),
            std::wstring(m_audioCodec),
            std::wstring(m_audioBitrate),
            m_audioOnly,
            m_videoOnly);
    }

    void DownloadViewModel::AppendLog(const std::wstring& message, int level)
    {
        std::wstring prefix;
        switch (level)
        {
        case 1: prefix = L"[OK] "; break;
        case 2: prefix = L"[ERR] "; break;
        default: prefix = L"[INFO] "; break;
        }

        std::wstring newLine = prefix + message + L"\n";
        m_logText = m_logText + newLine;
        const size_t MaxLog = 200000;
        if (m_logText.size() > MaxLog)
            m_logText = m_logText.substr(m_logText.size() - MaxLog);
        RaisePropertyChanged(L"LogText");
    }

    void DownloadViewModel::ClearLog()
    {
        m_logText = L"";
        RaisePropertyChanged(L"LogText");
    }

    void DownloadViewModel::UpdateProgress(double percent, const std::wstring& speed, const std::wstring& eta)
    {
        m_progressValue = percent;
        RaisePropertyChanged(L"ProgressValue");
        StatusText(L"Загрузка: " + std::to_wstring(static_cast<int>(percent)) + L"% " + speed + L" ETA: " + eta);
    }
}
