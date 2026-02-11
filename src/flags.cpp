#include "flags.hpp"

namespace cpph
{
    Command parseCommand(const std::string& str) noexcept
    {
        for(int i = 0; i < (int)Command::_len; ++i)
        {
            if(str == Command_str[i])
                return (Command)i;
        }

        return Command::none;
    }

    static ProjectType parseProjectType(const std::string& str)
    {
        for(int i = 0; i < (int)ProjectType::_len; ++i)
        {
            if(str == ProjectType_str[i])
                return (ProjectType)i;
        }

        return ProjectType::none;
    }

    static DebuggerType parseDebuggerType(const std::string& str)
    {
        for(int i = 0; i < (int)DebuggerType::_len; ++i)
        {
            if(str == DebuggerType_str[i])
                return (DebuggerType)i;
        }

        return DebuggerType::none;
    }

    static Language parseLanguage(const std::string& str) noexcept
    {
        for(int i = 0; i < (int)Language::_len; ++i)
        {
            if(str == Language_str[i])
                return (Language)i;
        }

        return Language::none;
    }

    ProjectType extractProjectTypeFlag(const Args& args) noexcept
    {
        static const std::string flagNames[] { "t", "type" };

        for(auto& flag : flagNames)
        {
            auto iter = args.find(flag);
            if(iter == args.end()) continue;

            ProjectType result = parseProjectType(iter->second.front());
            if(result != ProjectType::none) return result;
        }
        
        return ProjectType::none;
    }

    DebuggerType extractDebuggerTypeFlag(const Args& args) noexcept
    {
        static const std::string flagNames[] { "t", "type" };

        for(auto& flag : flagNames)
        {
            auto iter = args.find(flag);
            if(iter == args.end()) continue;

            DebuggerType result = parseDebuggerType(iter->second.front());
            if(result != DebuggerType::none) return result;
        }
        
        return DebuggerType::none;
    }

    Language extractLanguageFlag(const Args& args) noexcept
    {
        static const char* flagNames[] { "l", "lang", "language" };
        static const Language defaultValue { Language::cpp };

        for(auto& flag : flagNames)
        {
            auto iter = args.find(flag);
            if(iter == args.end()) continue;

            Language result = parseLanguage(iter->second.front());
            if(result != Language::none) return result;
        }
        
        return defaultValue;
    }

    static const std::string& extractStringFlag(const Args& args, const std::vector<std::string> flagNames, const std::string& defaultValue)
    {
        static const std::string empty("");

        for(auto& flag : flagNames)
        {
            auto iter = args.find(flag);
            if(iter == args.end()) continue;

            const std::string& result = iter->second.front();
            if(!result.empty()) return result;
        }
        
        return defaultValue;
    }

    const std::string& extractProjectNameFlag(const Args& args) noexcept
    {
        static const std::vector<std::string> flagNames{ "n", "name" };
        static const std::string defaultValue { "NewProject" };

        return extractStringFlag(args, flagNames, defaultValue);
    }

    const std::string& extractCmakeVersionFlag(const Args& args) noexcept
    {
        static const std::vector<std::string> flagNames{ "c", "cmake-version" };
        static const std::string defaultValue { "3.22" };

        return extractStringFlag(args, flagNames, defaultValue);
    }

    const std::string& extractCStdFlag(const Args& args) noexcept
    {
        static const std::vector<std::string> flagNames{ "cs", "c-s", "cstd", "c-std" };
        static const std::string defaultValue { "23" };

        return extractStringFlag(args, flagNames, defaultValue);
    }

    const std::string& extractCppStdFlag(const Args& args) noexcept
    {
        static const std::vector<std::string> flagNames{ "cpps", "cpp-s", "cppstd", "cpp-std" };
        static const std::string defaultValue { "17" };

        return extractStringFlag(args, flagNames, defaultValue);
    }
}