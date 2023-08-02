#pragma once

#include <proxy/commands/basic_command.hpp>
#include <proxy/endpoints.hpp>

class Server;

namespace cmd
{

	class Insert final : public ::BasicCommand
	{
	public:

		Insert(Server& server, std::string id, Endpoint ep);

		void Execute() override;

	private:
		Server& server_;
		std::string id_;
		Endpoint ep_;
	};

	class InsertBuilder final : public ::BasicCommandBuilder
	{
	public:

		static constexpr std::string_view kCommandName = "insert";

		explicit InsertBuilder(Server& server);

		CommandPtr Build(std::string_view params) override;

	private:
		Server& server_;
	};

} // namespace cmd