#pragma once

#include <atomic>
#include <vector>

#include <proxy/selectors/selection_strategy.hpp>

class RoundRobinStrategy final : public SelectionStrategy
{
public:
	explicit RoundRobinStrategy(const EndpointMap& endpoints);

	void InsertEndpoint(const Endpoint& ep) override;

	void EraseEndpoint(const Endpoint& ep) override;

	std::optional<Endpoint> Select() override;

	[[nodiscard]] bool Empty() const override;
private:
	std::vector<Endpoint> endpoints_;
	std::atomic<std::size_t> offset_;
};