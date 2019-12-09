#include <iostream>
#include <cstring>
#include <iterator>
#include "calculator.h"
#include "generic.h"

int main(int argc, char* argv[] )
{    
    //essentially just wraps the calculator class 
    //so that it can interract with a shell
    if(argc >2 && std::strcmp(argv[1],"help") ==0 )
    { 
        calculator::printOperatorHelp(argv[2]);
    }
    else if(argc < 3)
    {
        calculator::printHelp();
    }
    else
    {
        try
        {
            std::printf("%f\n",calculator::compute(argv,&argc));
        }
        catch (...)
        {
            std::cout << ("\033[0;31mAn error occured when evaluating:\033[0m\n\t");
            std::copy(argv+1, argv+argc, std::ostream_iterator<const char*>(std::cout, " "));
            std::cout << "\n";
        }
    }
    return 0;
}
