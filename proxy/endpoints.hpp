#pragma once

#include <map>
#include <string>
#include <yaml-cpp/yaml.h>
#include <boost/asio/ip/tcp.hpp>

using Endpoint = boost::asio::ip::tcp::endpoint;

using EndpointMap = std::map<std::string, Endpoint>;

EndpointMap ParseEndpoints(YAML::const_iterator begin, YAML::const_iterator end);
