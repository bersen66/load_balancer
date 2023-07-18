#pragma once

#include "selection_strategy.hpp"

class RoundRobinStrategy final : public SelectionStrategy
{
public:
	explicit RoundRobinStrategy(const EndpointMap& endpoints);

	void InsertEndpoint(const Endpoint& ep) override;

	void EraseEndpoint(const Endpoint& ep) override;

	Endpoint Select() override;

	[[nodiscard]] bool Empty() const override;

private:
	std::vector<Endpoint> endpoints_;
};

template<typename Selector, typename... Args>
SelectorPtr MakeSelector(Args&& ... args)
{
	return std::make_shared<Selector>(std::forward<Args>(args)...);
}
