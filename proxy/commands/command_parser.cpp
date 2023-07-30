#include <proxy/commands/command_parser.hpp>


[[nodiscard]] CommandPtr CommandParser::ParseCommand(std::string_view src) const
{
	return command_map_.at(std::string(src))->Build();
}

void CommandParser::Insert(std::string_view name, CommandBuilderPtr value)
{
	command_map_[std::move(std::string(name))] = std::move(value);
}