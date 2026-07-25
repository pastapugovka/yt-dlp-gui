<div align="center">

# yt-dlp-gui — Build Guide / Сборка / 构建指南 / מדריך בנייה

[English](#en) / [Русский](#ru) / [简体中文](#cn) / [עברית](#he)

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
2. Enable workload:
   - **Desktop development with C++** ("Разработка классических приложений на C++")
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

> ✅ Output: `YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe`.

### <a id="en-6"></a>6. Run
- `F5` — run from VS.
- Or run `YtDlpGui.exe` directly from the output folder — no installation needed.

### <a id="en-7"></a>7. Setup
On the Settings page, set paths to `yt-dlp.exe` and `ffmpeg.exe`. Settings are saved to `%LocalAppData%\YtDlpGui\config\settings.json`.

### <a id="en-t"></a>Troubleshooting
| Error | Fix |
|-------|-----|
| `MSB4019` (targets not found) | Packages not restored — step 3. If NuGet restores to root folder, delete `packages/` and restore again. The `NuGet.Config` should ensure correct path. |
| `Package.appxmanifest already exists in filter` | This file was deleted — remove any remaining references from `.vcxproj`. |
| `bootstrap failed` at launch | Windows App SDK Runtime 1.5 missing — install separately. |
| `YtDlpGui` type not found | Headers not generated yet — rebuild. |


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
2. Включите рабочую нагрузку:
   - **Разработка классических приложений на C++**
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

> ✅ Результат: `YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe`.

### <a id="ru-6"></a>6. Запуск
- `F5` — запуск из VS.
- Или запустите `YtDlpGui.exe` напрямую из папки сборки — установка не нужна.

### <a id="ru-7"></a>7. Настройка
На странице «Настройки» укажите пути к `yt-dlp.exe` и `ffmpeg.exe`. Настройки сохраняются в `%LocalAppData%\YtDlpGui\config\settings.json`.

### <a id="ru-t"></a>Решение проблем
| Ошибка | Решение |
|--------|---------|
| `MSB4019` (не найден targets) | Пакеты не восстановлены — шаг 3. Если NuGet восстанавливает в корневую папку, удалите `packages/` и восстановите заново. |
| `Package.appxmanifest уже существует в фильтре` | Этот файл был удалён — уберите оставшиеся ссылки из `.vcxproj`. |
| `bootstrap failed` при запуске | Не установлен Windows App SDK Runtime 1.5 — поставьте отдельно. |
| Тип `YtDlpGui` не найден | Заголовки ещё не сгенерированы — пересоберите. |


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

> ✅ 输出：`YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe`。

### <a id="cn-6"></a>6. 运行
- `F5` — 从 VS 运行。
- 或直接运行输出文件夹中的 `YtDlpGui.exe` — 无需安装。

### <a id="cn-7"></a>7. 设置
在“设置”页中指定 `yt-dlp.exe` 和 `ffmpeg.exe` 的路径。设置保存在 `%LocalAppData%\YtDlpGui\config\settings.json`。

### <a id="cn-t"></a>故障排除
| 错误 | 解决方法 |
|------|----------|
| `MSB4019`（找不到 targets） | 未还原包——第 3 步。 |
| 启动时 `bootstrap failed` | 未安装 Windows App SDK Runtime 1.5——单独安装。 |
| 找不到 `YtDlpGui` 类型 | 头文件尚未生成——重新生成。 |


<a id="he"></a>

## עברית

מדריך מפורט מ-Visual Studio ועד להרצה. נדרש אינטרנט לשחזור חבילות NuGet.
מאגר: https://github.com/pastapugovka/yt-dlp-gui · גרסה: [v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)

<details>
<summary><b>תוכן עניינים</b></summary>

- [1. התקנת Visual Studio](#he-1)
- [2. מקורות](#he-2)
- [3. שחזור NuGet](#he-3)
- [4. תצורה](#he-4)
- [5. בנייה](#he-5)
- [6. הרצה](#he-6)
- [7. הגדרה](#he-7)
- [פתרון תקלות](#he-t)

</details>

### <a id="he-1"></a>1. התקנת Visual Studio
1. הורד את [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) (הגרסה Community מספיקה).
2. הפעל עומסי עבודה:
   - **Desktop development with C++**
3. ב"רכיבים בודדים" ודא שנבחר **Windows 10/11 SDK (10.0.26100.0)**.

### <a id="he-2"></a>2. מקורות
שכפל את המאגר או חלץ את הארכיון. נדרשים `YtDlpGui.sln` ותיקיית `YtDlpGui/`.

```powershell
git clone https://github.com/pastapugovka/yt-dlp-gui.git
cd yt-dlp-gui
```

### <a id="he-3"></a>3. שחזור NuGet
הפרויקט משתמש בחבילות `Microsoft.Windows.CppWinRT 2.0.240405.15` ו-`Microsoft.WindowsAppSDK 1.5.240802000`. הן לא נמצאות במאגר — יש לשחזר אותן.

**ב-Visual Studio:** פתח את הפתרון → *Build → Restore NuGet Packages*.

**שורת פקודה:**
```powershell
nuget restore YtDlpGui.sln
```

> ⚠️ "project references NuGet package(s) that are missing" פירושו שהשחזור לא רץ. החבילות חייבות להופיע בתיקיית `packages\`.

### <a id="he-4"></a>4. תצורה
- פתח את `YtDlpGui.sln`.
- תצורה: `Release`, פלטפורמה: `x64`.

### <a id="he-5"></a>5. בנייה
*Build → Build Solution* (`Ctrl+Shift+B`). הבנייה הראשונה מייצרת כותרות מ-`.idl` — המתן 1–3 דקות.

> ✅ פלט: `YtDlpGui\x64\Release\YtDlpGui\YtDlpGui.exe`.

### <a id="he-6"></a>6. הרצה
- `F5` — הרצה מתוך VS.
- או הפעל את `YtDlpGui.exe` ישירות מתיקיית הפלט — אין צורך בהתקנה.

### <a id="he-7"></a>7. הגדרה
בעמוד ההגדרות, הגדר נתיבים ל-`yt-dlp.exe` ול-`ffmpeg.exe`. ההגדרות נשמרות ב-`%LocalAppData%\YtDlpGui\config\settings.json`.

### <a id="he-t"></a>פתרון תקלות
| שגיאה | תיקון |
|-------|-------|
| `MSB4019` (targets לא נמצאו) | חבילות לא שוחזרו — שלב 3. אם NuGet משחזר לתיקיית השורש, מחק את `packages/` ושחזר שוב. |
| `Package.appxmanifest כבר קיים בפילטר` | קובץ זה נמחק — הסר הפניות שנותרו מ-`.vcxproj`. |
| `bootstrap failed` בהרצה | Windows App SDK Runtime 1.5 חסר — התקן בנפרד. |
| הסוג `YtDlpGui` לא נמצא | הכותרות עדיין לא נוצרו — בנה מחדש. |
