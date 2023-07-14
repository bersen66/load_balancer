#pragma once
#include <iostream>
#include <proxy/selectors.hpp>

class Server 
{
public:

    static Server FromConfig(const YAML::Node& config);
    
    void SetupStrategy(SelectorPtr new_strategy);
private:
    boost::asio::io_context executor_;
    SelectorPtr strategy_;

};
