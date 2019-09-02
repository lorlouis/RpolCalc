#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <string>
#include <cmath>
#include "calculator.h"
#include "generic.h"


const char* calculator::OPERATORS[] = {"x","*","/","+","-","^","pow","nroot"};
const int OPERATORS_LN = 8;//Don't forget to update when adding functionnalities
const char* calculator::SINGLE_ARGUMENT_OPERATORS[] = {"cos"};
const int SINGLE_ARGUMENT_OPERATORS_LN = 1;//Don't forget to update when adding functionnalities
void calculator::printHelp()
{
    std::cout << "\t\033[1;31mTHIS CALCULATOR ONLY SUPPORTS INTEGERS\033[0m\n";
    
    std::cout << "Operators: \n\t    ";
    for(int i =0; i< OPERATORS_LN;i++)
    {
        std::printf("%c\t",OPERATORS[i]);
    }
    std::cout << "\n  x multiplies two numbers\n  / divides the first number by the second\n  + sums two numbers\n  - substracs the second number from the fist number\n  ^ raises the first number to the second number's power\n";
}

bool calculator::isValidOperator(char* c,const char* ref[], const int ln)
{
    int i =0;
    while(std::strcmp(c,ref[i]) != 0 && i < ln)
    {
        i++;
    }
    return (i < ln);
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
    while((calculator::isValidOperator(arguments[i],OPERATORS,OPERATORS_LN) || 
          generic::isNumber(arguments[i])) && i < *numberOfArguments)
    {
        if(calculator::isValidOperator(arguments[i],OPERATORS,OPERATORS_LN))
        {
            nbOp++;
        }
        else if(generic::isNumber(arguments[i]))
        {
            nbNum++;
        }
        i++;
    }
    if(i!= *numberOfArguments || nbOp != nbNum-1)
    {
        return false;
    }
    return true;
}

double calculator::evaluateSingleValueExpression(char** val,char** oper)
{
    if(strcmp(*oper, "cos") ==0)
    {
        return std::cos(std::stod(*val));
    }
    else
    {
        throw std::runtime_error("invalid operator");
    }
}

double calculator::evaluate(char** val1,char** val2,char** oper)
{
    if(strcmp(*oper,"pow") == 0)
    {
        return std::pow(std::stod(*val1),std::stod(*val2));
    }
    else if(strcmp(*oper,"nroot") == 0)
    {
        return std::pow(std::stod(*val1),1.0f/std::stod(*val2));
    }
    //all of the single character operators will be handled in a switch 
    //for the sake of performance and code readability.
    else
    {
        switch(*oper[0])
        {
            case('^'):
                return std::pow(std::stod(*val1),std::stod(*val2));
            case('*'):
            case('x'):
                return std::stod(*val1) * std::stod(*val2);
            case('/'):
                if(val1 !=0)
                {
                    return std::stod(*val2) / std::stod(*val1);
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
}

//calculates the values
double calculator::compute(char* arguments[],int *numberOfArguments)
{
    std::stack <char*> workingStack;
    std::stack <char*> bufferStack;
    int i =1;
    for(i=1;i < *numberOfArguments;i++)
    {

        if(calculator::isValidOperator(arguments[i], OPERATORS,OPERATORS_LN)||generic::isNumber(arguments[i]))
        {
            bufferStack.push(arguments[i]);
        }
    }
    while(!bufferStack.empty())
    {
        char* oper = {};
        char* val1 = {};
        char* val2 = {};
        if(calculator::isValidOperator(bufferStack.top(), OPERATORS,OPERATORS_LN))
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
                        int ret = std::snprintf(buffer,sizeof(buffer),"%f",calculator::evaluate(&val1,&val2,&oper));
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
        else
        {
            workingStack.push(bufferStack.top());
            bufferStack.pop();
        }
    }
    throw std::runtime_error("Syntax error"); 
}
