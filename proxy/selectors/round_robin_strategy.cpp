#include <proxy/selectors/round_robin_strategy.hpp>

using tcp = boost::asio::ip::tcp;

std::vector<Endpoint> GetValues(const EndpointMap& endpoints)
{
	std::vector<Endpoint> result;
	result.reserve(endpoints.size());

	for (const auto& [k, v] : endpoints)
	{
		result.push_back(v);
	}

	return result;
}

RoundRobinStrategy::RoundRobinStrategy(const EndpointMap& endpoints)
	: endpoints_(GetValues(endpoints))
	, offset_(0)
{
}

void RoundRobinStrategy::InsertEndpoint(const Endpoint& ep)
{
	endpoints_.push_back(ep);
}

void RoundRobinStrategy::EraseEndpoint(const Endpoint& ep)
{
	auto it = std::find(endpoints_.begin(), endpoints_.end(), ep);
	if (it == endpoints_.end())
	{
		return;
	}
	endpoints_.erase(it);
	if (!endpoints_.empty())
	{
		offset_ = offset_ % endpoints_.size();
	}
	else
	{
		offset_ = 0;
	}

}

std::optional<Endpoint> RoundRobinStrategy::Select()
{
	if (endpoints_.empty())
	{
		return std::nullopt;
	}

	auto result = endpoints_[offset_++];
	offset_ = offset_ % endpoints_.size();
	return std::make_optional(std::move(result));
}

bool RoundRobinStrategy::Empty() const
{
	return endpoints_.empty();
}

