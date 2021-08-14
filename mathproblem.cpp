#include "pch.h"
#include "stmrLib.h"
#include "functions.h"

namespace stmr
{
    MathProblem::MathProblem(std::string str, unsigned int plug)
    {
        m_array = findOperations(str, plug);
    }

    MathProblem::MathProblem(std::vector<Operation>& arr)
    {
        m_array = arr;
    }

    long double MathProblem::solve()
    {
        const MathProblem& it = *this;
        m_answer = m_array[m_array.size() - 1].answer(it);
        return m_answer;
    }

    Operation MathProblem::getElement(int index) const
    {
        return m_array[index];
    }
}
