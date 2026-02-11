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

    ProjectType parseProjectType(const std::string& str)
    {
        for(int i = 0; i < (int)ProjectType::_len; ++i)
        {
            if(str == ProjectType_str[i])
                return (ProjectType)i;
        }

        return ProjectType::none;
    }

    DebuggerType parseDebuggerType(const std::string& str)
    {
        for(int i = 0; i < (int)DebuggerType::_len; ++i)
        {
            if(str == DebuggerType_str[i])
                return (DebuggerType)i;
        }

        return DebuggerType::none;
    }

    Language parseLanguage(const std::string& str) noexcept
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
            ProjectType result = parseProjectType(args.at(flag).front());
            if(result != ProjectType::none) return result;
        }
        
        return ProjectType::none;
    }

    DebuggerType extractDebuggerTypeFlag(const Args& args) noexcept
    {
        static const std::string flagNames[] { "t", "type" };

        for(auto& flag : flagNames)
        {
            DebuggerType result = parseDebuggerType(args.at(flag).front());
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
            Language result = parseLanguage(args.at(flag).front());
            if(result != Language::none) return result;
        }
        
        return defaultValue;
    }

    static const std::string& extractStringFlag(const Args& args, const std::vector<std::string> flagNames, const std::string& defaultValue)
    {
        static const std::string empty("");

        for(auto& flag : flagNames)
        {
            const std::string& result = args.at(flag).front();
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
        static const std::vector<std::string> flagNames{ "s", "std" };
        static const std::string defaultValue { "3.22" };

        return extractStringFlag(args, flagNames, defaultValue);
    }

    const std::string& extractStdFlag(const Args& args) noexcept
    {
        static const std::vector<std::string> flagNames{ "c", "cmake-version" };
        static const std::string defaultValue { "17" };

        return extractStringFlag(args, flagNames, defaultValue);
    }
}