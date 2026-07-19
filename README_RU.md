<div align="center">

# yt-dlp-gui

**yt-dlp-gui** — графический интерфейс (WinUI 3, C++/WinRT) для [yt-dlp](https://github.com/yt-dlp/yt-dlp).

[English](README.md) / Русский / [简体中文](README_CN.md) / [فارسی](README_FA.md)

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

## Возможности
- Загрузка отдельных видео и плейлистов
- Выбор диапазона элементов плейлиста (с возможностью возобновления)
- Настройка параметров загрузки: папка, разрешение, кодек, битрейт, доп. флаги
- Автоматический выбор формата, если видео не совпадает с заданными параметрами
- Только аудио / только видео / отдельная дорожка
- Импорт кук (файл Netscape/JSON, буфер обмена, браузер) для закрытого контента
- История загрузок с фильтрами, экспортом в CSV/JSON и повторной загрузкой
- Встроенная консоль с передачей команд напрямую в yt-dlp
- Тёмная/светлая тема и выбор языка (ru/en/uk)
- Проверка и обновление yt-dlp из интерфейса

## Требования
- Windows 10/11 (версия 17763 и новее)
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — путь задаётся в настройках (при необходимости можно положить `yt-dlp.exe` рядом с программой)
- [FFmpeg](https://ffmpeg.org/) — путь задаётся в настройках (нужен для слияния/перекодирования)

## Загрузки
Последний релиз: **[v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)**

- `YtDlpGui.msix` — установочный пакет (при первом запуске доверьте сертификат `YtDlpGui_TemporaryKey.pfx`)
- Портативный EXE — папка `AppX` рядом с исполняемым файлом

Исходный код: [github.com/pastapugovka/yt-dlp-gui](https://github.com/pastapugovka/yt-dlp-gui)

## Установка
1. Скачайте последний релиз (`YtDlpGui.msix` или портативный EXE)
2. При первом запуске укажите пути к `yt-dlp.exe` и `ffmpeg.exe` на странице «Настройки»
3. Готово — можно загружать

## Загрузка
1. Вставьте ссылку на видео или плейлист на странице «Загрузка»
2. При необходимости укажите разрешение, кодек, аудио и дополнительные флаги
3. Для плейлистов откройте диалог плейлиста и выберите диапазон/режим
4. Наблюдайте прогресс в реальном времени
5. Файл сохраняется в выбранную папку (по умолчанию — папка загрузок приложения)

## Настройки
- Путь к yt-dlp и ffmpeg
- Папка для загрузок
- Прокси и User-Agent
- Импорт/очистка кук
- Шаблон имени файла, макс. число параллельных загрузок
- Встраивание обложки/субтитров/метаданных
- Тема (светлая/тёмная/системная) и язык интерфейса
- Автообновление yt-dlp

Настройки хранятся в `%LocalAppData%\YtDlpGui\config\settings.json`.

## Куки
Встроенный редактор кук позволяет получить доступ к ограниченному контенту:
- Импорт файла (.txt Netscape или .json)
- Вставка текста из буфера обмена
- Импорт напрямую из браузера (Chrome, Edge, Firefox, Opera)

> Примечание: куки хранятся локально без шифрования.

## Поддерживаемые сервисы
Поддерживаются все сайты и сервисы, которые изначально поддерживаются [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme). Полный актуальный список поддерживаемых извлекателей доступен в документе [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md).

<div align="left">
  <img src="https://upload.wikimedia.org/wikipedia/commons/b/b8/YouTube_Logo_2017.svg" height="32" alt="youtube"  />
  <img width="20" />
  <img src="https://upload.wikimedia.org/wikipedia/commons/c/ce/Twitch_logo_2019.svg" height="32" alt="twitch"  />
  <img width="20" />
  <img src="https://upload.wikimedia.org/wikipedia/commons/b/b6/Tiktok_logo_text.svg" height="32" alt="tiktok"  />
  <img width="20" />
  <img src="https://upload.wikimedia.org/wikipedia/commons/9/95/Instagram_logo_2022.svg" height="32" alt="instagram"  />
  <img width="20" />
  <img src="https://en.wikipedia.org/wiki/Special:FilePath/VK_Compact_Logo_(2021-present).svg" height="32" alt="vk"  />
</div>


## Сборка из исходников
Подробная пошаговая инструкция с решением проблем — в [BUILD.md](BUILD.md#ru).

### Требования
- Visual Studio 2022 или новее
- Рабочая нагрузка «Разработка классических приложений на C++» и Windows App SDK
- Windows SDK 10.0.26100.0

### Компиляция
1. Клонируйте репозиторий: `git clone https://github.com/pastapugovka/yt-dlp-gui.git`
2. Сделайте `nuget restore` (пакеты `Microsoft.Windows.CppWinRT` и `Microsoft.WindowsAppSDK`)
3. Откройте `YtDlpGui.sln`
4. Выберите конфигурацию `Release | x64`
5. Соберите решение (Ctrl+Shift+B)

## Лицензия
MIT — свободное использование и модификация. Автор: [pastapugovka](https://github.com/pastapugovka).

## Благодарности
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — основа инструмента
- [FFmpeg](https://ffmpeg.org/) — обработка медиа
- [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/) — UI-фреймворк
