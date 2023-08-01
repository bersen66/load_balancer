#include <string>
#include <cstdlib>
#include <iostream>
#include <utility>

#include <yaml-cpp/yaml.h>
#include <boost/program_options.hpp>

#include <proxy/application.hpp>
#include <proxy/server.hpp>
#include <proxy/commands/commands.hpp>

namespace opt = boost::program_options;

Application::Application(std::string path_to_config)
		: config_path_(std::move(path_to_config))
{}

AppPtr Application::Create(int argc, char** argv)
{
	opt::positional_options_description p;
	p.add("help", -1);

	opt::options_description desc("Allowed options");

	// .clang-format off
	desc.add_options()
			    ("help,h", "produce help message")
			    ("config,c", opt::value<std::string>(),
			     "specify path to config-file");
	// .clang-format on

	opt::variables_map vm;

	// .clang-format off
	opt::store(opt::command_line_parser(argc, argv)
			           .options(desc)
			           .positional(p)
			           .run(), vm);
	// .clang-format on

	opt::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return nullptr;
	}

	if (!vm.count("config"))
	{
		std::cerr << "path to config file must be specified!" << std::endl;
		return nullptr;
	}

	Application result(vm["config"].as<std::string>());
	return std::make_unique<Application>(std::move(result));
}

int Application::Run() noexcept
{
	try
	{
		YAML::Node config = YAML::LoadFile(config_path_);
		Server server = Server::FromConfig(config);
		server.Run();

		CommandProcessor cp;
		// .clang-format off
		cp.AddCommand<cmd::ShutdownBuilder>()
		  .AddCommand<cmd::ListBuilder>(server, std::cout)
		;
		// .clang-format on

		cp.ProcessCommands();
	}
	catch (const cmd::Shutdown::ShutdownException& exc)
	{
		std::cout << "Bye!" << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cerr << "Unhandled exception: " << exc.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
