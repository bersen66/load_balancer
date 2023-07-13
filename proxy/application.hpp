#pragma once 
#include <memory>
#include <string>

class Application;
using AppPtr = std::unique_ptr<Application>;


class Application
{
public:
    static AppPtr Create(int argc, char** argv);

    Application(const std::string& path_to_config);

    int Run() noexcept;
private:
    std::string config_path_;
};
