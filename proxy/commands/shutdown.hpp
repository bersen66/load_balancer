#pragma once

#include <proxy/commands/basic_command.hpp>


namespace cmd
{

	class Shutdown final : public ::BasicCommand
	{
	public:

		class ShutdownException : public std::exception
		{
		public:
			[[nodiscard]] const char* what() const noexcept override;

		private:
			std::string message_;
		};

		void Execute() override;

	private:

	};

	class ShutdownBuilder final : public ::BasicCommandBuilder
	{
	public:
		static constexpr std::string_view kCommandName = "shutdown";

		CommandPtr Build(std::string_view params) override;

	};
} // namespace cmd