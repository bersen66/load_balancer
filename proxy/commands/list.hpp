#pragma once

#include <proxy/commands/basic_command.hpp>
#include <proxy/server.hpp>
#include <iostream>

namespace cmd
{

	class List final : public ::BasicCommand
	{
	public:

		explicit List(Server& server, std::ostream& out);
		void Execute() override;

	private:
		Server& server_;
		std::ostream& out_;
	};

	class ListBuilder final : public ::BasicCommandBuilder
	{
	public:
		static constexpr std::string_view
		kCommandName = "list";

		explicit ListBuilder(Server& server, std::ostream& out = std::cout);
		CommandPtr Build(std::string_view params) override;
	private:
		Server& server_;
		std::ostream& out_;
	};
} // namespace cmd
