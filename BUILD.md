<div align="center">

# yt-dlp-gui — Build Guide / Сборка

[English](#en) / [Русский](#ru)

</div>

---

<a id="en"></a>

## English

Detailed guide from Visual Studio to launch. Internet required to restore NuGet packages.
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
   - **Desktop development with C++**
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
| `MSB4019` (targets not found) | Packages not restored — step 3. If NuGet restores to root folder, delete `packages/` and restore again. |
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
| `MSB4019` (не найден targets) | Пакеты не восстановлены — шаг 3. |
| `Package.appxmanifest уже существует в фильтре` | Этот файл был удалён — уберите оставшиеся ссылки из `.vcxproj`. |
| `bootstrap failed` при запуске | Не установлен Windows App SDK Runtime 1.5 — поставьте отдельно. |
| Тип `YtDlpGui` не найден | Заголовки ещё не сгенерированы — пересоберите. |