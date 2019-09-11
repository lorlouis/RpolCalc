#include <iostream>
#include <cstring>
#include "calculator.h"
#include "generic.h"

int main(int argc, char* argv[] )
{    
    
    if(argc >2 && std::strcmp(argv[1],"help") ==0 )
    {
        char h[] = "sin"; 
        calculator::printOperatorHelp(h);
    }
    else if(argc < 3)
    {
        calculator::printHelp();
    }
    else
    {
        std::printf("%f\n",calculator::compute(argv,&argc));
    }
    return 0;
}
