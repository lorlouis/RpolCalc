#ifndef CALCUCATOR_CLASS_IS_LOADED
#define CALCUCATOR_CLASS_IS_LOADED
#include <stack>
class calculator
{
    public:
    const static char* OPERATORS[];
    
    static void printHelp();
    
    static bool isValidOperator(char*c);
    
    template <typename T>
    static void fillstacks(std::stack <T>* st,char* arguments[], int *numberOfArguments, bool (*function)(T));
    
    static bool isValidExpression(char* arguments[], int *numberOfArguments);

    static double evaluate(char** val1,char** val2,char** oper);
    
    static double compute(char* arguments[],int *numberOfArguments);
};
#endif
