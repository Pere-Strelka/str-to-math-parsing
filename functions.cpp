#include "pch.h"
#include "functions.h"
#include "stmpLib.h"

namespace stmp
{
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    std::vector<Operation, std::allocator<Operation>> second)
    {
        auto it = second.begin();
        while (it != second.end()) {
            first.push_back(*it);
            it++;
        }
    }

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
        else if (op == "log")
            return Operator::LOGARITHM;
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
}
