#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <string>
#include <cmath>
#include "calculator.h"
#include "generic.h"

//public
const char calculator::OPERATORS[] = {'*','x','/','+','-','^'};
void calculator::printHelp()
{
    std::cout << "Operators: \n";
    for(int i =0; i< generic::size(OPERATORS);i++)
    {
        std::printf("\t%c",OPERATORS[i]);
    }
    std::cout << "\nx multiplies two numbers\n / divides the first number by the second\n + sums two numbers\n - substracs the second number from the fist number\n ^ elevates the first number to the second number's power\n";
}
bool calculator::isValidOperator(char *c)
{
    int i =0;
    while(*c != OPERATORS[i] && i < generic::size((OPERATORS)))
    {
        i++;
    }
    return (i < generic::size(OPERATORS));
}
//­­­­­­­TOO CONFUSING FOR NEW PLAYERS­­­­­­­--­
//takes a pointer to a stack and fills it with an 
//element from an array if the function pointer 
//returns true when supplied with said element
//        and does it recursively
template <typename T>
void calculator::fillstacks(std::stack <T>* st,char* arguments[], int *numberOfArguments, bool (*function)(T))
{
    if(*function(arguments[*numberOfArguments]))
    {
        st->push(arguments[*numberOfArguments]);
    }
    *numberOfArguments--;
    calculator::fillstacks(st,arguments,numberOfArguments,function);
}

bool calculator::isValidExpression(char* arguments[], int *numberOfArguments)
{
    int nbNum=0;
    int nbOp = 0;
    int i = 1;
    while((calculator::isValidOperator(arguments[i]) || 
          generic::isNumber(arguments[i])) && i < *numberOfArguments)
    {
        if(calculator::isValidOperator(arguments[i]))
        {
            nbOp++;
        }
        else if(generic::isNumber(arguments[i]))
        {
            nbNum++;
        }
        i++;
    }

    std::printf("%i op\t%i num\n",nbOp,nbNum);
    if(i!= *numberOfArguments || nbOp != nbNum-1)
    {
        return false;
    }
    return true;
}

long calculator::evaluate(char** val1,char** val2,char** oper)
{
    switch(*oper[0])
    {
        case('^'):
            return std::pow(std::stod(*val1),std::stod(*val2));
        case('x'):
            return std::stod(*val1) * std::stod(*val2);
        case('/'):
            if(val2 !=0)
            {
                return std::stod(*val1) / std::stod(*val2);
            }
            throw std::runtime_error("division by 0");
        case('+'):
            return std::stod(*val1) + std::stod(*val2);
        case('-'):
            return std::stod(*val2) - std::stod(*val1);
        default:
            throw std::runtime_error("invalid operator");
    }
}

//calculates the values
long calculator::compute(char* arguments[],int *numberOfArguments)
{
    std::stack <char*> workingStack;
    std::stack <char*> bufferStack;
    int i =1;
    for(i=1;i < *numberOfArguments;i++)
    {

        if(calculator::isValidOperator(arguments[i])||generic::isNumber(arguments[i]))
        {
            bufferStack.push(arguments[i]);
        }
    }
    while(!bufferStack.empty())
    {
        char* oper = {};
        char* val1 = {};
        char* val2 = {};
        if(!calculator::isValidOperator(bufferStack.top()))
        {
            workingStack.push(bufferStack.top());
            bufferStack.pop();
        }
        else
        {
            oper = bufferStack.top();
            bufferStack.pop();
            if(generic::isNumber(bufferStack.top()))
            {
                val1 = bufferStack.top();
                bufferStack.pop();
                if(generic::isNumber(bufferStack.top()))
                {
                    val2 = bufferStack.top();
                    bufferStack.pop();
                    char buffer[100];
                    if(bufferStack.empty() && workingStack.empty())
                    {
                        return calculator::evaluate(&val1,&val2,&oper);
                    }
                    else
                    {    
                        int ret = std::snprintf(buffer,sizeof(buffer),"%ld",calculator::evaluate(&val1,&val2,&oper));
                        bufferStack.push(buffer);
                        //unwinding the working stack
                        while(!workingStack.empty())
                        {
                            bufferStack.push(workingStack.top());
                            workingStack.pop();
                        }
                    }
                }
                else
                {
                    workingStack.push(oper);
                    workingStack.push(val1);
                }
            }
            else
            {
                workingStack.push(oper);
            }
            
        }
    }
    throw std::runtime_error("Syntax error"); 
}
