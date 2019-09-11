#ifndef CALCUCATOR_CLASS_IS_LOADED
#define CALCUCATOR_CLASS_IS_LOADED
#include <stack>
class calculator
{
    public:
    const static char* OPERATORS[];
    const static char* SINGLE_ARGUMENT_OPERATORS[];
    
    static void printHelp();

    static void printOperatorHelp(char* c);
    
    static bool isValidOperator(char*c,const char* ref[], const int ln);
    
    template <typename T>
    static void fillstacks(std::stack <T>* st,char* arguments[], int *numberOfArguments, bool (*function)(T));
    
    static bool isValidExpression(char* arguments[], int *numberOfArguments);

    static double evaluateSingleValueExpression(char** val,char** oper);

    static double evaluate(char** val1,char** val2,char** oper);
    
    static double compute(char* arguments[],int *numberOfArguments);
};
#endif
