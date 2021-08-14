#include "pch.h"
#include "functions.h"
#include "stmrLib.h"

namespace stmr
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

    long double answerOfOperation(unsigned int index, const MathProblem& it)
    {
        return it.getElement(index).answer(it);
    }

    long double Operation::answer(const MathProblem& it) const
    {
        long double(&ans)(unsigned int, const MathProblem&) = answerOfOperation;
        switch (m_operator) {
        case Operator::MULTIPLY:
            if (is1num && is2num)
                return m_number1 * m_number2;
            else if (is1num)
                return m_number1 * ans(m_index2, it);
            else if (is2num)
                return ans(m_index1, it) * m_number2;
            else
                return ans(m_index1, it) * ans(m_index2, it);
        case Operator::DIVIDE:
            if (is1num && is2num)
                return m_number1 / m_number2;
            else if (is1num)
                return m_number1 / ans(m_index2, it);
            else if (is2num)
                return ans(m_index1, it) / m_number2;
            else
                return ans(m_index1, it) / ans(m_index2, it);
        case Operator::ADD:
            if (is1num && is2num)
                return m_number1 + m_number2;
            else if (is1num)
                return m_number1 + ans(m_index2, it);
            else if (is2num)
                return ans(m_index1, it) + m_number2;
            else
                return ans(m_index1, it) + ans(m_index2, it);
        case Operator::SUBTRACT:
            if (is1num && is2num)
                return m_number1 - m_number2;
            else if (is1num)
                return m_number1 - ans(m_index2, it);
            else if (is2num)
                return ans(m_index1, it) - m_number2;
            else
                return ans(m_index1, it) - ans(m_index2, it);
        case Operator::NEGATE:
            if (is1num)
                return -m_number1;
            else
                return -(ans(m_index1, it));
        case Operator::NONE:
            if (is1num)
                return m_number1;
            else
                return ans(m_index1, it);
        }
    }
}

