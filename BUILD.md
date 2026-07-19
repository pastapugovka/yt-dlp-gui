<div align="center">

# yt-dlp-gui — Build Guide / Сборка / 构建指南 / راهنمای ساخت

[English](#english) / [Русский](#русский) / [简体中文](#简体中文) / [فارسی](#فارسی)

</div>

---


<a id="en"></a>

## English

Detailed guide from Visual Studio to launch. Internet is required to restore NuGet packages.
Repository: https://github.com/pastapugovka/yt-dlp-gui · Release: [v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)

<details open>
<summary><b>Table of contents</b></summary>

- [1. Install Visual Studio](#en-1)
- [2. Sources](#en-2)
- [3. Restore NuGet](#en-3)
- [4. Configuration](#en-4)
- [5. Build](#en-5)
- [6. Run](#en-6)
- [7. Setup](#en-7)
- [Troubleshooting](#en-t)

</details>

### <a id="en-1"></a>1. Install Visual Studio
1. Download [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) (Community is fine).
2. Enable workloads:
   - **Desktop development with C++**
   - **Windows development with C++** (WinUI 3)
   - **Universal Windows Platform** (provides Windows SDK)
3. In "Individual components" ensure **Windows 10/11 SDK (10.0.26100.0)** is selected.

### <a id="en-2"></a>2. Sources
Clone the repo or extract the archive. You need `YtDlpGui.sln` and the `YtDlpGui/` folder.

```powershell
git clone https://github.com/pastapugovka/yt-dlp-gui.git
cd yt-dlp-gui
```

### <a id="en-3"></a>3. Restore NuGet
The project uses `Microsoft.Windows.CppWinRT 2.0.240405.15` and `Microsoft.WindowsAppSDK 1.5.240802000`. They are not in the repo — restore them.

**In Visual Studio:** open the solution → *Build → Restore NuGet Packages*.

**Console:**
```powershell
nuget restore YtDlpGui.sln
```

> ⚠️ "project references NuGet package(s) that are missing" means restore did not run. Packages must appear in the `packages\` folder.

### <a id="en-4"></a>4. Configuration
- Open `YtDlpGui.sln`.
- Configuration: `Release`, Platform: `x64`.

### <a id="en-5"></a>5. Build
*Build → Build Solution* (`Ctrl+Shift+B`). The first build generates headers from `.idl` — wait 1–3 minutes.

> ✅ Output: `YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe` and `YtDlpGui.msix`.

### <a id="en-6"></a>6. Run
- `F5` — run from VS.
- Double-click the `.msix` — install (trust `YtDlpGui_TemporaryKey.pfx` in "Trusted Root Certification Authorities" on first run).
- Portable: the `AppX\` folder next to the EXE.

### <a id="en-7"></a>7. Setup
On the Settings page, set paths to `yt-dlp.exe` and `ffmpeg.exe`. Settings are saved to `%LocalAppData%\YtDlpGui\config\settings.json`.

### <a id="en-t"></a>Troubleshooting
| Error | Fix |
|-------|-----|
| `MSB4019` (targets not found) | Packages not restored — step 3. |
| `bootstrap failed` at launch | Windows App SDK Runtime 1.5 missing — install separately. |
| `YtDlpGui` type not found | Headers not generated yet — rebuild. |



<a id="fa"></a>

## فارسی

راهنمای کامل: از Visual Studio تا اجرا. اینترنت برای بازیابی بسته‌های NuGet لازم است.
مخزن: https://github.com/pastapugovka/yt-dlp-gui · نسخه: [v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)

<details>
<summary><b>فهرست</b></summary>

- [۱. نصب Visual Studio](#fa-1)
- [۲. دریافت منبع](#fa-2)
- [۳. بازیابی NuGet](#fa-3)
- [۴. پیکربندی](#fa-4)
- [۵. ساخت](#fa-5)
- [۶. اجرا](#fa-6)
- [۷. تنظیمات](#fa-7)
- [رفع اشکال](#fa-t)

</details>

### <a id="fa-1"></a>۱. نصب Visual Studio
۱. [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) را دانلود کنید (نسخه Community کافی است).
۲. این بارهای کاری را فعال کنید:
   - **توسعه دسکتاپ با C++**
   - **توسعه ویندوز با C++** (WinUI 3)
   - **بستر فراگیر ویندوز** (Windows SDK را فراهم می‌کند)
۳. در «اجزای مجزا» مطمئن شوید **Windows 10/11 SDK (10.0.26100.0)** انتخاب شده است.

### <a id="fa-2"></a>۲. دریافت منبع
مخزن را کلون کنید یا فایل را استخراج کنید. به `YtDlpGui.sln` و پوشه `YtDlpGui/` نیاز دارید.

```powershell
git clone https://github.com/pastapugovka/yt-dlp-gui.git
cd yt-dlp-gui
```

### <a id="fa-3"></a>۳. بازیابی NuGet
پروژه از بسته‌های `Microsoft.Windows.CppWinRT 2.0.240405.15` و `Microsoft.WindowsAppSDK 1.5.240802000` استفاده می‌کند. آن‌ها در مخزن نیستند — باید بازیابی شوند.

**در Visual Studio:** راه‌حل را باز کنید → *Build → Restore NuGet Packages*.

**خط فرمان:**
```powershell
nuget restore YtDlpGui.sln
```

> ⚠️ "project references NuGet package(s) that are missing" یعنی بازیابی انجام نشده است. بسته‌ها باید در پوشه `packages\` ظاهر شوند.

### <a id="fa-4"></a>۴. پیکربندی
- فایل `YtDlpGui.sln` را باز کنید.
- پیکربندی: `Release`، پلتفرم: `x64`.

### <a id="fa-5"></a>۵. ساخت
*Build → Build Solution* (`Ctrl+Shift+B`). در ساخت اول، هدرها از `.idl` تولید می‌شوند — ۱ تا ۳ دقیقه صبر کنید.

> ✅ خروجی: `YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe` و `YtDlpGui.msix`.

### <a id="fa-6"></a>۶. اجرا
- `F5` — اجرا از داخل VS.
- دوبار کلیک روی `.msix` — نصب (در اولین اجرا گواهی `YtDlpGui_TemporaryKey.pfx` را تأیید کنید).
- نسخه قابل‌حمل: پوشه `AppX\` کنار فایل اجرایی.

### <a id="fa-7"></a>۷. تنظیمات
در صفحه «تنظیمات»، مسیر `yt-dlp.exe` و `ffmpeg.exe` را مشخص کنید. تنظیمات در `%LocalAppData%\YtDlpGui\config\settings.json` ذخیره می‌شوند.

### <a id="fa-t"></a>رفع اشکال
| خطا | راه‌حل |
|-----|--------|
| `MSB4019` (عدم یافتن targets) | بسته‌ها بازیابی نشده‌اند — گام ۳. |
| `bootstrap failed` هنگام اجرا | Windows App SDK Runtime 1.5 نصب نیست — جداگانه نصب کنید. |
| نوع `YtDlpGui` یافت نشد | هدرها هنوز تولید نشده‌اند — بازسازی کنید. |



<a id="cn"></a>

## 简体中文

从 Visual Studio 到运行的详细指南。还原 NuGet 包需要联网。
仓库：https://github.com/pastapugovka/yt-dlp-gui · 发布：[v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)

<details>
<summary><b>目录</b></summary>

- [1. 安装 Visual Studio](#cn-1)
- [2. 获取源码](#cn-2)
- [3. 还原 NuGet](#cn-3)
- [4. 配置](#cn-4)
- [5. 生成](#cn-5)
- [6. 运行](#cn-6)
- [7. 设置](#cn-7)
- [故障排除](#cn-t)

</details>

### <a id="cn-1"></a>1. 安装 Visual Studio
1. 下载 [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)（Community 即可）。
2. 启用工作负载：
   - **使用 C++ 的桌面开发**
   - **使用 C++ 的 Windows 开发**（WinUI 3）
   - **通用 Windows 平台**（提供 Windows SDK）
3. 在“单个组件”中确认已勾选 **Windows 10/11 SDK (10.0.26100.0)**。

### <a id="cn-2"></a>2. 获取源码
克隆仓库或解压压缩包。需要 `YtDlpGui.sln` 和 `YtDlpGui/` 文件夹。

```powershell
git clone https://github.com/pastapugovka/yt-dlp-gui.git
cd yt-dlp-gui
```

### <a id="cn-3"></a>3. 还原 NuGet
项目使用 `Microsoft.Windows.CppWinRT 2.0.240405.15` 和 `Microsoft.WindowsAppSDK 1.5.240802000`。它们不在仓库中——需要还原。

**在 Visual Studio 中：** 打开解决方案 → *生成 → 还原 NuGet 包*。

**命令行：**
```powershell
nuget restore YtDlpGui.sln
```

> ⚠️ “project references NuGet package(s) that are missing” 表示未还原。包必须出现在 `packages\` 文件夹中。

### <a id="cn-4"></a>4. 配置
- 打开 `YtDlpGui.sln`。
- 配置：`Release`，平台：`x64`。

### <a id="cn-5"></a>5. 生成
*生成 → 生成解决方案*（`Ctrl+Shift+B`）。首次生成会从 `.idl` 生成头文件——请等待 1–3 分钟。

> ✅ 输出：`YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe` 和 `YtDlpGui.msix`。

### <a id="cn-6"></a>6. 运行
- `F5` — 从 VS 运行。
- 双击 `.msix` — 安装（首次请将 `YtDlpGui_TemporaryKey.pfx` 信任到“受信任的根证书颁发机构”）。
- 便携版：EXE 旁的 `AppX\` 文件夹。

### <a id="cn-7"></a>7. 设置
在“设置”页中指定 `yt-dlp.exe` 和 `ffmpeg.exe` 的路径。设置保存在 `%LocalAppData%\YtDlpGui\config\settings.json`。

### <a id="cn-t"></a>故障排除
| 错误 | 解决方法 |
|------|----------|
| `MSB4019`（找不到 targets） | 未还原包——第 3 步。 |
| 启动时 `bootstrap failed` | 未安装 Windows App SDK Runtime 1.5——单独安装。 |
| 找不到 `YtDlpGui` 类型 | 头文件尚未生成——重新生成。 |



<a id="ru"></a>

## Русский

Подробная инструкция: от Visual Studio до запуска. Интернет нужен для восстановления NuGet-пакетов.
Репозиторий: https://github.com/pastapugovka/yt-dlp-gui · Релиз: [v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)

<details>
<summary><b>Содержание</b></summary>

- [1. Установка Visual Studio](#ru-1)
- [2. Исходники](#ru-2)
- [3. Восстановление NuGet](#ru-3)
- [4. Конфигурация](#ru-4)
- [5. Сборка](#ru-5)
- [6. Запуск](#ru-6)
- [7. Настройка](#ru-7)
- [Решение проблем](#ru-t)

</details>

### <a id="ru-1"></a>1. Установка Visual Studio
1. Скачайте [Visual Studio 2022](https://visualstudio.microsoft.com/ru/downloads/) (Community подойдёт).
2. Включите рабочие нагрузки:
   - **Разработка классических приложений на C++**
   - **Разработка приложений для Windows с помощью C++** (WinUI 3)
   - **Универсальная платформа Windows** (даёт Windows SDK)
3. В «Отдельные компоненты» убедитесь, что выбран **Windows 10/11 SDK (10.0.26100.0)**.

### <a id="ru-2"></a>2. Исходники
Клонируйте репозиторий или распакуйте архив. Нужны `YtDlpGui.sln` и папка `YtDlpGui/`.

```powershell
git clone https://github.com/pastapugovka/yt-dlp-gui.git
cd yt-dlp-gui
```

### <a id="ru-3"></a>3. Восстановление NuGet
Проект использует пакеты `Microsoft.Windows.CppWinRT 2.0.240405.15` и `Microsoft.WindowsAppSDK 1.5.240802000`. Их нет в репозитории — надо скачать.

**В Visual Studio:** откройте решение → *Сборка → Восстановить пакеты NuGet*.

**Консоль:**
```powershell
nuget restore YtDlpGui.sln
```

> ⚠️ Ошибка «project references NuGet package(s) that are missing» означает, что restore не выполнен. Пакеты должны появиться в папке `packages\`.

### <a id="ru-4"></a>4. Конфигурация
- Откройте `YtDlpGui.sln`.
- Конфигурация: `Release`, Платформа: `x64`.

### <a id="ru-5"></a>5. Сборка
*Сборка → Собрать решение* (`Ctrl+Shift+B`). Первая сборка генерирует заголовки из `.idl` — подождите 1–3 минуты.

> ✅ Результат: `YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe` и `YtDlpGui.msix`.

### <a id="ru-6"></a>6. Запуск
- `F5` — запуск из VS.
- Двойной клик по `.msix` — установка (при первом разе доверьте сертификат `YtDlpGui_TemporaryKey.pfx` в «Доверенные корневые центры»).
- Портативно: папка `AppX\` рядом с EXE.

### <a id="ru-7"></a>7. Настройка
На странице «Настройки» укажите пути к `yt-dlp.exe` и `ffmpeg.exe`. Настройки сохраняются в `%LocalAppData%\YtDlpGui\config\settings.json`.

### <a id="ru-t"></a>Решение проблем
| Ошибка | Решение |
|--------|---------|
| `MSB4019` (не найден targets) | Пакеты не восстановлены — шаг 3. |
| `bootstrap failed` при запуске | Не установлен Windows App SDK Runtime 1.5 — поставьте отдельно. |
| Тип `YtDlpGui` не найден | Заголовки ещё не сгенерированы — пересоберите. |
