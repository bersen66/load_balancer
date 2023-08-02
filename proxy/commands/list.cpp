#include <proxy/commands/list.hpp>

namespace cmd
{
	List::List(Server& server, std::ostream& out)
		: server_(server)
		, out_(out)
	{}

	void List::Execute()
	{
		server_.Flush(out_);
	}

	CommandPtr ListBuilder::Build(std::string_view params)
	{
		auto result = std::make_shared<List>(server_, out_);
		return result;
	}

	ListBuilder::ListBuilder(Server& server, std::ostream& out)
		: server_(server)
		, out_(out)
	{}
} // namespace cmd
