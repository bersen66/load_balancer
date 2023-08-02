#pragma once

#include <map>
#include <string>
#include <string_view>
#include <boost/asio/ip/tcp.hpp>

using Endpoint = boost::asio::ip::tcp::endpoint;

using EndpointMap = std::map<std::string, Endpoint>;

Endpoint MakeEndpoint(std::string_view ip, std::string_view port);
