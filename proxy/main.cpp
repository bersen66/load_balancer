#include <iostream>
#include <cstddef>


int main(int argc, char** argv)
{
    try
    {
        std::cout << "Hello, world!\n";
    } 
    catch(const std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
