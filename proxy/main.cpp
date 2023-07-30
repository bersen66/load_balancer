#include <cstdlib>
#include <proxy/application.hpp>


int main(int argc, char** argv)
{
	AppPtr app = Application::Create(argc, argv);
	return app ? app->Run() : EXIT_FAILURE;
}
