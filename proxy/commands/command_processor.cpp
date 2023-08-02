#include <string>
#include <iostream>

#include <proxy/commands/command_processor.hpp>
#include <proxy/commands/shutdown.hpp>

void CommandProcessor::ProcessCommands(std::istream& in)
{
	for (std::string line; std::getline(in, line);)
	{
		try
		{
			std::string_view line_view(line);
			CommandPtr cmd = parser_.ParseCommand(line_view);
			if (cmd)
			{
				cmd->Execute();
			}
			else
			{
				std::cout << std::endl;
			}

		}
		catch(const cmd::Shutdown::ShutdownException& exc)
		{
			throw exc;
		}
		catch (const std::exception& exc)
		{
			std::cerr << "Exception: " << exc.what() << std::endl;
		}

	}
}
