#pragma once

#include <memory> // std::shared_ptr
#include <map>
#include <boost/asio/ip/tcp.hpp>

struct SelectionStrategy
{
public:
	using Endpoint = boost::asio::ip::tcp::endpoint;
	using EndpointMap = std::map<std::string, Endpoint>;
public:
	SelectionStrategy() = default;

	virtual void InsertEndpoint(const Endpoint& ep) = 0;

	virtual void EraseEndpoint(const Endpoint& ep) = 0;

	virtual Endpoint Select() = 0;

	[[nodiscard]] virtual bool Empty() const = 0;

	virtual ~SelectionStrategy() = default;
};

using SelectorPtr = std::shared_ptr<SelectionStrategy>;