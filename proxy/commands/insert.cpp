#include <proxy/commands/insert.hpp>
#include <proxy/commands/impl/parsing.hpp>
#include  <proxy/server.hpp>

namespace cmd
{

	Insert::Insert(Server& server, std::string id, Endpoint ep)
			: server_(server)
			  , id_(std::move(id))
			  , ep_(std::move(ep))
	{}

	void Insert::Execute()
	{
		server_.InsertEndpoint(id_, ep_);
	}

	[[maybe_unused]] InsertBuilder::InsertBuilder(Server& server)
			: server_(server)
	{

	}

	CommandPtr InsertBuilder::Build(std::string_view params)
	{
		std::string_view id = impl::ReadToken(params);
		std::string_view ip = impl::ReadToken(params);
		std::string_view port = impl::ReadToken(params);

		// #TODO: ERROR HANDLING
		return std::make_shared<Insert>(server_, std::string(id),
		                                MakeEndpoint(ip, port));
	}


} // namespace cmd

