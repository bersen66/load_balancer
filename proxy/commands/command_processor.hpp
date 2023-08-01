#pragma once

#include <proxy/commands/command_parser.hpp>
#include <iostream>

class CommandProcessor
{
public:

	void ProcessCommands(std::istream& in = std::cin);

	template<typename CommandBuilderType, typename... Args>
	CommandProcessor& AddCommand(Args&& ... args)
	{
		std::unique_ptr<CommandBuilderType> builder
				= std::make_unique<CommandBuilderType>(
						std::forward<Args>(args)...);
		parser_.Insert(CommandBuilderType::kCommandName, std::move(builder));
		return *this;
	}

private:

	CommandParser parser_;
};
