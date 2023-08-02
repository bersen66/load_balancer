#include <proxy/commands/remove.hpp>
#include <proxy/server.hpp>
#include <proxy/commands/impl/parsing.hpp>

namespace cmd
{
	Remove::Remove(Server& server, std::string id)
			: server_(server)
			  , id_(std::move(id))
	{}

	void Remove::Execute()
	{
		server_.EraseEndpoint(id_);
	}

	RemoveBuilder::RemoveBuilder(Server& server)
			: server_(server)
	{}

	CommandPtr RemoveBuilder::Build(std::string_view params)
	{
		std::string_view id = impl::ReadToken(params,/*delimiter=*/ " ");
		// # TODO: BETTER ERROR HANDLING
		return std::make_shared<Remove>(server_, std::move(std::string(id)));
	}
} // namespace cmd

