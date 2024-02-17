#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include <unordered_map>
#include <string>
#include <vector>


namespace cpph
{
    enum class Command { none, init, help, vscodedebug, _len };
    inline const char* Command_str[] { "none", "init", "help", "vscodedebug" };

    struct CommandContext
    {
        Command command;
        std::unordered_map<std::string, std::vector<std::string>> args;
    };

    CommandContext createCommandContext(int argc, char* argv[]);
    void executeCommand(CommandContext context);
}

#endif // __COMMANDS_HPP__