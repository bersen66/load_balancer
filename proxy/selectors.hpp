#pragma once

#include <memory> // std::shared_ptr
#include <proxy/endpoints.hpp>

struct SelectionStrategy
{
    virtual void InsertEndpoint(const Endpoint& ep) = 0;
    virtual void EraseEndpoint(const Endpoint& ep) = 0;
    virtual Endpoint Select() = 0;
    virtual bool Empty() const = 0;
    virtual ~SelectionStrategy() = default;
};


using SelectorPtr = std::shared_ptr<SelectionStrategy>;


class RoundRobinStrategy final : public SelectionStrategy
{
public:
    void InsertEndpoint(const Endpoint& ep) override;
    void EraseEndpoint(const Endpoint& ep) override;
    Endpoint Select() override;
    bool Empty() const override;
private:

};


template<typename Selector, typename... Args>
SelectorPtr MakeSelector(Args&&... args)
{
    return std::make_shared<Selector>(std::forward<Args>(args)...); 
}
