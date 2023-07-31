#include <proxy/commands/exceptions/command_not_found.hpp>
#include <fmt/core.h>


namespace cmd
{

	CommandNotFound::CommandNotFound(std::string_view name)
		: msg_(fmt::format("Command {} is not found", name))
	{}

	const char* CommandNotFound::what() const noexcept
	{
		return msg_.c_str();
	}

} // namespace cmd

