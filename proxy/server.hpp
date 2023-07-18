#pragma once

#include <thread>

#include <boost/asio/io_context.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <proxy/selectors/selectors.hpp>

class Server
{
private:
	template<typename T>
	using awaitable = boost::asio::awaitable<T>;
	template<typename T>
	using executor_work_guard = boost::asio::executor_work_guard<T>;
	using tcp = boost::asio::ip::tcp;
	using io_context = boost::asio::io_context;
public:

	static Server FromConfig(const YAML::Node& config);

	~Server();

	Server(const Server& srv) = delete;

	Server& operator=(const Server& other) = delete;

	Server(Server&& other) = delete;

	void SetupStrategy(SelectorPtr new_strategy);

	void Run();

	void InsertEndpoint(const std::string& id, tcp::endpoint ep);

	void EraseEndpoint(const std::string& id);

	void Shutdown();

private:
	Server(int threads_num, int listen_port, EndpointMap endpoints,
	       SelectorPtr selector);

	awaitable<void> DoAccept();

	void JoinWorkers();

	awaitable<void> StartSession(tcp::socket client);

private:
	io_context ioc_;
	executor_work_guard<io_context::executor_type> wg_;
	std::vector<std::thread> tp;
	tcp::acceptor acceptor_;
	int threads_num_;
	EndpointMap endpoints_;
	SelectorPtr selector_;
};

