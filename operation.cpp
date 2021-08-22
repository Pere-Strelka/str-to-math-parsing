#include "pch.h"
#include "functions.h"
#include "stmpLib.h"

namespace stmp
{
    Operation::Operation(double num1, double num2, Operator op)
    {
        m_number1 = num1;
        m_number2 = num2;
        m_operator = op;
        is1num = true, is2num = true;
    }

    Operation::Operation(unsigned int num1, double num2, Operator op)
    {
        m_index1 = num1;
        m_number2 = num2;
        m_operator = op;
        is1num = false, is2num = true;
    }

    Operation::Operation(double num1, unsigned int num2, Operator op)
    {
        m_number1 = num1;
        m_index2 = num2;
        m_operator = op;
        is1num = true, is2num = false;
    }

    Operation::Operation(unsigned int num1, unsigned int num2, Operator op)
    {
        m_index1 = num1;
        m_index2 = num2;
        m_operator = op;
        is1num = false, is2num = false;
    }

    Operation::Operation(double num, Operator func)
    {
        m_number1 = num;
        m_operator = func;
        is1num = true;
    }

    Operation::Operation(unsigned int num, Operator func)
    {
        m_index1 = num;
        m_operator = func;
        is1num = false;
    }

    long double Operation::answer(const MathProblem& it) const
    {
        auto ans = [&it] (unsigned int index) { 
            return it.getElement(index).answer(it);
        };
        switch (m_operator) {
        case Operator::MULTIPLY:
            if (is1num && is2num)
                return m_number1 * m_number2;
            else if (is1num)
                return m_number1 * ans(m_index2);
            else if (is2num)
                return ans(m_index1) * m_number2;
            else
                return ans(m_index1) * ans(m_index2);
        case Operator::DIVIDE:
            if (is1num && is2num)
                return m_number1 / m_number2;
            else if (is1num)
                return m_number1 / ans(m_index2);
            else if (is2num)
                return ans(m_index1) / m_number2;
            else
                return ans(m_index1) / ans(m_index2);
        case Operator::ADD:
            if (is1num && is2num)
                return m_number1 + m_number2;
            else if (is1num)
                return m_number1 + ans(m_index2);
            else if (is2num)
                return ans(m_index1) + m_number2;
            else
                return ans(m_index1) + ans(m_index2);
        case Operator::SUBTRACT:
            if (is1num && is2num)
                return m_number1 - m_number2;
            else if (is1num)
                return m_number1 - ans(m_index2);
            else if (is2num)
                return ans(m_index1) - m_number2;
            else
                return ans(m_index1) - ans(m_index2);
        case Operator::SQRT:
            if (is1num)
                return sqrt(m_number1);
            else
                return sqrt(ans(m_index1));
        case Operator::SQR:
            if (is1num)
                return pow(m_number1, 2);
            else
                return pow(ans(m_index1), 2);
        case Operator::CBRT:
            if (is1num)
                return cbrt(m_number1);
            else
                return cbrt(ans(m_index1));
        case Operator::EXP:
            if (is1num)
                return exp(m_number1);
            else
                return exp(ans(m_index1));
        case Operator::LOGARITHM:
            if (is1num)
                return log(m_number1);
            else
                return log(ans(m_index1));
        case Operator::NEGATE:
            if (is1num)
                return -m_number1;
            else
                return -(ans(m_index1));
        case Operator::NONE:
            if (is1num)
                return m_number1;
            else
                return ans(m_index1);
        }
    }
}

