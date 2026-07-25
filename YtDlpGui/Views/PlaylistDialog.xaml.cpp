#include "pch.h"
#include "PlaylistDialog.xaml.h"

namespace winrt::YtDlpGui::Views::implementation
{
    PlaylistDialog::PlaylistDialog()
    {
        InitializeComponent();
    }

    void PlaylistDialog::SetPlaylistInfo(const std::wstring& title, int count)
    {
        if (PlaylistTitle())
            PlaylistTitle().Text(winrt::hstring(title));
        if (PlaylistInfo())
        {
            std::wstring info = L"Всего элементов: " + std::to_wstring(count);
            PlaylistInfo().Text(winrt::hstring(info));
        }
    }

    void PlaylistDialog::OnModeChanged()
    {
        if (!PlaylistModeGroup())
            return;
        auto selected = PlaylistModeGroup().SelectedItem().try_as<winrt::Microsoft::UI::Xaml::Controls::RadioButton>();
        m_mode = selected ? std::wstring(selected.Tag().as<winrt::hstring>()) : L"All";
        if (RangePanel())
            RangePanel().Visibility(m_mode == L"Range" ? winrt::Microsoft::UI::Xaml::Visibility::Visible
                                                       : winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    void PlaylistDialog::OnPrimary()
    {
        if (RangeStartBox()) m_rangeStart = static_cast<int>(RangeStartBox().Value());
        if (RangeEndBox()) m_rangeEnd = static_cast<int>(RangeEndBox().Value());
        if (CreateDirCheckBox()) m_createDir = CreateDirCheckBox().IsChecked().GetBoolean();
        if (NumberFilesCheckBox()) m_numberFiles = NumberFilesCheckBox().IsChecked().GetBoolean();
        if (PlaylistModeGroup())
        {
            auto selected = PlaylistModeGroup().SelectedItem().try_as<winrt::Microsoft::UI::Xaml::Controls::RadioButton>();
            m_mode = selected ? std::wstring(selected.Tag().as<winrt::hstring>()) : L"All";
        }
    }

    winrt::Windows::Foundation::IAsyncAction PlaylistDialog::ShowDialogAsync(
        winrt::Microsoft::UI::Xaml::Window const& parentWindow)
    {
        auto self = get_strong();
        if (PlaylistModeGroup())
            PlaylistModeGroup().SelectionChanged([this, self](auto&&, auto&&) { OnModeChanged(); });
        PrimaryButtonClick([this, self](auto&&, auto&&) { OnPrimary(); });

        OnModeChanged();
        co_await ShowAsync();
    }
}
