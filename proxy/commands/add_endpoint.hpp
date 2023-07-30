#pragma once

#include <iostream>
#include <proxy/commands/basic_command.hpp>

// #TODO: endpoint parsing
// #TODO: interaction with server
// #TODO: rewrite
class AddEndpoint final : public BasicCommand
{
public:
	// It's just an example
	void Execute() override
	{
		std::cout << "Hello, World!" << std::endl;
	}
};

class AddEndpointBuilder final : public BasicCommandBuilder
{
public:
	static constexpr std::string_view kCommandName = "Add";

	CommandPtr Build(std::string_view params) override
	{
		auto result = std::make_shared<AddEndpoint>();
		return result;
	}

};