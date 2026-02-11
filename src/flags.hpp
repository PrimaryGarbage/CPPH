#ifndef __FLAGS_HPP__
#define __FLAGS_HPP__

#include <string>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::vector<std::string>> Args;

namespace cpph
{

    enum class Command { none, init, help, vscodedebug, _len };
    inline const char* Command_str[] { "none", "init", "help", "vscodedebug" };

    enum class ProjectType { none, exe, lib, test, _len };
    static const char* ProjectType_str[] {"none", "exe", "lib", "test"};

    enum class DebuggerType { none, gdb, lldb, _len };
    static const char* DebuggerType_str[] {"none", "gdb", "lldb"};

    enum class Language { none, c, cpp, _len };
    static const char* Language_str[] {"none", "c", "cpp"};


    Command parseCommand(const std::string& str) noexcept;

    ProjectType extractProjectTypeFlag(const Args& args) noexcept;
    DebuggerType extractDebuggerTypeFlag(const Args& args) noexcept;
    Language extractLanguageFlag(const Args& args) noexcept;
    const std::string& extractProjectNameFlag(const Args& args) noexcept;
    const std::string& extractCmakeVersionFlag(const Args& args) noexcept;
    const std::string& extractStdFlag(const Args& args) noexcept;
}

#endif // __FLAGS_HPP__