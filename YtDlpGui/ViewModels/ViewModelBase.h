#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <string>
#include <functional>

namespace winrt::YtDlpGui::ViewModels
{
    struct ViewModelBase
    {
        ViewModelBase() = default;
        virtual ~ViewModelBase() = default;

        winrt::event_token PropertyChanged(
            Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return m_propertyChanged.add(handler);
        }

        void PropertyChanged(winrt::event_token const& token) noexcept
        {
            m_propertyChanged.remove(token);
        }

        void RaisePropertyChanged(std::wstring const& propertyName)
        {
            m_propertyChanged(nullptr, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }

        void SetDispatcher(winrt::Microsoft::UI::Dispatching::DispatcherQueue const& dispatcher)
        {
            m_dispatcher = dispatcher;
        }

        void RunOnUI(std::function<void()> const& action)
        {
            if (m_dispatcher)
            {
                m_dispatcher.TryEnqueue([action]()
                {
                    action();
                });
            }
            else
            {
                action();
            }
        }

    protected:
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        winrt::Microsoft::UI::Dispatching::DispatcherQueue m_dispatcher{ nullptr };
    };
}
