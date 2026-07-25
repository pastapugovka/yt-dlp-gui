# yt-dlp-gui Project Documentation

This document provides a comprehensive overview of the yt-dlp-gui project, including its multilingual documentation structure, build instructions, and implementation details.

## Project Overview

### Core Information
- **Repository**: pastapugovka/yt-dlp-gui
- **Homepage**: English README (`README.md`) - primary documentation
- **Technical Stack**: C++/WinRT with WinUI 3 (Windows GUI application)
- **License**: MIT (pastapugovka)
- **Primary Author**: pastapugovka

### Project Purpose
yt-dlp-gui is a graphical user interface for the yt-dlp command-line tool, providing an intuitive desktop application for downloading videos and audio from thousands of supported websites.

## Multilingual Documentation Structure

### README Files
The project includes four language versions of the main documentation:

| Language | File Name | Primary Language | Description |
|----------|-----------|------------------|-------------|
| English | `README.md` | 🇬🇧 English | Homepage and primary documentation |
| Russian | `README_RU.md` | 🇷🇺 Русский | Russian translation with regional services |
| Chinese | `README_CN.md` | 🇨🇳 简体中文 | Chinese translation with regional services |
| Hebrew | `README_HE.md` | 🇮🇱 עברית | Hebrew translation (formerly Persian) |

### README Structure Template

```markdown
<div align="center">

# yt-dlp-gui

**yt-dlp-gui** — description ([en] / [ru] / [cn] / [he])

[![Version](https://img.shields.io/badge/release-v%201.0.b-green.svg)](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)
![License](https://img.shields.io/badge/license-MIT-green.svg)

<div align="center">
  <img src="https://skillicons.dev/icons?i=cs" height="64" alt="csharp logo"  />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=cpp" height="64" alt="cplusplus logo"  />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=windows" height="64" alt="windows logo"  />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=visualstudio" height="64" alt="visualstudio logo"  />
</div>
</div>

## Features
- Feature 1
- Feature 2
- Feature 3

## Supported Services
> Description with regional services

## How to Use
- Step 1
- Step 2
- Step 3
```

### Language Switching
Each README features a language switcher with country flags:

- **🇬🇧 English** (current language - primary)
- **🇷🇺 [Русский](README_RU.md)** (Russian translation)
- **🇨🇳 [简体中文](README_CN.md)** (Chinese translation)
- **🇮🇱 [עברית](README_HE.md)** (Hebrew translation)

## Supported Services Documentation

The `Supported Services` section in each README follows a regional content strategy:

### English (README.md)
> Supports all sites and services natively supported by [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme), including YouTube, Vimeo, Twitch, TikTok, and 2 music services (SoundCloud, Spotify). The full, always up-to-date list of supported extractors is available in the [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md) document.

### Russian (README_RU.md)
> Поддерживаются все сайты и сервисы, которые изначально поддерживаются [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme), включая YouTube, RuTube, VK Видео и TikTok, а также 2 музыкальных сервиса (Яндекс.Музыка, VK Музыка). Полный актуальный список поддерживаемых извлекателей доступен в документе [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md).

### Chinese (README_CN.md)
> 支持 [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme) 原生支持的所有网站和服务，包括 YouTube、哔哩哔哩（Bilibili）、抖音（Douyin）和 TikTok，以及网易云音乐、QQ音乐等音乐服务。完整且最新的提取器列表见 [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md)。

### Hebrew (README_HE.md)
> כל האתרים והשירותים הנתמכים באופן טבעי על ידי [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme), כולל YouTube, Aparat ו-Rubika נתמכים. הרשימה המלאה והעדכנית ביותר של מחלצים נתמכים זמינה במסמך [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md).

### Regional Service Selection Rationale

| Language | Primary Services | Music Services | Geographic Focus |
|----------|------------------|----------------|------------------|
| English | YouTube, Vimeo, Twitch, TikTok | SoundCloud, Spotify | Global |
| Russian | YouTube, RuTube, VK Video, TikTok | Yandex Music, VK Music | Russia/CIS |
| Chinese | YouTube, Bilibili, Douyin, TikTok | NetEase Music, QQ Music | China |
| Hebrew | YouTube, Aparat, Rubika, TikTok | Spotify, Deezer | Israel |

## BUILD.md Documentation

### Language Structure
The `BUILD.md` file contains four language sections with unique anchors for direct navigation:

```markdown
[English](#en) / [Русский](#ru) / [简体中文](#cn) / [עברית](#he)
```

### Section Anchors
- `## English` → `#en` (English)
- `## Русский` → `#ru` (Russian)
- `## 简体中文` → `#cn` (Chinese)
- `## עברית` → `#he` (Hebrew)

### Section Navigation
Each section can be accessed directly using the anchor links:
- English: `#en`
- Russian: `#ru`
- Chinese: `#cn`
- Hebrew: `#he`

## Git Repository Management

