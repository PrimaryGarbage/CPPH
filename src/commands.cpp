#include "commands.hpp"
#include "exception.hpp"
#include "utils.hpp"
#include "sources.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace cpph
{
    enum class ProjectType { none, exe, lib, test, _len };
    static const char* ProjectType_str[] {"none", "exe", "lib", "test"};

    const char* Command_str[] { "none", "init", "help" };

    static const char* defaultProjectName = "NewProject";
    static const char* defaultStdVersion = "17";
    static const char* defaultCmakeVersion = "3.22";
    static const char* buildDir = "./bin";

    void helpCommand()
    {
        std::cout << "\nCommands:\n";
        std::cout << "  init [-t, --type] [-n, --name] [-s --std] [c, --cmake-version] => init new project,\n";
        std::cout << "  help => print help,\n";
    }

    void initCommand(ProjectType type, std::string name, std::string stdVersion, std::string cmakeVersion)
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

    ProjectType parseProjectType(std::string str)
    {
        for(int i = 0; i < (int)ProjectType::_len; ++i)
        {
            if(str == ProjectType_str[i])
                return (ProjectType)i;
        }

        return ProjectType::none;
    }

    CommandContext createCommandContext(int argc, char* argv[])
    {
        CommandContext context;

        // parse command
        if(argc == 1)
        {
            context.command = Command::help;
        }
        else
        {
            std::string commandStr(argv[1]);
            context.command = Command::none;
            for(int i = 0; i < (int)Command::_len; ++i)
            {
                if(commandStr == Command_str[i])
                {
                    context.command = (Command)i;
                    break;
                }
            }
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
                context.args[flag].push_back(token);
            }
        }

        return context;
    }

    void executeCommand(CommandContext context)
    {
        switch(context.command)
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
                    ProjectType type = context.args.contains("type") ? parseProjectType(context.args["type"].front()) : 
                        context.args.contains("t")? parseProjectType(context.args["t"].front()) : ProjectType::exe;
                    if(type == ProjectType::none) 
                    {
                        std::cout << "Invalid project type." << std::endl;
                        break;
                    }

                    std::string name = context.args.contains("name") ? context.args["name"].front() : 
                        context.args.contains("n") ? context.args["n"].front() : defaultProjectName;
                    std::string stdVersion = context.args.contains("std") ? context.args["std"].front() :
                        context.args.contains("s") ? context.args["s"].front() : defaultStdVersion; 
                    std::string cmakeVersion = context.args.contains("cmake-version") ? context.args["cmake-version"].front() :
                        context.args.contains("c") ? context.args["c"].front() : defaultCmakeVersion;

                    initCommand(type, name, stdVersion, cmakeVersion);
                    break;
                }
            default:
                throw CPPH_EXCEPTION("Forbidden command value.");
        }
    }


}