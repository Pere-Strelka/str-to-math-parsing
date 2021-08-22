#include "pch.h"
#include "stmpLib.h"
#include "functions.h"

namespace stmp
{
    MathProblem::MathProblem(std::string str, unsigned int plug)
    {
        if (str.empty())
            return;
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
        m_answerReady = true;
        return m_answer;
    }

    Operation MathProblem::getElement(int index) const
    {
        if (index < 0 || index >= m_array.size())
            throw std::out_of_range(std::string("Index out of range"));
        return m_array[index];
    }
}
