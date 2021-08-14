#pragma once

#ifdef STMR_EXPORTS
#define STMR_API __declspec(dllexport)
#else
#define STMR_API __declspec(dllimport)
#endif

#include <vector>
#include <string>
#include <deque>
#include <locale>
#include "operators.h"

namespace stmr
{
    class STMR_API Operation;

    class STMR_API MathProblem
    {
    public:
        MathProblem() {}
        MathProblem(std::string str, unsigned int plug = 0);
        MathProblem(std::vector<Operation>& arr);
        long double solve();
        long double answer() { return m_answer; }
        Operation getElement(int index) const;
    private:
        std::vector<Operation> m_array;
        long double m_answer;
    };

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
        long double answer(const MathProblem& it) const;
    private:
        double m_number1, m_number2;
        unsigned int m_index1, m_index2;
        bool is1num, is2num;
        Operator m_operator;
        double m_answer;
    };

}
