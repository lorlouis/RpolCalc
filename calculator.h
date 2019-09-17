//lorlouis 
#ifndef CALCUCATOR_CLASS_IS_LOADED
#define CALCUCATOR_CLASS_IS_LOADED
#include <stack>
class calculator
{
    public:
    //a list of all supported operators see .cpp for declaration
    const static char* OPERATORS[];
    //the number operators in OPERATORS[]
    const static int   OPERATORS_LN;
    //a list of the help messages for each operator at the same
    //index as the operator in OPERATORS[]
    //should be built into a dictionnary
    const static char* OPERATORS_HELP[];

    //a list of all supported single argument operators see .cpp
    const static char* SINGLE_ARGUMENT_OPERATORS[];
    //the number operators in SINGLE_ARGUMENT_OPERATORS[]
    const static int SINGLE_ARGUMENT_OPERATORS_LN;
    //a list of the help messages for each single argument operator
    //at the same index as the operator in SINGLE_ARGUMENT_OPERATORS[]
    //should really be built into a dictionnary
    const static char* SINGLE_ARGUMENT_OPERATORS_HELP[];
    
    
    //Prints all the operators with their respective help message
    static void printHelp();
    
    //Prints an help message according to the operator passed as an argument
    //if the argument is invalid it will call calculator::PrintHelp()
    //[TAKES]
    //a char* (c) containing the operator
    static void printOperatorHelp(char* c);
    
    //Returns true if the c is in the array ref; False if otherwise
    //[TAKES] 
    //a char* (c) to test
    //an array of char* (ref)
    //the length of the array (ln)
    static bool isValidOperator(char*c,const char* ref[], const int ln);
    
    //Returns True if the expression is in a valid reverse polish notation
    //[TAKES] 
    //an array of char* (arguments)
    //a pointer to an integer containing the length of arguments[]
    static bool isValidExpression(char* arguments[], int *numberOfArguments);

    //Evaluates a value according to the given operator
    //[TAKES]
    //a pointer to a value (val)
    //a pointer to an operator (oper)
    static double evaluateSingleValueExpression(char** val,char** oper);

    //Evaluates 2 values according to the given operator
    //[TAKES]
    //a pointer to a value (val1)
    //a pointer to another value (val2)
    //a pointer to an operator (oper)
    static double evaluate(char** val1,char** val2,char** oper);
   
    //Evaluates recursively the array of arguments 
    //till it returns or throws an error message
    static double compute(char* arguments[],int *numberOfArguments);
};
#endif
