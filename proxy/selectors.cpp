#include <proxy/selectors.hpp>


void RoundRobinStrategy::InsertEndpoint(const Endpoint& ep) 
{
    
}

void RoundRobinStrategy::EraseEndpoint(const Endpoint& ep) 
{

}

Endpoint RoundRobinStrategy::Select() 
{
    return {};
}

bool RoundRobinStrategy::Empty() const 
{
    return false;
}
