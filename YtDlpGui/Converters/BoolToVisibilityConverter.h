#pragma once

#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Windows.Foundation.h>

namespace winrt::YtDlpGui::Converters::implementation
{
    struct BoolToVisibilityConverter : BoolToVisibilityConverterT<BoolToVisibilityConverter>
    {
        winrt::Windows::Foundation::IInspectable Convert(
            winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::Foundation::IInspectable const& targetType,
            winrt::Windows::Foundation::IInspectable const& parameter,
            winrt::hstring const& language);

        winrt::Windows::Foundation::IInspectable ConvertBack(
            winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::Foundation::IInspectable const& targetType,
            winrt::Windows::Foundation::IInspectable const& parameter,
            winrt::hstring const& language);
    };
}

namespace winrt::YtDlpGui::Converters::factory_implementation
{
    struct BoolToVisibilityConverter : BoolToVisibilityConverterT<BoolToVisibilityConverter, implementation::BoolToVisibilityConverter>
    {
    };
}
