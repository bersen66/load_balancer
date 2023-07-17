#pragma once

#include <memory>

#include <boost/asio/awaitable.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

class Session
{
private:
	template<typename T>
	using awaitable = boost::asio::awaitable<T>;
	using tcp = boost::asio::ip::tcp;
	using error_code = boost::system::error_code;
public:
	Session(tcp::socket client, tcp::socket server);

	awaitable<void> Run();

private:
	tcp::socket client_;
	tcp::socket server_;
};


