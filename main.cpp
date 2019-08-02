#include <iostream>
#include "calculator.h"
#include "generic.h"

int main(int argc, char* argv[] )
{
    if(argc < 4)
    {
        calculator::printHelp();
    }
    else
    {
        std::printf("%ld",calculator::compute(argv,&argc));
    }
    return 0;
}
