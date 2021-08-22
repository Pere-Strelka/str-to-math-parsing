#pragma once

#ifdef STMP_EXPORTS
#define STMP_API __declspec(dllexport)
#else
#define STMP_API __declspec(dllimport)
#endif

#include <vector>
#include <string>
#include <deque>
#include <locale>
#include "operators.h"

namespace stmp
{
    class STMP_API Operation;

    class STMP_API MathProblem
    {
    public:
        MathProblem() {}
        MathProblem(std::string str, unsigned int plug = 0);
        MathProblem(std::vector<Operation>& arr);
        long double answer() { return m_answerReady ? m_answer : this->solve(); }
        Operation getElement(int index) const;

    private:
        long double solve();
        bool m_answerReady = false;
        std::vector<Operation> m_array;
        long double m_answer;
    };

    class STMP_API Operation
    {
    public:
        Operation() {}
        Operation(double num1, double num2, Operator op);
        Operation(unsigned int num1, double num2, Operator op);
        Operation(double num1, unsigned int num2, Operator op);
        Operation(unsigned int num1, unsigned int num2, Operator op);
        Operation(double num, Operator func);
        Operation(unsigned int num, Operator func);

        friend class STMP_API MathProblem;

    private:
        long double answer(const MathProblem& it) const;
        double m_number1, m_number2;
        unsigned int m_index1, m_index2;
        bool is1num, is2num;
        Operator m_operator;
    };

}
