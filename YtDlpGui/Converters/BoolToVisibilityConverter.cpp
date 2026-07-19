#include "pch.h"
#include "BoolToVisibilityConverter.h"

namespace winrt::YtDlpGui::Converters::implementation
{
    winrt::Windows::Foundation::IInspectable BoolToVisibilityConverter::Convert(
        winrt::Windows::Foundation::IInspectable const& value,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::hstring const&)
    {
        if (value == nullptr)
            return winrt::box_value(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

        auto boolValue = winrt::unbox_value<bool>(value);
        return winrt::box_value(
            boolValue
                ? winrt::Microsoft::UI::Xaml::Visibility::Visible
                : winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    winrt::Windows::Foundation::IInspectable BoolToVisibilityConverter::ConvertBack(
        winrt::Windows::Foundation::IInspectable const& value,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Windows::Foundation::IInspectable const&,
        winrt::hstring const&)
    {
        if (value == nullptr)
            return winrt::box_value(false);

        auto visibility = winrt::unbox_value<winrt::Microsoft::UI::Xaml::Visibility>(value);
        return winrt::box_value(
            visibility == winrt::Microsoft::UI::Xaml::Visibility::Visible);
    }
}
