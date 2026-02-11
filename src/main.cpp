#include "exception.hpp"
#include "command_execution.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    try
    {
        auto context = cpph::createCommandContext(argc, argv);
        cpph::executeCommand(context.get());
    }
    catch (cpph::Exception ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}

