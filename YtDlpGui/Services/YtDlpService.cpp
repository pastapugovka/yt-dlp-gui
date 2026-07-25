#include "pch.h"
#include "YtDlpService.h"
#include <sstream>
#include <regex>

namespace winrt::YtDlpGui::Services
{
    YtDlpService::YtDlpService()
        : m_runner(std::make_unique<ProcessRunner>())
    {
    }

    YtDlpService::~YtDlpService()
    {
        CancelCurrentOperation();
    }

    std::wstring YtDlpService::GetExecutablePath()
    {
        wchar_t exePath[MAX_PATH];
        DWORD len = GetModuleFileNameW(nullptr, exePath, MAX_PATH);
        if (len == 0 || len >= MAX_PATH)
            return L".\\";
        std::wstring path(exePath);
        auto pos = path.find_last_of(L"\\");
        if (pos != std::wstring::npos)
            path = path.substr(0, pos + 1);
        return path;
    }

    void YtDlpService::AnalyzeUrl(const std::wstring& url)
    {
        if (m_runner->IsRunning())
            m_runner->Cancel();

        m_runner->SetOutputCallback([this](const std::string& line)
        {
            if (m_logCallback)
                m_logCallback(line, 0);
        });

        std::wstring args = L"--dump-json --no-warnings";
        args += L" --no-playlist";
        args += L" " + ProcessRunner::QuoteArg(url);

        m_runner->RunAsync(m_ytdlpPath, args, nullptr);
    }

    void YtDlpService::DownloadVideo(const std::wstring& url, const std::wstring& outputTemplate,
                                      const std::wstring& formatStr, const std::wstring& extraArgs)
    {
        if (m_runner->IsRunning())
            m_runner->Cancel();

        m_runner->SetOutputCallback([this](const std::string& line)
        {
            if (m_logCallback)
                m_logCallback(line, 0);
        });

        std::wstring args;
        args += L" --newline --no-warnings";
        args += L" -o " + ProcessRunner::QuoteArg(outputTemplate);
        args += L" -f " + ProcessRunner::QuoteArg(formatStr);

        if (!m_proxy.empty())
            args += L" --proxy " + ProcessRunner::QuoteArg(m_proxy);
        if (!m_userAgent.empty())
            args += L" --user-agent " + ProcessRunner::QuoteArg(m_userAgent);
        if (!m_cookies.empty())
            args += L" --cookies " + ProcessRunner::QuoteArg(m_cookies);
        if (!m_ffmpegPath.empty())
            args += L" --ffmpeg-location " + ProcessRunner::QuoteArg(m_ffmpegPath);

        args += L" " + extraArgs;
        args += L" " + ProcessRunner::QuoteArg(url);

        m_runner->RunAsync(m_ytdlpPath, args, nullptr);
    }

    void YtDlpService::DownloadPlaylist(const std::wstring& url, const std::wstring& outputTemplate,
                                         const std::wstring& formatStr, int start, int end,
                                         const std::wstring& extraArgs)
    {
        if (m_runner->IsRunning())
            m_runner->Cancel();

        m_runner->SetOutputCallback([this](const std::string& line)
        {
            if (m_logCallback)
                m_logCallback(line, 0);
        });

        std::wstring args;
        args += L" --newline --no-warnings";
        args += L" -o " + ProcessRunner::QuoteArg(outputTemplate);
        args += L" -f " + ProcessRunner::QuoteArg(formatStr);

        if (start > 0 || end > 0)
        {
            std::wostringstream range;
            if (start > 0 && end > 0)
                range << start << L"-" << end;
            else if (start > 0)
                range << start << L"-";
            else if (end > 0)
                range << L"1-" << end;
            args += L" --playlist-items " + ProcessRunner::QuoteArg(range.str());
        }

        if (!m_proxy.empty())
            args += L" --proxy " + ProcessRunner::QuoteArg(m_proxy);
        if (!m_userAgent.empty())
            args += L" --user-agent " + ProcessRunner::QuoteArg(m_userAgent);
        if (!m_cookies.empty())
            args += L" --cookies " + ProcessRunner::QuoteArg(m_cookies);
        if (!m_ffmpegPath.empty())
            args += L" --ffmpeg-location " + ProcessRunner::QuoteArg(m_ffmpegPath);

        args += L" " + extraArgs;
        args += L" " + ProcessRunner::QuoteArg(url);

        m_runner->RunAsync(m_ytdlpPath, args, nullptr);
    }

