#include <iostream>

#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/as_tuple.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>

#include <proxy/session.hpp>

template<typename T>
using awaitable = boost::asio::awaitable<T>;

using boost::asio::ip::tcp;
using boost::asio::use_awaitable;
using boost::asio::as_tuple;
using boost::asio::co_spawn;
using boost::asio::buffer;
using boost::asio::cancellation_state;

namespace sys = boost::system;

Session::Session(tcp::socket client, tcp::socket server)
		: client_(std::move(client))
		  , server_(std::move(server))
{
}

template<std::size_t buffer_size_bytes = 1024>
awaitable<sys::error_code> ForwardMessage(tcp::socket& src, tcp::socket& dest)
{
	std::array<char, buffer_size_bytes> data{};
	auto [recive_req_err, bytes_readed] =
			co_await src.async_read_some(buffer(data),
			                             as_tuple(use_awaitable));
	if (recive_req_err)
	{
		co_return recive_req_err;
	}

	auto [send_req_err, bytes_written] = co_await
			async_write(dest, buffer(data, bytes_readed),
			            as_tuple(use_awaitable));
	if (send_req_err)
	{
		co_return send_req_err;
	}
	auto result = sys::errc::make_error_code(sys::errc::success);
	co_return result;
}

awaitable<sys::error_code> Communicate(tcp::socket& client, tcp::socket& server)
{
	namespace this_coro = boost::asio::this_coro;
	while (true)
	{
		cancellation_state cs = co_await this_coro::cancellation_state;
		if (cs.cancelled() != boost::asio::cancellation_type::none)
		{
			break;
		}
		auto ec = co_await ForwardMessage(client, server);
		if (ec)
		{
			co_return ec;
		}
	}

	co_return sys::errc::make_error_code(sys::errc::success);
}

awaitable<void> Session::Run()
{
	using namespace boost::asio::experimental::awaitable_operators;
	std::variant<sys::error_code, sys::error_code> results
			= co_await (Communicate(client_, server_) ||
			            Communicate(server_, client_));
	co_return;
}