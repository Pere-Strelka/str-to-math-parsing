#pragma once

#include "stmrLib.h"
#include "operation.h"
#include "functions.h"

class STMR_API MathProblem
{
public:
    MathProblem() {}
    MathProblem(std::string str, unsigned int plug = 0);
    MathProblem(std::vector<Operation>& arr);
    long double solve();
    long double answer() { return m_answer; }
    Operation getElement(int index) const { return m_array[index]; }
private:
    std::vector<Operation> m_array;
    long double m_answer;
};