    void YtDlpService::CancelCurrentOperation()
    {
        if (m_runner)
            m_runner->Cancel();
    }

    std::wstring YtDlpService::BuildFormatString(const std::wstring& videoCodec,
                                                  const std::wstring& resolution,
                                                  const std::wstring& audioCodec,
                                                  const std::wstring& audioBitrate,
                                                  bool audioOnly, bool videoOnly)
    {
        std::wostringstream fmt;

        if (audioOnly)
        {
            fmt << L"bestaudio";
            if (audioCodec != L"best")
                fmt << L"[acodec~=\"" << audioCodec << L"\"]";
            if (!audioBitrate.empty())
                fmt << L"[abr~=" << audioBitrate << L"]";
        }
        else if (videoOnly)
        {
            fmt << L"bestvideo";
            if (videoCodec != L"best")
                fmt << L"[vcodec~=\"" << videoCodec << L"\"]";
            if (resolution != L"best")
                fmt << L"[height<=" << resolution << L"]";
        }
        else
        {
            if (videoCodec != L"best" || resolution != L"best")
            {
                fmt << L"bestvideo";
                if (videoCodec != L"best")
                    fmt << L"[vcodec~=\"" << videoCodec << L"\"]";
                if (resolution != L"best")
                    fmt << L"[height<=" << resolution << L"]";
                fmt << L"+bestaudio";
                if (audioCodec != L"best")
                    fmt << L"[acodec~=\"" << audioCodec << L"\"]";
            }
            else
            {
                fmt << L"bestvideo+bestaudio/best";
            }
        }

        return fmt.str();
    }

    std::wstring YtDlpService::BuildCommonArgs(const AppSettings& settings)
    {
        std::wostringstream args;
        args << L" --newline --no-warnings";

        if (!settings.Proxy.empty())
            args << L" --proxy " << ProcessRunner::QuoteArg(settings.Proxy);
        if (!settings.UserAgent.empty())
            args << L" --user-agent " << ProcessRunner::QuoteArg(settings.UserAgent);
        if (!settings.FfmpegPath.empty())
            args << L" --ffmpeg-location " << ProcessRunner::QuoteArg(settings.FfmpegPath);
        if (settings.EmbedThumbnail)
            args << L" --embed-thumbnail";
        if (settings.EmbedSubtitles)
            args << L" --embed-subs";
        if (settings.WriteMetadata)
            args << L" --add-metadata";
        if (settings.DownloadSubtitles)
            args << L" --write-subs --write-auto-subs --sub-langs " << ProcessRunner::QuoteArg(settings.PreferredLanguage);
        if (!settings.AdvancedFlags.empty())
            args << L" " << settings.AdvancedFlags;

        return args.str();
    }

