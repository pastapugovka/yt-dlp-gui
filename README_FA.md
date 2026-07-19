<div align="center" dir="rtl">

# yt-dlp-gui

**yt-dlp-gui** — رابط گرافیکی (WinUI 3، C++/WinRT) برای [yt-dlp](https://github.com/yt-dlp/yt-dlp).

[English](README.md) / [Русский](README_RU.md) / [简体中文](README_CN.md) / فارسی

[![Version](https://img.shields.io/badge/release-v%201.0.b-green.svg)](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)
![License](https://img.shields.io/badge/license-MIT-green.svg)

<div align="center">
  <img src="https://skillicons.dev/icons?i=cs,cpp,windows,visualstudio" height="40" alt="tech stack"  />
</div>

</div>

<div dir="rtl">

## ویژگی‌ها
- دانلود ویدیوهای تکی و پلی‌لیست‌ها
- انتخاب بازه آیتم‌های پلی‌لیست (با پشتیبانی از ادامه دانلود)
- تنظیم پارامترهای دانلود: پوشه، رزولوشن، کدک، نرخ بیت، پرچم‌های اضافی
- انتخاب خودکار فرمت در صورت عدم تطابق ویدیو با تنظیمات
- فقط صوت / فقط تصویر / مسیر صوتی جداگانه
- وارد کردن کوکی‌ها (فایل Netscape/JSON، کلیپ‌بورد، مرورگر) برای محتوای محدود
- تاریخچه دانلود با فیلتر، خروجی CSV/JSON و دانلود مجدد
- کنسول داخلی برای ارسال دستورات مستقیم به yt-dlp
- تم تیره/روشن و انتخاب زبان (ru/en/uk)
- بررسی و به‌روزرسانی yt-dlp از درون برنامه

## نیازمندی‌ها
- ویندوز ۱۰/۱۱ (نسخه ۱۷۷۶۳ و بالاتر)
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — مسیر در تنظیمات مشخص می‌شود (می‌توانید `yt-dlp.exe` را کنار برنامه بگذارید)
- [FFmpeg](https://ffmpeg.org/) — مسیر در تنظیمات مشخص می‌شود (برای ادغام/تبدیل لازم است)

## دانلودها
آخرین نسخه: **[v 1.0.b](https://github.com/pastapugovka/yt-dlp-gui/releases/tag/v1.0.b)**

- `YtDlpGui.msix` — بسته نصب (در اولین اجرا گواهی `YtDlpGui_TemporaryKey.pfx` را تأیید کنید)
- نسخه قابل‌حمل EXE — پوشه `AppX` کنار فایل اجرایی

کد منبع: [github.com/pastapugovka/yt-dlp-gui](https://github.com/pastapugovka/yt-dlp-gui)

## نصب
۱. آخرین نسخه را دانلود کنید (`YtDlpGui.msix` یا EXE قابل‌حمل)
۲. در اولین اجرا، مسیر `yt-dlp.exe` و `ffmpeg.exe` را در صفحه «تنظیمات» مشخص کنید
۳. آماده — می‌توانید دانلود کنید

## دانلود
۱. لینک ویدیو یا پلی‌لیست را در صفحه «دانلود» بچسبانید
۲. در صورت نیاز رزولوشن، کدک، صوت و پرچم‌های اضافی را تنظیم کنید
۳. برای پلی‌لیست‌ها، پنجره پلی‌لیست را باز کرده و بازه/حالت را انتخاب کنید
۴. پیشرفت را به‌صورت لحظه‌ای مشاهده کنید
۵. فایل در پوشه انتخابی ذخیره می‌شود (پیش‌فرض: پوشه دانلود برنامه)

## تنظیمات
- مسیر yt-dlp و ffmpeg
- پوشه دانلود
- پروکسی و User-Agent
- وارد/پاک کردن کوکی
- الگوی نام فایل، حداکثر دانلود موازی
- جاسازی تصویر/زیرنویس/متادیتا
- تم (روشن/تیره/سیستم) و زبان رابط
- به‌روزرسانی خودکار yt-dlp

تنظیمات در `%LocalAppData%\YtDlpGui\config\settings.json` ذخیره می‌شوند.

## کوکی‌ها
ویرایشگر داخلی کوکی برای دسترسی به محتوای محدود:
- وارد کردن فایل (.txt Netscape یا .json)
- چسباندن متن از کلیپ‌بورد
- وارد کردن مستقیم از مرورگر (Chrome، Edge، Firefox، Opera)

> توجه: کوکی‌ها به‌صورت محلی و بدون رمزنگاری ذخیره می‌شوند.

## سرویس‌های پشتیبانی‌شده
تمام سایت‌ها و سرویس‌هایی که بومی توسط [yt-dlp](https://github.com/yt-dlp/yt-dlp#readme) پشتیبانی می‌شوند، پشتیبانی می‌شوند. فهرست کامل و به‌روز استخراج‌کننده‌ها در مستند [yt-dlp supported sites](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md) موجود است.

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


## ساخت از منبع
راهنمای گام‌به‌گام با عیب‌یابی در [BUILD.md](BUILD.md#fa).

### نیازمندی‌ها
- Visual Studio 2022 یا بالاتر
- بار کاری «توسعه دسکتاپ با C++» و Windows App SDK
- Windows SDK 10.0.26100.0

### کامپایل
1. کلون کردن: `git clone https://github.com/pastapugovka/yt-dlp-gui.git`
2. اجرای `nuget restore` (بسته‌های `Microsoft.Windows.CppWinRT` و `Microsoft.WindowsAppSDK`)
3. باز کردن `YtDlpGui.sln`
4. انتخاب `Release | x64`
5. ساخت解决方案 (Ctrl+Shift+B)

## مجوز
MIT — استفاده و تغییر آزاد. نویسنده: [pastapugovka](https://github.com/pastapugovka).

## قدردانی
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) — هسته ابزار
- [FFmpeg](https://ffmpeg.org/) — پردازش رسانه
- [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/) — چارچوب رابط

</div>
