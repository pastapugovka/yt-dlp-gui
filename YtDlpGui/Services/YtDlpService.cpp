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
        std::wstring fmt;
        fmt.reserve(128);

        if (audioOnly)
        {
            fmt = L"bestaudio";
            if (audioCodec != L"best")
            {
                fmt += L"[acodec~=\"";
                fmt += audioCodec;
                fmt += L"\"]";
            }
            if (!audioBitrate.empty())
            {
                fmt += L"[abr~=";
                fmt += audioBitrate;
                fmt += L"]";
            }
        }
        else if (videoOnly)
        {
            fmt = L"bestvideo";
            if (videoCodec != L"best")
            {
                fmt += L"[vcodec~=\"";
                fmt += videoCodec;
                fmt += L"\"]";
            }
            if (resolution != L"best")
            {
                fmt += L"[height<=";
                fmt += resolution;
                fmt += L"]";
            }
        }
        else
        {
            if (videoCodec != L"best" || resolution != L"best")
            {
                fmt = L"bestvideo";
                if (videoCodec != L"best")
                {
                    fmt += L"[vcodec~=\"";
                    fmt += videoCodec;
                    fmt += L"\"]";
                }
                if (resolution != L"best")
                {
                    fmt += L"[height<=";
                    fmt += resolution;
                    fmt += L"]";
                }
                fmt += L"+bestaudio";
                if (audioCodec != L"best")
                {
                    fmt += L"[acodec~=\"";
                    fmt += audioCodec;
                    fmt += L"\"]";
                }
            }
            else
            {
                fmt = L"bestvideo+bestaudio/best";
            }
        }

        return fmt;
    }

    std::wstring YtDlpService::BuildCommonArgs(const AppSettings& settings)
    {
        std::wstring args;
        args.reserve(256);
        args = L" --newline --no-warnings";

        if (!settings.Proxy.empty())
        {
            args += L" --proxy ";
            args += ProcessRunner::QuoteArg(settings.Proxy);
        }
        if (!settings.UserAgent.empty())
        {
            args += L" --user-agent ";
            args += ProcessRunner::QuoteArg(settings.UserAgent);
        }
        if (!settings.FfmpegPath.empty())
        {
            args += L" --ffmpeg-location ";
            args += ProcessRunner::QuoteArg(settings.FfmpegPath);
        }
        if (settings.EmbedThumbnail)
            args += L" --embed-thumbnail";
        if (settings.EmbedSubtitles)
            args += L" --embed-subs";
        if (settings.WriteMetadata)
            args += L" --add-metadata";
        if (settings.DownloadSubtitles)
        {
            args += L" --write-subs --write-auto-subs --sub-langs ";
            args += ProcessRunner::QuoteArg(settings.PreferredLanguage);
        }
        if (!settings.AdvancedFlags.empty())
        {
            args += L" ";
            args += settings.AdvancedFlags;
        }

        return args;
    }

    Models::VideoInfo YtDlpService::ParseVideoInfo(const std::string& json)
    {
        Models::VideoInfo info;

        try
        {
            auto jsonObj = winrt::Windows::Data::Json::JsonObject::Parse(winrt::to_hstring(json));

            if (auto val = jsonObj.Lookup(L"title"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                info.Title = val.GetString();
            if (auto val = jsonObj.Lookup(L"uploader"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                info.Uploader = val.GetString();
            if (auto val = jsonObj.Lookup(L"thumbnail"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                info.ThumbnailUrl = val.GetString();
            if (auto val = jsonObj.Lookup(L"description"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                info.Description = val.GetString();
            if (auto val = jsonObj.Lookup(L"duration"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                info.Duration = val.GetNumber();
            if (auto val = jsonObj.Lookup(L"view_count"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                info.ViewCount = val.GetNumber();
            if (auto val = jsonObj.Lookup(L"like_count"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                info.LikeCount = val.GetNumber();
            if (auto val = jsonObj.Lookup(L"is_live"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::Boolean)
                info.IsLive = val.GetBoolean();
            if (auto val = jsonObj.Lookup(L"id"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                info.Id = val.GetString();
            if (auto val = jsonObj.Lookup(L"webpage_url"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                info.WebpageUrl = val.GetString();
            if (auto val = jsonObj.Lookup(L"upload_date"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                info.UploadDate = val.GetString();

            info.JsonData = winrt::to_hstring(json);

            std::string platform;
            if (auto val = jsonObj.Lookup(L"extractor_key"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
            {
                auto extractor = winrt::to_string(val.GetString());
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

            if (auto val = jsonObj.Lookup(L"formats"); val.ValueType() == winrt::Windows::Data::Json::JsonValueType::Array)
            {
                auto formatsArray = val.GetArray();
                info.Formats.reserve(formatsArray.Size());
                for (auto const& fmt : formatsArray)
                {
                    auto fmtObj = fmt.GetObject();
                    Models::FormatInfo fi;
                    if (auto v = fmtObj.Lookup(L"format_id"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                        fi.FormatId = v.GetString();
                    if (auto v = fmtObj.Lookup(L"ext"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                        fi.Extension = v.GetString();
                    if (auto v = fmtObj.Lookup(L"resolution"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                        fi.Resolution = v.GetString();
                    if (auto v = fmtObj.Lookup(L"vcodec"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String && v.GetString() != L"none")
                    {
                        fi.VideoCodec = v.GetString();
                        fi.HasVideo = true;
                    }
                    if (auto v = fmtObj.Lookup(L"acodec"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String && v.GetString() != L"none")
                    {
                        fi.AudioCodec = v.GetString();
                        fi.HasAudio = true;
                    }
                    if (auto v = fmtObj.Lookup(L"filesize"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                        fi.FileSize = v.GetNumber();
                    if (auto v = fmtObj.Lookup(L"tbr"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                        fi.Bitrate = v.GetNumber();
                    if (auto v = fmtObj.Lookup(L"fps"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                        fi.FPS = static_cast<int>(v.GetNumber());
                    if (auto v = fmtObj.Lookup(L"format_note"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                        fi.FormatNote = v.GetString();
                    if (auto v = fmtObj.Lookup(L"quality"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                        fi.QualityNote = v.GetString();
                    info.Formats.push_back(std::move(fi));
                }
            }
        }
        catch (const winrt::hresult_error& ex)
        {
            if (m_logCallback) m_logCallback(winrt::to_string(ex.message()), 2);
        }
        catch (const std::exception& e)
        {
            if (m_logCallback) m_logCallback(std::string("Error parsing video info: ") + e.what(), 2);
        }
        catch (...)
        {
            if (m_logCallback) m_logCallback("Unknown error parsing video info", 2);
        }

        return info;
    }

    std::vector<Models::PlaylistItem> YtDlpService::ParsePlaylistEntries(const std::string& json)
    {
        std::vector<Models::PlaylistItem> items;
        try
        {
            auto jsonArray = winrt::Windows::Data::Json::JsonArray::Parse(winrt::to_hstring(json));
            items.reserve(jsonArray.Size());
            for (auto const& entry : jsonArray)
            {
                auto obj = entry.GetObject();
                Models::PlaylistItem item;
                if (auto v = obj.Lookup(L"url"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                    item.Url = v.GetString();
                if (auto v = obj.Lookup(L"title"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                    item.Title = v.GetString();
                if (auto v = obj.Lookup(L"uploader"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                    item.Uploader = v.GetString();
                if (auto v = obj.Lookup(L"duration"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                    item.Duration = v.GetNumber();
                if (auto v = obj.Lookup(L"_playlist_index"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::Number)
                    item.Index = static_cast<int>(v.GetNumber());
                if (auto v = obj.Lookup(L"thumbnail"); v.ValueType() == winrt::Windows::Data::Json::JsonValueType::String)
                    item.ThumbnailUrl = v.GetString();
                items.push_back(std::move(item));
            }
        }
        catch (const winrt::hresult_error& ex)
        {
            if (m_logCallback) m_logCallback(winrt::to_string(ex.message()), 2);
        }
        catch (const std::exception& e)
        {
            if (m_logCallback) m_logCallback(std::string("Error parsing playlist entries: ") + e.what(), 2);
        }
        catch (...)
        {
            if (m_logCallback) m_logCallback("Unknown error parsing playlist entries", 2);
        }
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
