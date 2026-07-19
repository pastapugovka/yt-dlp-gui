#pragma once

#include "PlaylistDialog.xaml.g.h"
#include <vector>
#include <string>

namespace winrt::YtDlpGui::Views::implementation
{
    struct PlaylistDialog : PlaylistDialogT<PlaylistDialog>
    {
        PlaylistDialog();

        winrt::Windows::Foundation::IAsyncAction ShowDialogAsync(
            winrt::Microsoft::UI::Xaml::Window const& parentWindow);

        int RangeStart() const { return m_rangeStart; }
        int RangeEnd() const { return m_rangeEnd; }
        bool CreateDirectory() const { return m_createDir; }
        bool NumberFiles() const { return m_numberFiles; }
        std::wstring Mode() const { return m_mode; }

        void SetPlaylistInfo(const std::wstring& title, int count);

    private:
        void OnModeChanged();
        void OnPrimary();

        int m_rangeStart{ 1 };
        int m_rangeEnd{ 0 };
        bool m_createDir{ true };
        bool m_numberFiles{ true };
        std::wstring m_mode{ L"All" };
    };
}

namespace winrt::YtDlpGui::Views::factory_implementation
{
    struct PlaylistDialog : PlaylistDialogT<PlaylistDialog, implementation::PlaylistDialog>
    {
    };
}
