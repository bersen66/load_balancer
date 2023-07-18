#pragma once

#include <proxy/endpoints.hpp>

EndpointMap
ParseEndpoints(YAML::const_iterator begin, YAML::const_iterator end);