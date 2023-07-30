#pragma once

#include <string>
#include <map>
#include <string_view>

#include <proxy/commands/basic_command.hpp>

class CommandParser
{
public:
	[[nodiscard]] CommandPtr ParseCommand(std::string_view src) const;

	void Insert(std::string_view name, CommandBuilderPtr value);
private:
	std::map<std::string, CommandBuilderPtr> command_map_;
};