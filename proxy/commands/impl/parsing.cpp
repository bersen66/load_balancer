#include <proxy/commands/impl/parsing.hpp>

namespace impl
{
	std::pair<std::string_view, std::optional<std::string_view>>
	SplitTwoStrict(std::string_view line_to_split, std::string_view delimeter)
	{
		const size_t pos = line_to_split.find(delimeter);
		if (pos == std::string_view::npos)
		{
			return {line_to_split, std::nullopt};
		} else
		{
			return {line_to_split.substr(0, pos),
			        line_to_split.substr(pos + delimeter.length())};
		}
	}

	std::vector<std::string_view>
	SplitLineIntoTokensViews(std::string_view line, std::string_view delimeter)
	{
		std::vector<std::string_view> result;

		do
		{
			auto [l, r] = SplitTwoStrict(line, delimeter);
			if (!l.empty())
			{
				result.push_back(std::string(l));
				line = r.value_or(std::string_view(""));
			}
		} while (!line.empty());

		return result;
	}

	std::vector<std::string>
	SplitLineIntoTokens(std::string_view line, std::string_view delimeter)
	{
		std::vector<std::string> result;

		do
		{
			auto [l, r] = SplitTwoStrict(line, delimeter);
			if (!l.empty())
			{
				result.push_back(std::move(std::string(l)));
				line = r.value_or("");

			}
		} while (!line.empty());

		return result;
	}

	std::pair<std::string_view, std::string_view>
	SplitTwo(std::string_view s, std::string_view delimiter)
	{
		const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
		return {lhs, rhs_opt.value_or("")};
	}

	std::string_view ReadToken(std::string_view& s, std::string_view delimiter)
	{
		const auto [lhs, rhs] = SplitTwo(s, delimiter);
		s = rhs;
		return lhs;
	}
} // namespace impl
