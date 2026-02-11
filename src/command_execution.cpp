#include "command_execution.hpp"
#include "exception.hpp"
#include "utils.hpp"
#include "sources.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "flags.hpp"

namespace cpph
{
    static const char* buildDir = "./bin";

    static void helpCommand()
    {
        std::cout << "\nCommands:\n";
        std::cout << "  init [-t, --type] [-n, --name] [-l --lang] [-s --std] [c, --cmake-version] => init new project,\n";
        std::cout << "    -> valid project types: " + toString(ProjectType_str + 1, (size_t)ProjectType::_len - 1) + ",\n";
        std::cout << "    -> valid languages: " + toString(Language_str + 1, (size_t)Language::_len - 1) + ",\n";
        std::cout << "    -> other flags can have any string value.\n";
        std::cout << "  vscodedebug [-t, --type] => create launch.json file for vscode,\n";
        std::cout << "    -> valid types: " + toString(DebuggerType_str + 1, (size_t)DebuggerType::_len - 1) + ",\n";
        std::cout << "  help => print help.\n";
    }

    static void initCommand(ProjectType type, std::string name, std::string stdVersion, std::string cmakeVersion)
    {
        namespace fs = std::filesystem;

        std::string bashSrc;
        std::string cmakeSrc;
        std::string mainSrc(MAIN_SRC);
        std::string gitignoreSrc(GITIGNORE_SRC);

        switch(type)
        {
            case ProjectType::exe:
            {
                bashSrc = BASH_EXE_SRC;
                cmakeSrc = CMAKE_EXE_SRC;
                break;
            }
            case ProjectType::lib:
            {
                bashSrc = BASH_LIB_SRC;
                cmakeSrc = CMAKE_LIB_SRC;
                break;
            }
            case ProjectType::test:
            {
                fs::create_directory("./tests");

                std::ofstream testsFile("./tests/tests.cpp", std::ios::trunc);
                testsFile << TESTS_SRC;
                testsFile.close();

                std::ofstream testingFile("./tests/testing.hpp", std::ios::trunc);
                testingFile << TESTING_SRC;
                testingFile.close();

                std::string makefileSrc = replaceString(MAKEFILE_TEST_SRC, "{{cpp_standard}}", "c++" + stdVersion);
                std::ofstream makefile("./tests/Makefile", std::ios::trunc);
                makefile << makefileSrc;
                makefile.close();

                std::cout << "Test project initialized successfully." << std::endl;
                return;
            }
            default:
                throw CPPH_EXCEPTION("Invalid project type!");
        }

        bashSrc = replaceString(bashSrc, "{{project_name}}", name);
        bashSrc = replaceString(bashSrc, "{{build_dir}}", buildDir);
        cmakeSrc = replaceString(cmakeSrc, "{{project_name}}", name);
        cmakeSrc = replaceString(cmakeSrc, "{{cmake_min_version}}", cmakeVersion);
        cmakeSrc = replaceString(cmakeSrc, "{{cpp_standard}}", stdVersion);
        gitignoreSrc = replaceString(gitignoreSrc, "{{build_dir_name}}", replaceString(buildDir, "./", ""));

        fs::create_directory("./src");
        fs::create_directories("./external");

        std::ofstream bashFile("./build.sh", std::ios::trunc);
        bashFile << bashSrc;
        bashFile.close();

        std::ofstream cmakeFile("./CMakeLists.txt", std::ios::trunc);
        cmakeFile << cmakeSrc;
        cmakeFile.close();

        std::ofstream mainFile("./src/main.cpp", std::ios::trunc);
        mainFile << mainSrc;
        mainFile.close();

        std::ofstream gitignoreFile("./.gitignore", std::ios::trunc);
        gitignoreFile << gitignoreSrc;
        gitignoreFile.close();

        std::cout << "Project initialized successfully." << std::endl;
    }

    static void vsCodeDebugCommand(DebuggerType type, std::string projectName)
    {
        namespace fs = std::filesystem;

        fs::create_directory("./.vscode");
        std::string fileSrc;

        switch(type)
        {
            case DebuggerType::gdb:
                {
                    fileSrc = VSCODEDEBUG_GDB_SRC;
                    break;
                }
            case DebuggerType::lldb:
                {
                    fileSrc = VSCODEDEBUG_LLDB_SRC;
                    break;
                }
            default:
                throw CPPH_EXCEPTION("Invalid debugger type!");
        }

        fileSrc = replaceString(fileSrc, "{{project_name}}", projectName);

        std::ofstream file("./.vscode/launch.json");
        file << fileSrc;
        file.close();

        std::cout << "VS Code launch file created successfully." << std::endl;
    }


    std::unique_ptr<CommandContext> createCommandContext(int argc, char* argv[])
    {
        CommandContext* context = new CommandContext();

        // parse command
        if(argc == 1)
        {
            context->command = Command::help;
        }
        else
        {
            std::string commandStr(argv[1]);
            context->command = parseCommand(commandStr);
        }

        // parse args
        std::string flag;
        for(int i = 2; i < argc; ++i)
        {
            std::string token(argv[i]);
            if(token.starts_with('-'))
            {
                if(token.starts_with("--"))
                    flag = token.substr(2);
                else
                    flag = token.substr(1);
            }
            else
            {
                context->args[flag].push_back(token);
            }
        }

        return std::unique_ptr<CommandContext>(context);
    }

    void executeCommand(const CommandContext* context)
    {
        switch(context->command)
        {
            case Command::none:
                {
                    std::cout << "Invalid command" << std::endl;
                    break;
                }
            case Command::help:
                {
                    helpCommand();
                    break;
                }
            case Command::init:
                {
                    ProjectType type = extractProjectTypeFlag(context->args);

                    if(type == ProjectType::none) 
                    {
                        std::cout << "Invalid project type." << std::endl;
                        break;
                    }

                    Language language = extractLanguageFlag(context->args);

                    std::string name = extractProjectNameFlag(context->args);
                    std::string stdVersion = extractStdFlag(context->args);
                    std::string cmakeVersion = extractCmakeVersionFlag(context->args);

                    initCommand(type, name, stdVersion, cmakeVersion);
                    break;
                }
            case Command::vscodedebug:
                {
                    DebuggerType type = extractDebuggerTypeFlag(context->args);

                    if(type == DebuggerType::none)
                    {
                        std::cout << "Invalid debugger type." << std::endl;
                        break;
                    }

                    std::string name = extractProjectNameFlag(context->args);

                    vsCodeDebugCommand(type, name);
                    break;
                }
            default:
                throw CPPH_EXCEPTION("Invalid command value.");
        }
    }
}