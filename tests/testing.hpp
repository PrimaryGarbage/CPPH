#ifndef __TESTING_HPP__
#define __TESTING_HPP__

#include <string>

namespace prim
{
    class TestException
    {
    private:
        std::string message;
    public:
        TestException() : TestException("Test failed.") {}
        TestException(std::string message) : message(message) {}
    
        inline std::string what() const noexcept
        {
            return message;
        }
    };

    #define ASSERT(expression, message) if(!(expression)) throw prim::TestException(std::string(message) + " >> File: " + __FILE__ + "; Line: " + std::to_string(__LINE__));
}

#endif // __TESTING_HPP__
