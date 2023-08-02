#include <proxy/endpoints.hpp>
#include <boost/lexical_cast.hpp>

Endpoint MakeEndpoint(std::string_view ip, std::string_view port)
{
	int p = boost::lexical_cast<int>(port);
	std::string ip_addr = std::string(ip);
	// # TODO: BETTER ERROR HANDLING
	return {boost::asio::ip::address::from_string(ip_addr),
	        static_cast<unsigned short >(p)};
}