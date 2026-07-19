# Заливка проекта YtDlpGui в GitHub

Полный гайд: от локальной папки до публичного репозитория.

## 1. Подготовка локальной папки

У вас уже есть `C:\Users\Илья\Documents\yt-dlp-gui\` с файлами:
```
YtDlpGui.sln
YtDlpGui/            (исходники)
README.md  README_RU.md  README_CN.md  README_HE.md  BUILD.md
YtDlpGui_TemporaryKey.pfx   (если внутри YtDlpGui/)
```

Лишнее, что заливать НЕ надо (оно в .gitignore): `packages/`, `.vs/`, `out/`, `x64/`, `ARM64/`.

## 2. Создание репозитория на GitHub

1. Зайдите на https://github.com → <kbd>New</kbd> (зелёная кнопка) или <kbd>+</kbd> → <kbd>New repository</kbd>.
2. Имя: `YtDlpGui` (или `MR-CLI-FOR-YT-DLP`, как хотите).
3. Описание: `WinUI 3 GUI wrapper for yt-dlp (C++/WinRT)`.
4. Выберите **Public** (или Private).
5. **НЕ** ставьте галочки «Add a README», «Add .gitignore», «Add license» — у нас уже есть свои файлы.
6. Нажмите <kbd>Create repository</kbd>.

## 3. Заливка через Git (консоль)

Откройте PowerShell в папке проекта:

```powershell
cd C:\Users\Илья\Documents\yt-dlp-gui

git init
git add .
git commit -m "Initial commit: YtDlpGui WinUI 3 (C++/WinRT)"

git branch -M main
git remote add origin https://github.com/pastapugovka/yt-dlp-gui.git
git push -u origin main
```

Готово — проект в репозитории.

## 4. Заливка через GitHub Desktop (без консоли)

1. Скачайте и установите https://desktop.github.com/
2. <kbd>File</kbd> → <kbd>Add Local Repository</kbd> → выберите папку `yt-dlp-gui`.
3. В поле Summary напишите `Initial commit`, нажмите <kbd>Commit to main</kbd>.
4. <kbd>Publish repository</kbd> → выберите имя и видимость → <kbd>Publish</kbd>.

## 5. Заливка через VS Code

1. Откройте папку проекта в VS Code.
2. Установите расширение «Git Graph» или встроенный Git.
3. В панели «Source Control» (иконка ветки) нажмите <kbd>Initialize Repository</kbd>.
4. Введите сообщение `Initial commit`, нажмите <kbd>Commit</kbd>.
5. Нажмите <kbd>Publish to GitHub</kbd> (иконка облака) и следуйте мастеру.

## 6. Что попадёт в репозиторий

| Папка/файл | Заливать? | Почему |
|---|---|---|
| `YtDlpGui/` (исходники .cpp/.h/.xaml/.idl) | ✅ Да | Код проекта |
| `YtDlpGui/*.sln`, `*.vcxproj` | ✅ Да | Проектная система |
| `YtDlpGui/YtDlpGui_TemporaryKey.pfx` | ✅ Да | Нужен для подписи MSIX при сборке |
| `README*.md`, `BUILD.md` | ✅ Да | Документация |
| `packages/` | ❌ Нет | Восстанавливается через nuget restore |
| `.vs/`, `out/`, `x64/`, `ARM64/` | ❌ Нет | Временные артефакты сборки |
| `.nuget/`, `vs*.json` | ❌ Нет | Кэш VS |

## 7. Если `git push` требует логин

GitHub больше не принимает пароль от аккаунта. Используйте:
- **Personal Access Token (PAT)**: https://github.com/settings/tokens → создать с правами `repo` → вставить вместо пароля.
- Или настройте **SSH-ключ**: https://github.com/settings/ssh → добавить публичный ключ, затем `git remote set-url origin git@github.com:pastapugovka/yt-dlp-gui.git`.

## 8. Обновление репозитория после правок

```powershell
git add .
git commit -m "Описание изменений"
git push
```
