<div align="center">

# yt-dlp-gui

**yt-dlp-gui** — 图形界面（WinUI 3，C++/WinRT），基于 [yt-dlp](https://github.com/yt-dlp/yt-dlp)。

[English](README.md) / [Русский](README_RU.md) / 简体中文 / [فارسی](README_FA.md)

[![Version](https://img.shields.io/badge/release-v%201.0.b-green.svg)](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)
![Platform](https://img.shields.io/badge/platform-Windows-blue.svg)
![UI](https://img.shields.io/badge/ui-WinUI%203-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

</div>

## 功能
- 下载单个视频和整个播放列表
- 选择播放列表的区间（支持断点续传）
- 配置下载参数：保存目录、分辨率、编码格式、码率、额外参数
- 当视频不符合设置时自动选择格式
- 仅音频 / 仅视频 / 分离音轨
- 导入 Cookie（Netscape/JSON 文件、剪贴板、浏览器）以访问受限内容
- 下载历史，支持筛选、导出 CSV/JSON 和重新下载
- 内置控制台，可直接向 yt-dlp 发送命令
- 深色/浅色主题及界面语言（ru/en/uk）
- 在应用内检查和更新 yt-dlp

## 系统要求
- Windows 10/11（版本 17763 及以上）
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — 路径在设置中指定（也可将 `yt-dlp.exe` 放在程序旁边）
- [FFmpeg](https://ffmpeg.org/) — 路径在设置中指定（合并/转码时需要）

## 下载
最新版本：**[v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)**

- `YtDlpGui.msix` — 安装包（首次运行时信任 `YtDlpGui_TemporaryKey.pfx` 证书）
- 便携版 EXE — EXE 旁的 `AppX` 文件夹

源代码：[github.com/pastapugovka/yt-dlp-gui](https://github.com/pastapugovka/yt-dlp-gui)

## 安装
1. 下载最新版本（`YtDlpGui.msix` 或便携版 EXE）
2. 首次启动时，在「设置」页指定 `yt-dlp.exe` 和 `ffmpeg.exe` 的路径
3. 完成 — 即可开始下载

## 下载教程
1. 在「下载」页粘贴视频或播放列表链接
2. 可选：设置分辨率、编码格式、音频和额外参数
3. 对于播放列表，打开播放列表对话框并选择区间/模式
4. 实时查看进度
5. 文件保存到所选目录（默认：应用下载目录）

## 设置
- yt-dlp 和 ffmpeg 路径
- 下载目录
- 代理和 User-Agent
- 导入/清除 Cookie
- 文件名模板、最大并行下载数
- 嵌入封面 / 字幕 / 元数据
- 主题（浅色/深色/系统）和界面语言
- 自动更新 yt-dlp

设置保存在 `%LocalAppData%\YtDlpGui\config\settings.json`。

## Cookie
内置 Cookie 编辑器可访问受限内容：
- 导入文件（.txt Netscape 或 .json）
- 从剪贴板粘贴文本
- 直接从浏览器导入（Chrome、Edge、Firefox、Opera）

> 注意：Cookie 以明文形式保存在本地。

## 支持的服务
支持 [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme) 原生支持的所有网站和服务。完整且最新的提取器列表见 [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md)。包括 YouTube、Vimeo、Twitch 等。

## 从源码构建
详细的逐步指南和故障排除见 [BUILD.md](BUILD.md#cn)。

### 要求
- Visual Studio 2022 或更高版本
- 「使用 C++ 的桌面开发」工作负载和 Windows App SDK
- Windows SDK 10.0.26100.0

### 编译
1. 克隆仓库：`git clone https://github.com/pastapugovka/yt-dlp-gui.git`
2. 执行 `nuget restore`（包 `Microsoft.Windows.CppWinRT` 和 `Microsoft.WindowsAppSDK`）
3. 打开 `YtDlpGui.sln`
4. 选择 `Release | x64`
5. 生成解决方案（Ctrl+Shift+B）

## 许可证
MIT — 可自由使用和修改。作者：[pastapugovka](https://github.com/pastapugovka)。

## 致谢
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — 本工具的核心
- [FFmpeg](https://ffmpeg.org/) — 媒体处理
- [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/) — UI 框架
