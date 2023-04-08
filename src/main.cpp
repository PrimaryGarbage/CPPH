#include "exception.hpp"
#include "commands.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    try
    {
        cpph::CommandContext context = cpph::createCommandContext(argc, argv);
        cpph::executeCommand(context);
    }
    catch (cpph::Exception ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}

