#pragma once

#include <proxy/commands/basic_command.hpp>
#include <string>

class Server;

namespace cmd
{

	class Remove final : public ::BasicCommand
	{
	public:

		Remove(Server& server, std::string id);

		void Execute() override;

	private:
		Server& server_;
		std::string id_;
	};

	class RemoveBuilder final : public ::BasicCommandBuilder
	{
	public:

		static constexpr std::string_view kCommandName = "remove";

		explicit RemoveBuilder(Server& server);

		CommandPtr Build(std::string_view params) override;

	private:
		Server& server_;
	};

} // namespace cmd