#include <proxy/commands/shutdown.hpp>

namespace cmd
{
	void Shutdown::Execute()
	{
		throw ShutdownException{};
	}

	const char* Shutdown::ShutdownException::what() const noexcept
	{
		return message_.c_str();
	}

	CommandPtr ShutdownBuilder::Build(std::string_view params)
	{
		auto result = std::make_shared<Shutdown>();
		return result;
	}

} // namespace cmd


