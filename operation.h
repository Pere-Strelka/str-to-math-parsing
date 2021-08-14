#pragma once
#include <vector>
#include <string>
#include <locale>
#include <deque>

#include "stmrLib.h"
#include "operators.h"

class STMR_API MathProblem;

class STMR_API Operation
{
public:
    Operation() {}
    Operation(double num1, double num2, Operator op);
    Operation(unsigned int num1, double num2, Operator op);
    Operation(double num1, unsigned int num2, Operator op);
    Operation(unsigned int num1, unsigned int num2, Operator op);
    Operation(double num, Operator func);
    Operation(unsigned int num, Operator func);
    long double answer(const MathProblem &it) const;

private:
    double m_number1, m_number2;
    unsigned int m_index1, m_index2;
    bool is1num, is2num;
    Operator m_operator;
    double m_answer;
};
