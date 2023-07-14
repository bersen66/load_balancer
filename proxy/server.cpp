#include <proxy/server.hpp>

Server Server::FromConfig(const YAML::Node& config)
{
    return Server();    
}


void Server::SetupStrategy(SelectorPtr new_strategy)
{
    std::cout << "Switched!" << std::endl;
    strategy_ = new_strategy; 
}
