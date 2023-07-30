#include <proxy/commands/command_parser.hpp>
#include "impl/parsing.hpp"

[[nodiscard]] CommandPtr CommandParser::ParseCommand(std::string_view src) const
{
	const std::string& cmd_name = std::string(
			impl::ReadToken(src, /*delimiter=*/" "));
	if (command_map_.contains(cmd_name))
	{
		return command_map_.at(cmd_name)->Build(src);
	}
	return nullptr; // # TODO: better handling of invalid commands
}

void CommandParser::Insert(std::string_view name, CommandBuilderPtr value)
{
	command_map_[std::move(std::string(name))] = std::move(value);
}