### Repository Structure
```
C:\Users\Илья\Documents\yt-dlp-gui
├── YtDlpGui.sln
├── YtDlpGui/              (source code)
├── README.md              (English homepage)
├── README_RU.md           (Russian)
├── README_CN.md           (Chinese)
├── README_HE.md           (Hebrew)
├── BUILD.md               (build instructions)
├── YtDlpGui_TemporaryKey.pfx (MSIX signing)
└── LICENSE               (MIT license)
```

### Files Included in Repository
| File | Purpose |
|------|---------|
| `YtDlpGui.sln` | Visual Studio solution file |
| `YtDlpGui/` | Application source code (C++/WinRT) |
| `README*.md` | Multilingual documentation |
| `BUILD.md` | Build instructions |
| `YtDlpGui_TemporaryKey.pfx` | MSIX certificate |
| `LICENSE` | Project license |

### Files Excluded from Repository
| File/Folder | Reason |
|------------|--------|
| `packages/` | NuGet packages (retrieved via `nuget restore`) |
| `.vs/` | Visual Studio cache |
| `out/`, `x64/`, `ARM64/` | Build artifacts |
| `.nuget/`, `vs*.json` | VS configuration files |
| `Social Media Icons & Logos (Community)/` | Documentation assets (local only) |

### Git History Management
The repository maintains a clean git history with a single initial commit:

- **Initial Commit**: `a2e42b0` - "Initial commit: YtDlpGui WinUI 3 (C++/WinRT)"
- **Current Branch**: `main`
- **Remote Repository**: `https://github.com/pastapugovka/yt-dlp-gui.git`

### Personal Access Token (PAT)
**Important**: The repository uses a Personal Access Token (PAT) for GitHub operations.

- **Update Location**: `https://github.com/settings/tokens`
- **Permissions**: Repository read/write
- **Current PAT**: Previously visible in repository history (should be updated)

## Technical Implementation Details

### Development Environment

#### Prerequisites
- **Operating System**: Windows 10/11 (version 1776 or higher)
- **IDE**: Visual Studio 2022+ (Community or Professional)
- **Workloads**: 
  - Desktop development with C++
  - Windows development with C++ (WinUI 3)
  - Universal Windows Platform
- **SDK**: Windows 10/11 SDK (10.0.26100.0)

#### Runtime Dependencies
- **yt-dlp**: https://github.com/yt-dlp/yt-dlp
- **FFmpeg**: https://ffmpeg.org/

#### Build Process

**Step 1: Clone Repository**
```powershell
git clone https://github.com/pastapugovka/yt-dlp-gui.git
cd yt-dlp-gui
```

**Step 2: Restore NuGet Packages**
```powershell
nuget restore YtDlpGui.sln
```

**Step 3: Visual Studio Setup**
1. Open `YtDlpGui.sln`
2. Select configuration: `Release | x64`
3. Build solution (`Ctrl+Shift+B`)

**Step 4: Run Application**
- Debug mode: `F5` (from Visual Studio)
- MSIX package: Double-click `YtDlpGui.msix`
- Portable version: Use `AppX` folder next to executable

**Step 5: Initial Configuration**
1. Open "Settings" page
2. Configure paths to:
   - `yt-dlp.exe`
   - `ffmpeg.exe`
3. Settings are saved to `%LocalAppData%\YtDlpGui\config\settings.json`

### Application Features

#### Download Management
- Download individual videos and entire playlists
- Select playlist item ranges (with resume support)
- Configure download parameters (folder, resolution, codec, bitrate, flags)

#### Media Processing
- Automatic format selection based on settings
- Audio-only / video-only / separate audio track options
- Embed thumbnails, metadata, and subtitles

#### User Experience
- Cookie import (Netscape/JSON format, browser, clipboard)
- Advanced download history with search and filter capabilities
- Built-in console for direct yt-dlp command execution

#### Appearance and Localization
- Light/Dark/AUTO theme selection
- Multi-language support (ru/en/uk)
- Automatic yt-dlp updates from within application

### Folder Structure

```
YtDlpGui/
├── Views/
│   ├── DownloadPage.xaml.cpp/h
│   ├── HistoryPage.xaml.cpp/h
│   ├── SettingsPage.xaml.cpp/h
│   ├── ConsolePage.xaml.cpp/h
│   └── PlaylistDialog.xaml.cpp/h
├── ViewModels/
│   ├── MainViewModel.cpp/h
│   ├── DownloadViewModel.cpp/h
│   ├── SettingsViewModel.cpp/h
│   ├── HistoryViewModel.cpp/h
│   ├── ConsoleViewModel.cpp/h
│   ├── RelayCommand.cpp/h
│   └── ViewModelBase.cpp/h
├── Services/
│   ├── YtDlpService.cpp/h
│   ├── SettingsService.cpp/h
│   ├── HistoryDatabase.cpp/h
│   ├── ProxyService.cpp/h
│   ├── CookieService.cpp/h
│   ├── FileDownloader.cpp/h
│   ├── ProcessRunner.cpp/h
│   └── DownloadService.cpp/h
├── Models/
│   ├── VideoInfo.h
│   ├── HistoryEntry.h
│   ├── AppSettings.h
│   ├── DownloadItem.h
│   ├── FormatInfo.h
│   ├── PlaylistInfo.h
│   └── HistoryEntryModel.h
├── Converters/
│   ├── DurationFormatConverter.cpp/h
│   ├── BoolToVisibilityConverter.cpp/h
│   └── InverseBoolToVisibilityConverter.cpp/h
├── MainWindow.xaml.cpp/h
├── App.xaml.cpp/h
├── pch.cpp/h
└── YtDlpGui.vcxproj
```

