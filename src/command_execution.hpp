#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include <unordered_map>
#include <string>
#include <vector>
#include "flags.hpp"
#include <memory>

namespace cpph
{
    struct CommandContext
    {
        Command command;
        std::unordered_map<std::string, std::vector<std::string>> args;
    };

    std::unique_ptr<CommandContext> createCommandContext(int argc, char* argv[]);
    void executeCommand(const CommandContext* context);
    
}

#endif // __COMMANDS_HPP__