#include <iostream>
#include "calculator.h"
#include "generic.h"

int main(int argc, char* argv[] )
{
    calculator::printHelp();

    std::printf("%ld",calculator::compute(argv,&argc));
    return 0;
}
