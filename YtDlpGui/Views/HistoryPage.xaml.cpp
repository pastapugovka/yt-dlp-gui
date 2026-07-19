#include "pch.h"
#include "HistoryPage.xaml.h"

namespace winrt::YtDlpGui::Views::implementation
{
    HistoryPage::HistoryPage()
    {
        InitializeComponent();
        m_viewModel = winrt::make<winrt::YtDlpGui::ViewModels::HistoryViewModel>();
        m_viewModel.Initialize(DispatcherQueue());
        m_viewModel.PropertyChanged([this](winrt::Windows::Foundation::IInspectable const&,
                                           winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e)
        {
            if (e.PropertyName() == L"Entries" || e.PropertyName() == L"TotalCount")
                UpdateEmptyState();
        });
        UpdateEmptyState();
    }

    void HistoryPage::UpdateEmptyState()
    {
        bool isEmpty = m_viewModel.Entries().Size() == 0;
        EmptyStatePanel().Visibility(isEmpty
            ? winrt::Microsoft::UI::Xaml::Visibility::Visible
            : winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
        HistoryListView().Visibility(isEmpty
            ? winrt::Microsoft::UI::Xaml::Visibility::Collapsed
            : winrt::Microsoft::UI::Xaml::Visibility::Visible);
    }

    void HistoryPage::HistoryListView_ItemClick(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& args)
    {
        // Handle item click - open details or navigate to download
    }
}
