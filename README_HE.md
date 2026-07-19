<div dir="rtl">

<img src="https://raw.githubusercontent.com/pastapugovka/assets/main/hb%20il.png" alt="צילום מסך" width="100%"/>

</div>

<div align="center" dir="rtl">

# yt-dlp-gui

**yt-dlp-gui** — מוריד אולטימטיבי לתוכן הנתמך על ידי yt-dlp (WinUI 3, C++/WinRT).

🇬🇧 [English](README.md) / 🇷🇺 [Русский](README_RU.md) / 🇨🇳 [简体中文](README_CN.md) / 🇮🇱 עברית

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

<div dir="rtl">

## תכונות
- הורדת סרטונים בודדים ופלייליסטים
- בחירת טווח פריטים בפלייליסט (עם תמיכה בהמשך הורדה)
- הגדרת פרמטרי הורדה: תיקייה, רזולוציה, קודק, קצב סיביות, דגלים נוספים
- בחירת פורמט אוטומטית כאשר הסרטון אינו תואם להגדרות
- אודיו בלבד / תמונה בלבד / ערוץ אודיו נפרד
- ייבוא עוגיות (קובץ Netscape/JSON, לוח גזירים, דפדפן) לתוכן מוגבל
- היסטוריית הורדות עם סינון, פלט CSV/JSON והורדה מחדש
- קונסולה מובנית לשליחת פקודות ישירות ל-yt-dlp
- מצב כהה/בהיר ובחירת שפה (ru/en/uk)
- בדיקה ועדכון של yt-dlp מתוך האפליקציה

## דרישות
- Windows 10/11 (גרסה 17763 ומעלה)
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — הנתיב מוגדר בהגדרות (ניתן לשים `yt-dlp.exe` לצד האפליקציה)
- [FFmpeg](https://ffmpeg.org/) — הנתיב מוגדר בהגדרות (נדרש למיזוג/המרה)

## הורדות
הגרסה האחרונה: **[v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)**

- `YtDlpGui.msix` — חבילת התקנה (בהרצה הראשונה אשר את האישור `YtDlpGui_TemporaryKey.pfx`)
- גרסת EXE ניידת — תיקיית `AppX` לצד קובץ ההפעלה

קוד מקור: [github.com/pastapugovka/yt-dlp-gui](https://github.com/pastapugovka/yt-dlp-gui)

## התקנה
1. הורד את הגרסה האחרונה (`YtDlpGui.msix` או EXE נייד)
2. בהרצה הראשונה, הגדר את הנתיבים ל-`yt-dlp.exe` ול-`ffmpeg.exe` בעמוד «הגדרות»
3. מוכן — אפשר להתחיל להוריד

## הורדה
1. הדבק את קישור הסרטון או הפלייליסט בעמוד «הורדה»
2. לפי הצורך, הגדר רזולוציה, קודק, אודיו ודגלים נוספים
3. עבור פלייליסטים, פתח את חלון הפלייליסט ובחר טווח/מצב
4. עקוב אחר ההתקדמות בזמן אמת
5. הקובץ נשמר בתיקייה שנבחרה (ברירת מחדל: תיקיית ההורדות של האפליקציה)

## הגדרות
- נתיבי yt-dlp ו-ffmpeg
- תיקיית הורדות
- פרוקסי ו-User-Agent
- ייבוא/מחיקת עוגיות
- תבנית שם קובץ, מקסימום הורדות מקבילות
- הטבעת תמונה/כתוביות/מטא-דאטה
- ערכת נושא (בהיר/כהה/מערכת) ושפת ממשק
- עדכון אוטומטי של yt-dlp

ההגדרות נשמרות ב-`%LocalAppData%\YtDlpGui\config\settings.json`.

## עוגיות
עורך עוגיות מובנה לגישה לתוכן מוגבל:
- ייבוא קובץ (.txt Netscape או .json)
- הדבקת טקסט מלוח הגזירים
- ייבוא ישיר מדפדפן (Chrome, Edge, Firefox, Opera)

> שים לב: העוגיות נשמרות באופן מקומי וללא הצפנה.

## שירותים נתמכים
כל האתרים והשירותים הנתמכים באופן טבעי על ידי [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme), כולל YouTube ו-TikTok, כמו גם שירותי מוזיקה כמו Spotify ו-Deezer. הרשימה המלאה והעדכנית ביותר של מחלצים נתמכים זמינה במסמך [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md).


## בנייה מהמקור
מדריך שלב אחר שלב עם פתרון תקלות ב-[BUILD.md](BUILD.md#he).

### דרישות
- Visual Studio 2022 ומעלה
- עומס העבודה «פיתוח שולחן עבודה עם C++» ו-Windows App SDK
- Windows SDK 10.0.26100.0

### קומפילציה
1. שכפול: `git clone https://github.com/pastapugovka/yt-dlp-gui.git`
2. הרצת `nuget restore` (חבילות `Microsoft.Windows.CppWinRT` ו-`Microsoft.WindowsAppSDK`)
3. פתיחת `YtDlpGui.sln`
4. בחירת `Release | x64`
5. בניית הפתרון (Ctrl+Shift+B)

## רישיון
MIT — שימוש והתאמה חופשיים. יוצר: [pastapugovka](https://github.com/pastapugovka).

## תודות
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — ליב האמצעים
- [FFmpeg](https://ffmpeg.org/) — עיבוד מדיה
- [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/) — מסגרת הממשק

</div>
