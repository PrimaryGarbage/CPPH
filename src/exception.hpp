#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <string>

#define CPPH_EXCEPTION(message) Exception(message, __FILE__, __LINE__)

namespace cpph
{
    class Exception
    {
    private:
        std::string message;
    public:
        Exception(std::string message) : message("[CPPH EXCEPTION] =>" + message) {}
        Exception(std::string message, std::string file, int line) : message("[CPPH EXCEPTION] " + file + ":" + std::to_string(line) + " => " + message) {}

        inline std::string what() const { return message; }
    };
}
#endif // __EXCEPTION_HPP__