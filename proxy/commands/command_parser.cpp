#include <proxy/commands/command_parser.hpp>
#include "impl/parsing.hpp"
#include <proxy/commands/exceptions/command_not_found.hpp>

[[nodiscard]] CommandPtr CommandParser::ParseCommand(std::string_view src) const
{
	const std::string& cmd_name = std::string(
			impl::ReadToken(src, /*delimiter=*/" "));
	if (command_map_.contains(cmd_name))
	{
		return command_map_.at(cmd_name)->Build(src);
	}
    throw cmd::CommandNotFound(cmd_name);
}

void CommandParser::Insert(std::string_view name, CommandBuilderPtr value)
{
	command_map_[std::move(std::string(name))] = std::move(value);
}
