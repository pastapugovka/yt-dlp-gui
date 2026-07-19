<div align="center">

# yt-dlp-gui

**yt-dlp-gui** — a graphical interface (WinUI 3, C++/WinRT) for [yt-dlp](https://github.com/yt-dlp/yt-dlp).

English / [Русский](README_RU.md) / [简体中文](README_CN.md) / [فارسی](README_FA.md)

[![Version](https://img.shields.io/badge/release-v%201.0.b-green.svg)](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)
![License](https://img.shields.io/badge/license-MIT-green.svg)

<div align="center">
  <img src="https://skillicons.dev/icons?i=cpp" height="40" alt="cplusplus logo"  />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=cs" height="40" alt="csharp logo"  />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=windows" height="40" alt="windows logo"  />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=visualstudio" height="40" alt="visualstudio logo"  />
</div>

</div>

## Features
- Download individual videos and entire playlists
- Select a range of playlist items (with resume support)
- Configure download parameters: folder, resolution, codec, bitrate, extra flags
- Automatic format selection when the video does not match your settings
- Audio-only / video-only / separate audio track
- Cookie import (Netscape/JSON file, clipboard, browser) for restricted content
- Download history with filters, CSV/JSON export, and re-download
- Built-in console to pass commands directly to yt-dlp
- Dark/light theme and interface language (ru/en/uk)
- In-app yt-dlp update check

## Requirements
- Windows 10/11 (build 17763 and later)
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — path set in settings (or place `yt-dlp.exe` next to the app)
- [FFmpeg](https://ffmpeg.org/) — path set in settings (needed for merge/transcode)

## Downloads
Latest release: **[v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)**

- `YtDlpGui.msix` — installer package (trust the `YtDlpGui_TemporaryKey.pfx` certificate on first run)
- Portable EXE — the `AppX` folder next to the executable

Source code: [github.com/pastapugovka/yt-dlp-gui](https://github.com/pastapugovka/yt-dlp-gui)

## Installation
1. Download the latest release (`YtDlpGui.msix` or portable EXE)
2. On first launch, set the paths to `yt-dlp.exe` and `ffmpeg.exe` on the Settings page
3. Done — you can start downloading

## Downloading
1. Paste a video or playlist URL on the Download page
2. Optionally set resolution, codec, audio, and extra flags
3. For playlists, open the playlist dialog and choose range/mode
4. Watch real-time progress
5. Files are saved to the chosen folder (default: app download folder)

## Settings
- Path to yt-dlp and ffmpeg
- Download folder
- Proxy and User-Agent
- Cookie import / clear
- Filename template, max parallel downloads
- Embed thumbnail / subtitles / metadata
- Theme (light/dark/system) and interface language
- Auto-update yt-dlp

Settings are stored in `%LocalAppData%\YtDlpGui\config\settings.json`.

## Cookies
The built-in cookie editor helps access restricted content:
- Import a file (.txt Netscape or .json)
- Paste text from the clipboard
- Import directly from a browser (Chrome, Edge, Firefox, Opera)

> Note: cookies are stored locally without encryption.

## Supported Services
Supports all sites and services natively supported by [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme). The full, always up-to-date list of supported extractors is available in the [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md) document.

<div align="center" style="background:#000;padding:12px;border-radius:8px">
  <img src="Social%20Media%20Icons%20%26%20Logos%20(Community)/Platform=YouTube%2C%20Color=Negative.png" height="32" alt="youtube"  />
  <img width="8" />
  <img src="Social%20Media%20Icons%20%26%20Logos%20(Community)/Platform=Twitch%2C%20Color=Negative.png" height="32" alt="twitch"  />
  <img width="8" />
  <img src="Social%20Media%20Icons%20%26%20Logos%20(Community)/Platform=TikTok%2C%20Color=Negative.png" height="32" alt="tiktok"  />
  <img width="8" />
  <img src="Social%20Media%20Icons%20%26%20Logos%20(Community)/Platform=Instagram%2C%20Color=Negative.png" height="32" alt="instagram"  />
  <img width="8" />
  <img src="Social%20Media%20Icons%20%26%20Logos%20(Community)/Platform=VK%2C%20Color=Negative.png" height="32" alt="vk"  />
</div>

> Examples: YouTube, Twitch, TikTok, Instagram, Rutube, VK Video, Vimeo and many more.

## Building from Source
A detailed step-by-step guide with troubleshooting is in [BUILD.md](BUILD.md#en).

### Requirements
- Visual Studio 2022 or later
- "Desktop development with C++" workload and Windows App SDK
- Windows SDK 10.0.26100.0

### Compilation
1. Clone the repo: `git clone https://github.com/pastapugovka/yt-dlp-gui.git`
2. Run `nuget restore` (packages `Microsoft.Windows.CppWinRT` and `Microsoft.WindowsAppSDK`)
3. Open `YtDlpGui.sln`
4. Select `Release | x64`
5. Build the solution (Ctrl+Shift+B)

## License
MIT — free to use and modify. Author: [pastapugovka](https://github.com/pastapugovka).

## Acknowledgments
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — the backbone of this tool
- [FFmpeg](https://ffmpeg.org/) — for media processing
- [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/) — the UI framework
