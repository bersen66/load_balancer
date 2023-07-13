#include <string>
#include <cstdlib>
#include <iostream>

#include <yaml-cpp/yaml.h>
#include <boost/program_options.hpp>

#include <proxy/application.hpp>


namespace opt = boost::program_options;

Application::Application(const std::string& path_to_config)
    : config_path_(path_to_config)
{}

AppPtr Application::Create(int argc, char** argv) 
{
    opt::positional_options_description p;
    p.add("help", -1);

    opt::options_description desc("Allowed options");

    // .clang-format off
    desc.add_options()
        ("help,h", "produce help message")
        ("config,c", opt::value<std::string>(), "specify path to config-file")
    ;
    // .clang-format on
    
    opt::variables_map vm;

    opt::store(opt::command_line_parser(argc, argv)
                .options(desc)
                .positional(p)
                .run()
               , vm);

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
    return std::make_unique<Application>(vm["config"].as<std::string>());
}

int Application::Run() noexcept
{
    try
    {
        YAML::Node config = YAML::LoadFile(config_path_);
        std::cout << config["holla"].as<std::string>() << std::endl;
    } 
    catch (const std::exception& exc)
    {
        std::cerr << "Unhandled exception: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}