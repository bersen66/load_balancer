#pragma once
#include <proxy/selectors.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/awaitable.hpp>
#include <coroutine>
#include <boost/asio.hpp>

class Server 
{
public:

    static Server FromConfig(const YAML::Node& config);
    
    ~Server();
    
    Server(const Server& srv) = delete;
    Server& operator=(const Server& other) = delete;
    Server(Server&& other) = delete;

    void SetupStrategy(SelectorPtr new_strategy);

    void Serve();
    
    void InsertEndpoint(const std::string& id, 
                        boost::asio::ip::tcp::endpoint ep);

    void EraseEnpoint(const std::string& id);

    void Shutdown();

private:
    Server(int threads_num, int listen_port
           , EndpointMap endpoints, SelectorPtr selector);

    boost::asio::awaitable<void> DoListen();

    void JoinWorkers();
private:
    boost::asio::io_context ioc_;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> wg_;
    std::vector<std::thread> tp;
    boost::asio::ip::tcp::acceptor acceptor_;
    int threads_num_;
    EndpointMap endpoints_;
    SelectorPtr selector_;
};

