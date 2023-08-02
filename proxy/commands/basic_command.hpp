#pragma once

#include <memory>
#include <string_view>

struct BasicCommand
{
	virtual void Execute() = 0;

	virtual ~BasicCommand() = default;
};

using CommandPtr = std::shared_ptr<BasicCommand>;

struct BasicCommandBuilder
{
	virtual CommandPtr Build(std::string_view params) = 0;

	virtual ~BasicCommandBuilder() = default;
};

using CommandBuilderPtr = std::unique_ptr<BasicCommandBuilder>;

