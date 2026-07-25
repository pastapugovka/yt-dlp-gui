#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>

namespace winrt::YtDlpGui::ViewModels
{
    struct RelayCommand : winrt::implements<RelayCommand, Microsoft::UI::Xaml::Input::ICommand>
    {
        RelayCommand(std::function<void(winrt::Windows::Foundation::IInspectable const&)> execute)
            : m_execute(std::move(execute)), m_canExecute(nullptr) {}

        RelayCommand(std::function<void(winrt::Windows::Foundation::IInspectable const&)> execute,
                     std::function<bool(winrt::Windows::Foundation::IInspectable const&)> canExecute)
            : m_execute(std::move(execute)), m_canExecute(std::move(canExecute)) {}

        bool CanExecute(winrt::Windows::Foundation::IInspectable const& parameter) const override
        {
            if (m_canExecute)
                return m_canExecute(parameter);
            return true;
        }

        void Execute(winrt::Windows::Foundation::IInspectable const& args) const override
        {
            if (m_execute)
                m_execute(args);
        }

        winrt::event_token CanExecuteChanged(winrt::Windows::Foundation::TypedEventHandler<
            winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> const& handler)
        {
            return m_canExecuteChanged.add(handler);
        }

        void CanExecuteChanged(winrt::event_token const& token) noexcept
        {
            m_canExecuteChanged.remove(token);
        }

        void RaiseCanExecuteChanged()
        {
            m_canExecuteChanged(nullptr, nullptr);
        }

    private:
        std::function<void(winrt::Windows::Foundation::IInspectable const&)> m_execute;
        std::function<bool(winrt::Windows::Foundation::IInspectable const&)> m_canExecute;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<
            winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable>> m_canExecuteChanged;
    };
}
