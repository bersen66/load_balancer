#pragma once

#include <map>
#include <string>
#include <yaml-cpp/yaml.h>
#include <boost/asio/ip/tcp.hpp>




auto ParseEndpoints(YAML::const_iterator begin, YAML::const_iterator end) 
    -> std::map<std::string, boost::asio::ip::tcp::endpoint>;
