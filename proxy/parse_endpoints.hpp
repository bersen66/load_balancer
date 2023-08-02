#pragma once

#include <proxy/endpoints.hpp>
#include <yaml-cpp/yaml.h>

EndpointMap
ParseEndpoints(YAML::const_iterator begin, YAML::const_iterator end);