#pragma once

#include <map>
#include <string>
#include <boost/asio/ip/tcp.hpp>

using Endpoint = boost::asio::ip::tcp::endpoint;

using EndpointMap = std::map<std::string, Endpoint>;