## Application Architecture

### Core Components

#### GUI Layer (WinUI 3)
- **MainWindow.xaml.cpp**: Primary application window with navigation
- **Views**: Individual page implementations (Download, History, Settings, Console)
- **ViewModels**: MVVM pattern implementation
- **Converters**: Data formatting and display utilities

#### Application Logic
- **YtDlpService**: Core yt-dlp integration and command execution
- **HistoryDatabase**: Download history management with JSON persistence
- **SettingsService**: Application configuration management
- **CookieService**: Cookie handling for restricted content

#### Utility Services
- **FileDownloader**: Direct HTTP file downloading
- **ProcessRunner**: External process management and output processing
- **ProxyService**: Proxy configuration support
- **DownloadService**: Download queue and progress tracking

### Data Models

#### Core Models
- **VideoInfo**: Video metadata and format information
- **HistoryEntry**: Download history record
- **AppSettings**: Application configuration
- **DownloadItem**: Active download information

### Technical Architecture

#### Modern C++ Development
- **Language**: Modern C++ with WinRT/ATL patterns
- **UI Framework**: WinUI 3 (Microsoft UI Library)
- **Memory Management**: RAII (Resource Acquisition Is Initialization)
- **Threading**: Proper synchronization with mutexes
- **Error Handling**: Structured exception handling

#### Windows Integration
- **WinUI 3**: Modern Windows application framework
- **Windows App SDK**: Latest Windows development APIs
- **COM Integration**: Windows Runtime interop
- **File System**: Windows-native file operations

## Code Quality and Maintenance

### Current Improvements

#### Bug Fixes and Optimizations
1. **HistoryDatabase.cpp**: Fixed `WriteAtomic` function to properly save content
2. **ProcessRunner.cpp**: Improved handle management and error handling
3. **SettingsService.cpp**: Enhanced file save operations with error checking
4. **FileDownloader.cpp**: Fixed path handling in synchronous download method

#### Security Enhancements
- Safe file operations with proper error handling
- Improved JSON parsing with exception safety
- Handle management with proper resource cleanup

#### Performance Optimizations
- Reduced unnecessary memory allocations
- Improved file I/O error handling
- Better thread synchronization

### Development Best Practices

#### Error Handling Strategy
- Specific exception types for different error conditions
- Graceful degradation when operations fail
- User-friendly error messages

#### Memory Management
- RAII for resource management
- Smart pointer usage where appropriate
- Proper cleanup in destructors

#### Thread Safety
- Mutex protection for shared resources
- Proper synchronization in multi-threaded operations
- Thread pool usage for background tasks

## Repository Configuration

### .gitignore
```gitignore
# Build artifacts
out/
x64/
ARM64/

# Visual Studio cache
.vs/
*.vcdb

# NuGet packages
packages/
.nuget/

# Temporary files
*.tmp
*.temp

# System files
Thumbs.db
.DS_Store

# Personal files
*.swp
*.swo

# Log files
*.log
```

### Visual Studio Settings
```xml
<!-- UserPrefs.xml -->
<UsersSettings>
  <VB>
    <InheritsFrom>DefaultVB</InheritsFrom>
    <BrowserAccess>
      <Remoteenable>True</Remoteenable>
      <RemoteDebuggingPort>11139</RemoteDebuggingPort>
    </BrowserAccess>
  </VB>
  <FileBrowser>
    <BrowserAccess>
      <Remoteenable>True</Remoteenable>
    </BrowserAccess>
  </FileBrowser>
</UsersSettings>
```

## Project Status and Roadmap

### Current State
✅ **README Documentation**: Complete multilingual structure
✅ **BUILD Documentation**: Complete multilingual build guide
✅ **Git History**: Cleaned to single commit
✅ **Code Quality**: Critical bugs fixed and optimized
✅ **Repository Structure**: Clean and maintained

### Upcoming Improvements
- [ ] Automated documentation generation
- [ ] Continuous integration setup
- [ ] Performance benchmarking
- [ ] Accessibility enhancements

## Conclusion

The yt-dlp-gui project delivers a polished, multilingual Windows desktop application for downloading and managing online video content. The documentation provides comprehensive guidance for developers and users across different languages and regions, with a clean repository structure and robust application architecture.

The project successfully balances technical excellence with user-friendly design, making it accessible to both novice users and advanced power users requiring precise download control.
