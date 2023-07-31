#pragma once

#include <exception>
#include <string>
#include <string_view>

namespace cmd
{
	class CommandNotFound final : public std::exception
	{
	public:
		explicit CommandNotFound(std::string_view name);

		[[nodiscard]] const char* what() const noexcept override;
	private:
		std::string msg_;
	};
} // namespace cmd
