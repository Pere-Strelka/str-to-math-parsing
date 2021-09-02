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
#include <iterator>
#include "enums.h"

namespace stmp
{
    class STMP_API Operation;

    class STMP_API MathProblem
    {
    public:
        MathProblem() {}
        MathProblem(std::string str);
        long double answer() { return m_answerReady ? m_answer : solve(); }
        Operation getElement(int index) const;
        std::string getString(Format format = Format::None) const;
        long double solve();

    private:         
        template <class T>
        auto iteratorAt(std::deque<T>& arr, unsigned int index);
        std::vector<Operation> findOperations(std::string& str, unsigned int& opCount); // string will be changed during execution of the function
        std::vector<Operation> findBraces(std::string& str, unsigned int& opCount); // string will be changed during execution of the function
        std::vector<Operation> findFunctions(std::string& str, unsigned int& opCount); // string will be changed during execution of the function
        Operation power(const std::string &pow, unsigned int &opCount, std::vector<Operation> &array);

        bool m_answerReady = false;
        std::string m_str;
        std::vector<Operation> m_array;
        long double m_answer;
    };

    class STMP_API Operation
    {    
        friend class STMP_API MathProblem;

    private:
        Operation() {}
        Operation(double num1, double num2, Operator op);
        Operation(unsigned int num1, double num2, Operator op);
        Operation(double num1, unsigned int num2, Operator op);
        Operation(unsigned int num1, unsigned int num2, Operator op);
        Operation(double num, Operator func);
        Operation(unsigned int num, Operator func);
        Operation(unsigned int num, int power, Operator func = Operator::POWER);
        Operation(double num, int power, Operator func = Operator::POWER);
        long double answer(const MathProblem& it) const;
        double m_number1, m_number2;
        unsigned int m_index1, m_index2;
        int m_power;
        bool is1num, is2num;
        Operator m_operator;
    };
}
