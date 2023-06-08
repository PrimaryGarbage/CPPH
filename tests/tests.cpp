#include "testing.hpp"
#include <iostream>

int main()
{
    try
    {
        //////////////////// 
		// executeTests();//
		////////////////////

        std::cout << "Tests finished succesfully!" << std::endl;
    }
    catch(prim::TestException ex)
    {
        std::cout << "Test run failed:\n";
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
