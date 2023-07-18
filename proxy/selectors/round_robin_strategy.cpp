#include <proxy/selectors/round_robin_strategy.hpp>

using tcp = boost::asio::ip::tcp;

RoundRobinStrategy::RoundRobinStrategy(const EndpointMap& endpoints)
{

}


void RoundRobinStrategy::InsertEndpoint(const tcp::endpoint& ep)
{

}

void RoundRobinStrategy::EraseEndpoint(const Endpoint& ep)
{

}

Endpoint RoundRobinStrategy::Select()
{
	return {};
}

bool RoundRobinStrategy::Empty() const
{
	return false;
}

