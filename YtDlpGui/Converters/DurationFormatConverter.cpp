#include "pch.h"
#include "DurationFormatConverter.h"
#include <cmath>

namespace winrt::YtDlpGui::Converters::implementation
{
    winrt::Windows::Foundation::IInspectable DurationFormatConverter::Convert(
        winrt::Windows::Foundation::IInspectable const& value,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::hstring const&)
    {
        if (value == nullptr)
            return winrt::box_value(L"");

        double seconds = winrt::unbox_value<double>(value);
        int totalSeconds = static_cast<int>(std::round(seconds));

        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
        int secs = totalSeconds % 60;

        if (hours > 0)
        {
            return winrt::box_value(
                std::to_wstring(hours) + L":" +
                (minutes < 10 ? L"0" : L"") + std::to_wstring(minutes) + L":" +
                (secs < 10 ? L"0" : L"") + std::to_wstring(secs));
        }
        else
        {
            return winrt::box_value(
                std::to_wstring(minutes) + L":" +
                (secs < 10 ? L"0" : L"") + std::to_wstring(secs));
        }
    }

    winrt::Windows::Foundation::IInspectable DurationFormatConverter::ConvertBack(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::hstring const&)
    {
        return winrt::box_value(nullptr);
    }
}
