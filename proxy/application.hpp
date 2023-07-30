#pragma once

#include <memory>
#include <string>


class Application;

using AppPtr = std::unique_ptr<Application>;



class Application
{
public:
	static AppPtr Create(int argc, char** argv);

	int Run() noexcept;

protected:

	explicit Application(std::string  path_to_config);
private:
	std::string config_path_;

};
