#include "pch.h"
#include "functions.h"
#include "stmpLib.h"

namespace stmp
{
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    std::vector<Operation, std::allocator<Operation>> second)
    {
        if (first.empty()) {
            first = second;
        } else {
            for (auto it = second.begin(); it != second.end(); it++) 
                first.push_back(*it);
        }           
    }

    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    Operation second)
    { first.push_back(second); }

    Operator defineOperator(std::string& op)
    {
        if (op == "negate")
            return Operator::NEGATE;
        else if (op == "sqrt")
            return Operator::SQRT;
        else if (op == "sqr")
            return Operator::SQR;
        else if (op == "cbrt")
            return Operator::CBRT;
        else if (op == "exp")
            return Operator::EXP;
        else if (op == "ln")
            return Operator::LOGE;
        else if (op == "logtwo")
            return Operator::LOG2;
        else if (op == "lg")
            return Operator::LOG10;
        else if (op == "pow")
            return Operator::POWER;
        else
            return Operator::NONE;
    }

    Operator defineOperator(char op)
    {
        if (op == '*')
            return Operator::MULTIPLY;
        else if (op == '/')
            return Operator::DIVIDE;
        else if (op == '-')
            return Operator::SUBTRACT;
        else if (op == '+')
            return Operator::ADD;
        else
            return Operator::NONE;
    }

    std::string makeSpacesOnly(const std::string &str)
    {
        std::string strCopy = str;
        for (int i = 1; i < strCopy.size(); i++)
        {
            if (strCopy[i] == '+' || strCopy[i] == '-' || strCopy[i] == '/' || strCopy[i] == '*')
            {
                strCopy.insert(strCopy.begin()+i+1, ' ');
                strCopy.insert(strCopy.begin()+i, ' ');
                i++;
            }            
        }
        return strCopy;
    }

    std::string makeSpacesAndNoNegate(const std::string &str)
    {
        std::string strCopy = makeSpacesOnly(str);
        for (int i = 1; i < strCopy.size(); i++)
            if (strCopy[i] == 'n')
                if (strCopy.substr(i, 6) == "negate")
                    strCopy.replace(i, 6, 1, '-');           
        return strCopy;
    }
}