    Models::VideoInfo YtDlpService::ParseVideoInfo(const std::string& json)
    {
        Models::VideoInfo info;

        try
        {
            auto jsonObj = winrt::Windows::Data::Json::JsonObject::Parse(winrt::to_hstring(json));

            if (jsonObj.HasKey(L"title"))
                info.Title = jsonObj.GetNamedString(L"title");
            if (jsonObj.HasKey(L"uploader"))
                info.Uploader = jsonObj.GetNamedString(L"uploader");
            if (jsonObj.HasKey(L"thumbnail"))
                info.ThumbnailUrl = jsonObj.GetNamedString(L"thumbnail");
            if (jsonObj.HasKey(L"description"))
                info.Description = jsonObj.GetNamedString(L"description");
            if (jsonObj.HasKey(L"duration"))
                info.Duration = jsonObj.GetNamedNumber(L"duration");
            if (jsonObj.HasKey(L"view_count"))
                info.ViewCount = jsonObj.GetNamedNumber(L"view_count");
            if (jsonObj.HasKey(L"like_count"))
                info.LikeCount = jsonObj.GetNamedNumber(L"like_count");
            if (jsonObj.HasKey(L"is_live"))
                info.IsLive = jsonObj.GetNamedBoolean(L"is_live");
            if (jsonObj.HasKey(L"id"))
                info.Id = jsonObj.GetNamedString(L"id");
            if (jsonObj.HasKey(L"webpage_url"))
                info.WebpageUrl = jsonObj.GetNamedString(L"webpage_url");
            if (jsonObj.HasKey(L"upload_date"))
                info.UploadDate = jsonObj.GetNamedString(L"upload_date");

            info.JsonData = winrt::to_hstring(json);

            std::string platform;
            if (jsonObj.HasKey(L"extractor_key"))
            {
                auto extractor = winrt::to_string(jsonObj.GetNamedString(L"extractor_key"));
                if (extractor == "Youtube") platform = "YouTube";
                else if (extractor == "TikTok") platform = "TikTok";
                else if (extractor == "Twitch") platform = "Twitch";
                else if (extractor == "Twitter") platform = "X/Twitter";
                else if (extractor == "Instagram") platform = "Instagram";
                else if (extractor == "VK") platform = "VK";
                else if (extractor == "BiliBili") platform = "Bilibili";
                else platform = extractor;
            }
            else
            {
                platform = "Other";
            }
            info.Platform = winrt::to_hstring(platform);

            if (jsonObj.HasKey(L"formats"))
            {
                auto formatsArray = jsonObj.GetNamedArray(L"formats");
                for (auto const& fmt : formatsArray)
                {
                    auto fmtObj = fmt.GetObject();
                    Models::FormatInfo fi;
                    if (fmtObj.HasKey(L"format_id"))
                        fi.FormatId = fmtObj.GetNamedString(L"format_id");
                    if (fmtObj.HasKey(L"ext"))
                        fi.Extension = fmtObj.GetNamedString(L"ext");
                    if (fmtObj.HasKey(L"resolution"))
                        fi.Resolution = fmtObj.GetNamedString(L"resolution");
                    if (fmtObj.HasKey(L"vcodec") && fmtObj.GetNamedString(L"vcodec") != L"none")
                    {
                        fi.VideoCodec = fmtObj.GetNamedString(L"vcodec");
                        fi.HasVideo = true;
                    }
                    if (fmtObj.HasKey(L"acodec") && fmtObj.GetNamedString(L"acodec") != L"none")
                    {
                        fi.AudioCodec = fmtObj.GetNamedString(L"acodec");
                        fi.HasAudio = true;
                    }
                    if (fmtObj.HasKey(L"filesize") && fmtObj.GetNamedValue(L"filesize").ValueType() !=
                        winrt::Windows::Data::Json::JsonValueType::Null)
                        fi.FileSize = fmtObj.GetNamedNumber(L"filesize");
                    if (fmtObj.HasKey(L"tbr"))
                        fi.Bitrate = fmtObj.GetNamedNumber(L"tbr");
                    if (fmtObj.HasKey(L"fps") && fmtObj.GetNamedValue(L"fps").ValueType() !=
                        winrt::Windows::Data::Json::JsonValueType::Null)
                        fi.FPS = static_cast<int>(fmtObj.GetNamedNumber(L"fps"));
                    if (fmtObj.HasKey(L"format_note"))
                        fi.FormatNote = fmtObj.GetNamedString(L"format_note");
                    if (fmtObj.HasKey(L"quality"))
                        fi.QualityNote = fmtObj.GetNamedString(L"quality");
                    info.Formats.push_back(fi);
                }
            }
        }
        catch (...) {}

        return info;
    }

    std::vector<Models::PlaylistItem> YtDlpService::ParsePlaylistEntries(const std::string& json)
    {
        std::vector<Models::PlaylistItem> items;
        try
        {
            auto jsonArray = winrt::Windows::Data::Json::JsonArray::Parse(winrt::to_hstring(json));
            for (auto const& entry : jsonArray)
            {
                auto obj = entry.GetObject();
                Models::PlaylistItem item;
                if (obj.HasKey(L"url"))
                    item.Url = obj.GetNamedString(L"url");
                if (obj.HasKey(L"title"))
                    item.Title = obj.GetNamedString(L"title");
                if (obj.HasKey(L"uploader"))
                    item.Uploader = obj.GetNamedString(L"uploader");
                if (obj.HasKey(L"duration"))
                    item.Duration = obj.GetNamedNumber(L"duration");
                if (obj.HasKey(L"_playlist_index"))
                    item.Index = static_cast<int>(obj.GetNamedNumber(L"_playlist_index"));
                if (obj.HasKey(L"thumbnail"))
                    item.ThumbnailUrl = obj.GetNamedString(L"thumbnail");
                items.push_back(item);
            }
        }
        catch (...) {}
        return items;
    }

    void YtDlpService::CheckForUpdates()
    {
        if (m_runner->IsRunning())
            return;

        m_runner->SetOutputCallback([this](const std::string& line)
        {
            if (m_logCallback)
                m_logCallback(line, 0);
        });

        m_runner->RunAsync(m_ytdlpPath, L"-U", nullptr);
    }
}
