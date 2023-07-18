#pragma once

#include <memory> // std::shared_ptr
#include <map>
#include <proxy/endpoints.hpp>

struct SelectionStrategy
{
	SelectionStrategy() = default;

	virtual void InsertEndpoint(const Endpoint& ep) = 0;

	virtual void EraseEndpoint(const Endpoint& ep) = 0;

	virtual Endpoint Select() = 0;

	[[nodiscard]] virtual bool Empty() const = 0;

	virtual ~SelectionStrategy() = default;
};

using SelectorPtr = std::shared_ptr<SelectionStrategy>;