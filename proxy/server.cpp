#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include <math.h>
#include <yaml-cpp/yaml.h>
#include <proxy/server.hpp>


using boost::asio::ip::tcp;
using boost::asio::use_awaitable;
using boost::asio::detached;
using boost::asio::as_tuple;
using boost::asio::make_work_guard;

template<typename T>
using awaitable=boost::asio::awaitable<T>;

Server Server::FromConfig(const YAML::Node& config)
{
    
    int threads_num = config["threads_num"].as<int>();
    int listen_port = config["port"].as<int>();
    EndpointMap endpoints = ParseEndpoints(config["endpoints"].begin()
                                           , config["endpoints"].end());
    SelectorPtr selector = MakeSelector<RoundRobinStrategy>();
    return Server(threads_num, listen_port, std::move(endpoints), selector);    
}

Server::Server(int threads_num, int listen_port
               , EndpointMap endpoints, SelectorPtr selector)
   : ioc_(threads_num)
   , wg_(make_work_guard(ioc_))  
   , acceptor_(ioc_, tcp::endpoint(tcp::v4(), listen_port))
   , endpoints_(std::move(endpoints))
   , selector_(selector)
   , threads_num_(threads_num)
{
    boost::asio::co_spawn(ioc_, DoListen(), detached);
    tp.reserve(threads_num_);
}


void Server::SetupStrategy(SelectorPtr new_strategy)
{
    selector_ = new_strategy; 
}

void Server::InsertEndpoint(const std::string& id, tcp::endpoint ep)
{
    selector_->InsertEndpoint(ep);
}

void Server::EraseEnpoint(const std::string &id)
{
    
}

void Server::Serve()
{
     auto& exec = ioc_;
     
     for (int i = 0; i < threads_num_; i++)
     {
        tp.emplace_back([&exec](){
            exec.run();
        });
     }     
}


Server::~Server()
{
    Shutdown();
    JoinWorkers();
}

void Server::Shutdown()
{
    ioc_.stop();
}

void Server::JoinWorkers()
{
    for (auto& worker : tp)
    {
        worker.join();
    }
}

awaitable<void> echo_once(tcp::socket& socket)
{
    char data[128];
    std::size_t n = co_await socket.async_read_some(boost::asio::buffer(data), use_awaitable);
    co_await async_write(socket, boost::asio::buffer(data, n), use_awaitable);
}

awaitable<void> echo(tcp::socket socket)
{
    try
    {
      for (;;)
      {
        // The asynchronous operations to echo a single chunk of data have been
        // refactored into a separate function. When this function is called, the
        // operations are still performed in the context of the current
        // coroutine, and the behaviour is functionally equivalent.
        co_await echo_once(socket);
      }
    }
    catch (std::exception& e)
    {
      std::printf("echo Exception: %s\n", e.what());
    }
}



awaitable<void> Server::DoListen()
{
    
    auto executor = co_await boost::asio::this_coro::executor;
    while (true)
    {
        auto [err, client] = co_await acceptor_.async_accept(as_tuple(use_awaitable));
        if (err)
        {
            std::cout << "Listener error: " << err.message() << std::endl;
            break;
        }
        co_spawn(make_strand(executor), echo(std::move(client)), detached);
    }

}
