#include <string>
#include <iostream>

#include <proxy/commands/command_processor.hpp>


void CommandProcessor::ProcessCommands(std::istream& in)
{
	for (std::string line; std::getline(in, line);)
	{
		std::string_view line_view(line);
		CommandPtr cmd = parser_.ParseCommand(line_view);
		cmd->Execute();
	}
}