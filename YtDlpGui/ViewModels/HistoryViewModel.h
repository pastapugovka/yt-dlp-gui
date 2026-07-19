#pragma once

#include "../ViewModels/ViewModelBase.h"
#include "../ViewModels/RelayCommand.h"
#include "../Models/HistoryEntry.h"
#include "../Models/HistoryEntryModel.h"
#include "../Services/HistoryDatabase.h"
#include "../Services/ProcessRunner.h"
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <vector>

namespace winrt::YtDlpGui::ViewModels
{
    struct HistoryViewModel : HistoryViewModelT<HistoryViewModel>, ViewModelBase
    {
        using ViewModelBase::PropertyChanged;

        HistoryViewModel();

        void Initialize(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher);
        void RefreshEntries();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::YtDlpGui::Models::HistoryEntry> Entries() const { return m_entries; }

        winrt::hstring SearchText() const { return m_searchText; }
        void SearchText(winrt::hstring const& value);

        winrt::hstring StatusFilter() const { return m_statusFilter; }
        void StatusFilter(winrt::hstring const& value);

        winrt::hstring PlatformFilter() const { return m_platformFilter; }
        void PlatformFilter(winrt::hstring const& value);

        int TotalCount() const { return m_totalCount; }

        winrt::hstring StatusMessage() const { return m_statusMessage; }

        winrt::Microsoft::UI::Xaml::Input::ICommand DeleteCommand() { return m_deleteCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand DeleteAllCommand() { return m_deleteAllCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand RefreshCommand() { return m_refreshCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ExportCsvCommand() { return m_exportCsvCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ExportJsonCommand() { return m_exportJsonCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand OpenFolderCommand() { return m_openFolderCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand ToggleStarCommand() { return m_toggleStarCommand; }
        winrt::Microsoft::UI::Xaml::Input::ICommand RedownloadCommand() { return m_redownloadCommand; }

    private:
        void OnDelete(winrt::Windows::Foundation::IInspectable const& param);
        void OnDeleteAll();
        void OnRefresh();
        winrt::Windows::Foundation::IAsyncAction OnExportCsv();
        winrt::Windows::Foundation::IAsyncAction OnExportJson();
        void OnOpenFolder(winrt::Windows::Foundation::IInspectable const& param);
        void OnToggleStar(winrt::Windows::Foundation::IInspectable const& param);
        void OnRedownload(winrt::Windows::Foundation::IInspectable const& param);

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::YtDlpGui::Models::HistoryEntry> m_entries{
            winrt::single_threaded_observable_vector<winrt::YtDlpGui::Models::HistoryEntry>()
        };
        winrt::hstring m_searchText;
        winrt::hstring m_statusFilter;
        winrt::hstring m_platformFilter;
        winrt::hstring m_statusMessage;
        int m_totalCount{ 0 };

        std::shared_ptr<Services::HistoryDatabase> m_database;
        std::shared_ptr<Services::SettingsService> m_settingsService;
        std::shared_ptr<Services::CookieService> m_cookieService;

        winrt::Microsoft::UI::Xaml::Input::ICommand m_deleteCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_deleteAllCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_refreshCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_exportCsvCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_exportJsonCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_openFolderCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_toggleStarCommand{ nullptr };
        winrt::Microsoft::UI::Xaml::Input::ICommand m_redownloadCommand{ nullptr };
    };
}

namespace winrt::YtDlpGui::ViewModels::factory_implementation
{
    struct HistoryViewModel : HistoryViewModelT<HistoryViewModel, implementation::HistoryViewModel>
    {
    };
}
