#pragma once

#include <optional>
#include <memory> // std::shared_ptr

#include <proxy/endpoints.hpp>

struct SelectionStrategy
{
	SelectionStrategy() = default;

	virtual void InsertEndpoint(const Endpoint& ep) = 0;

	virtual void EraseEndpoint(const Endpoint& ep) = 0;

	virtual std::optional<Endpoint> Select() = 0;

	[[nodiscard]] virtual bool Empty() const = 0;

	virtual ~SelectionStrategy() = default;
};

using SelectorPtr = std::shared_ptr<SelectionStrategy>;

template<typename Selector, typename... Args>
SelectorPtr MakeSelector(Args&& ... args)
{
	return std::make_shared<Selector>(std::forward<Args>(args)...);
}