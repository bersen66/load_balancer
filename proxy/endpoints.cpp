#include <proxy/endpoints.hpp>

using boost::asio::ip::tcp;
namespace ip = boost::asio::ip;

EndpointMap ParseEndpoints(YAML::const_iterator begin, YAML::const_iterator end)  
{

    std::map<std::string, tcp::endpoint> result;
    for (auto it = begin; it != end; ++it)
    {
        const auto& ep = *it;
        std::string ep_id = ep.first.as<std::string>();
        std::string ip_string = ep.second["ip"].as<std::string>();
        int port = ep.second["port"].as<int>(); 
        result[ep_id]= tcp::endpoint(ip::address::from_string(ip_string), port);
    }

    return result;
}
