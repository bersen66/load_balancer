#include <iostream>
#include <yaml-cpp/yaml.h>

#include <boost/asio/detached.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/as_tuple.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/strand.hpp>

#include <proxy/server.hpp>
#include <proxy/session.hpp>
#include <proxy/parse_endpoints.hpp>

using boost::asio::ip::tcp;
using boost::asio::use_awaitable;
using boost::asio::detached;
using boost::asio::as_tuple;
using boost::asio::make_work_guard;
using boost::asio::co_spawn;
using boost::asio::make_strand;

template<typename T>
using awaitable = boost::asio::awaitable<T>;

Server Server::FromConfig(const YAML::Node& config)
{
	int threads_num = config["threads_num"].as<int>();
	int listen_port = config["port"].as<int>();
	EndpointMap endpoints = ParseEndpoints(config["endpoints"].begin(),
	                                       config["endpoints"].end());
	SelectorPtr selector = MakeSelector<RoundRobinStrategy>(endpoints);
	return {threads_num, listen_port, std::move(endpoints), selector};
}

Server::Server(int threads_num, int listen_port, EndpointMap endpoints,
               SelectorPtr selector)
		: ioc_(threads_num)
		  , wg_(make_work_guard(ioc_))
		  , acceptor_(ioc_, tcp::endpoint(tcp::v4(), listen_port))
		  , endpoints_(std::move(endpoints))
		  , selector_(selector)
		  , threads_num_(threads_num)
{
	co_spawn(ioc_, DoAccept(), detached);
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

void Server::EraseEndpoint(const std::string& id)
{

}

void Server::Run()
{
	auto& exec = ioc_;

	for (int i = 0; i < threads_num_; i++)
	{
		tp.emplace_back([&exec]() {
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
	for (auto& worker: tp)
	{
		worker.join();
	}
}

awaitable<void> Server::StartSession(tcp::socket client)
{
	try
	{
		tcp::socket server_socket(ioc_);
		auto endpoint = selector_->Select();
		auto [err] = co_await server_socket.async_connect(endpoint, as_tuple(
				use_awaitable));

		if (!err)
		{
			Session s(std::move(client), std::move(server_socket));
			co_await s.Run();
		} else
		{
			std::cout << "Session error: " << err.message() << std::endl;
		}

	}
	catch (const std::exception& exc)
	{
		std::cout << "Session exception: " << exc.what() << std::endl;
	}

	co_return;
}

awaitable<void> Server::DoAccept()
{

	auto executor = co_await boost::asio::this_coro::executor;
	while (true)
	{
		auto [err, client] = co_await acceptor_.async_accept(
				as_tuple(use_awaitable));
		if (err)
		{
			std::cout << "Listener error: " << err.message() << std::endl;
			break;
		}
		std::cout << "Accepted: " << std::endl;
		co_spawn(make_strand(executor), StartSession(std::move(client)),
		         detached);
	}

}
