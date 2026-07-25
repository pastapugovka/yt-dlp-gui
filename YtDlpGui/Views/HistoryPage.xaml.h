#pragma once

#include "HistoryPage.xaml.g.h"
#include "../ViewModels/HistoryViewModel.h"

namespace winrt::YtDlpGui::Views::implementation
{
    struct HistoryPage : HistoryPageT<HistoryPage>
    {
        HistoryPage();
        ~HistoryPage();

        winrt::YtDlpGui::ViewModels::HistoryViewModel ViewModel() const { return m_viewModel; }

        void HistoryListView_ItemClick(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& args);

    private:
        void UpdateEmptyState();

        winrt::YtDlpGui::ViewModels::HistoryViewModel m_viewModel{ nullptr };
        winrt::event_token m_propertyChangedToken{};
    };
}

namespace winrt::YtDlpGui::Views::factory_implementation
{
    struct HistoryPage : HistoryPageT<HistoryPage, implementation::HistoryPage>
    {
    };
}
