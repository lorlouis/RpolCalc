#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <string>
#include <cmath>
#include "calculator.h"
#include "generic.h"


const char* calculator::OPERATORS[] = {"x","*","/","+","-","^","pow","nroot","atan2"};
const int OPERATORS_LN = 9;//Don't forget to update when adding functionnalities
const char* OPERATORS_HELP[] = {"a b x : times a by b","a b * : times a by b","a b / : divides a by b, b != 0","a b + : adds a and b", "a b - : substracts a from b","a b ^ : raises a to the power of b", " a b pow : raises a to the power of b","a b nroot : returns the bth root of a", "a b atan2 : returns θ between a ray starting at 0,0 passing through a,b and the X axis"};
const char* calculator::SINGLE_ARGUMENT_OPERATORS[] = {"cos","sin","tan","acos","asin","atan","cosh","sinh","tanh","acosh","asinh","atanh","exp"};
const int SINGLE_ARGUMENT_OPERATORS_LN = 13;//Don't forget to update when adding functionnalities
const char* SINGLE_ARGUMENT_OPERATORS_HELP[] = {"a cos : return the cos (in radian) of a","a sin : return the sin (in radian) of a","a tan : return the tan (in radian) of a","a acos : return the inverse of cos(a) (in radian)","a asin : return the inverse of sin(a) (in radian)","a atan : return the inverse of tan(a) (in radian)","a cosh : return the hyperbolic cosine of a (in radian)","a sinh : return the hyperbolic sine of a (in radian)","a tanh : return the hyperbolic tangeant of a (in radian)","a acosh : return the inverse of the hyperbolic cosine of a (in radian)","a asinh : return the inverse of the hyperbolic sine of a (in radian)","a atanh : return the inverse of the hyperbolic tangeant of a (in radian)","a exp : returns e^a"};

void calculator::printHelp()
{
    std::cout << "Multiple Argument Operators:\n";
    for(int i =0; i< OPERATORS_LN;i++)
    {
        std::printf("%s\t%s\n",OPERATORS[i],OPERATORS_HELP[i]);
    } 
    std::printf("\nSingle Argument Opetators:\n");
    for(int i =0; i< SINGLE_ARGUMENT_OPERATORS_LN;i++)
    {
        std::printf("%s\t%s\n",SINGLE_ARGUMENT_OPERATORS[i],SINGLE_ARGUMENT_OPERATORS_HELP[i]);
    }
}
void calculator::printOperatorHelp(char* c)
{
    int i =0;
    printf("Operator usage:\n");
    while(i < OPERATORS_LN && std::strcmp(c,OPERATORS[i]) != 0)
    {
        i++;
    }
    if(i < OPERATORS_LN)
    {
        printf("%s\n",OPERATORS_HELP[i]);
    }
    else
    {
        i =0;
        while(i < SINGLE_ARGUMENT_OPERATORS_LN && std::strcmp(c,SINGLE_ARGUMENT_OPERATORS[i]) != 0)
        {
            i++;
        }
        if(i < SINGLE_ARGUMENT_OPERATORS_LN)
        {
            printf("%s",SINGLE_ARGUMENT_OPERATORS_HELP[i]);
        }
        else
        {
            calculator::printHelp();
        }
    }
}
bool calculator::isValidOperator(char* c,const char* ref[], const int ln)
{
    int i =0;
    while(i < ln && std::strcmp(c,ref[i]) != 0)
    {
        i++;
    }
    return (i < ln);
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
    else if(strcmp(*oper, "sin") == 0)
    {
        return std::sin(std::stod(*val));
    }
    else if(strcmp(*oper, "tan") == 0)
    {
        return std::tan(std::stod(*val));
    }
    else if(strcmp(*oper, "acos") == 0)
    {
        return std::acos(std::stod(*val));
    }
    else if(strcmp(*oper, "asin") == 0)
    {
        return std::asin(std::stod(*val));
    }
    else if(strcmp(*oper, "atan") == 0)
    {
        return std::atan(std::stod(*val));
    }
    else if(strcmp(*oper, "cosh") == 0)
    {
        return std::cosh(std::stod(*val));
    }
    else if(strcmp(*oper, "sinh") == 0)
    {
        return std::sinh(std::stod(*val));
    }
    else if(strcmp(*oper, "tanh") == 0)
    {
        return std::tanh(std::stod(*val));
    }
    else if(strcmp(*oper, "acosh") == 0)
    {
        return std::acosh(std::stod(*val));
    }
    else if(strcmp(*oper, "asinh") == 0)
    {
        return std::asinh(std::stod(*val));
    }
    else if(strcmp(*oper, "atanh") == 0)
    {
        return std::atanh(std::stod(*val));
    }
    else if(strcmp(*oper, "exp") == 0)
    {
        return std::exp(std::stod(*val));
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
        return std::pow(std::stod(*val2),std::stod(*val1));
    }
    else if(strcmp(*oper,"nroot") == 0)
    {
        return std::pow(std::stod(*val2),1.0f/std::stod(*val1));
    }
    else if(strcmp(*oper,"atan2") == 0)
    {
        return std::atan2(std::stod(*val1),1.0f/std::stod(*val2));
    }
    //all of the single character operators will be handled in a switch 
    //for the sake of performance and code readability.
    else
    {
        switch(*oper[0])
        {
            case('^'):
                return std::pow(std::stod(*val2),std::stod(*val1));
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
        if(calculator::isValidOperator(arguments[i], OPERATORS,OPERATORS_LN)||generic::isNumber(arguments[i])||calculator::isValidOperator(arguments[i],SINGLE_ARGUMENT_OPERATORS,SINGLE_ARGUMENT_OPERATORS_LN))
        {
            bufferStack.push(arguments[i]);
        }
    }
    while(!bufferStack.empty())
    {
        char* oper = {};
        char* val1 = {};
        char* val2 = {};
        if(calculator::isValidOperator(bufferStack.top(),SINGLE_ARGUMENT_OPERATORS,SINGLE_ARGUMENT_OPERATORS_LN))
        {
            oper = bufferStack.top();
            bufferStack.pop();
            if(generic::isNumber(bufferStack.top()))
            {
                val1 = bufferStack.top();
                bufferStack.pop();
                char buffer[100];
                if(bufferStack.empty() && workingStack.empty())
                {
                    return calculator::evaluateSingleValueExpression(&val1,&oper);
                }
                else
                {
                    int ret = std::snprintf(buffer,sizeof(buffer),"%f",calculator::evaluateSingleValueExpression(&val1,&oper));
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
                bufferStack.push(oper);
            }
        }
        if(!bufferStack.empty() && calculator::isValidOperator(bufferStack.top(), OPERATORS,OPERATORS_LN))
        {
            oper = bufferStack.top();
            bufferStack.pop();
            if(generic::isNumber(bufferStack.top()))
            {
                val1 = bufferStack.top();
                bufferStack.pop();
                if(!bufferStack.empty() && generic::isNumber(bufferStack.top()))
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
                    workingStack.push(val1);
                    workingStack.push(oper);
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
