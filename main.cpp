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
        std::printf("%f\n",calculator::compute(argv,&argc));
    }
    return 0;
}
