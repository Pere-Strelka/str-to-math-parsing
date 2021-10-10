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
#include <map>
#include "enums.h"

namespace stmp
{
    static const std::map<std::string, Operator> g_operators{ { "*", Operator::MULTIPLY },
                                                            { "/", Operator::DIVIDE }, 
                                                            { "+", Operator::ADD }, 
                                                            { "-", Operator::SUBTRACT },
                                                            { "sqrt", Operator::SQRT },
                                                            { "sqr", Operator::SQR },
                                                            { "cbrt", Operator::CBRT },
                                                            { "exp", Operator::EXP },
                                                            { "ln", Operator::LOGE },
                                                            { "lg", Operator::LOG10 },
                                                            { "logtwo", Operator::LOG2 },
                                                            { "pow", Operator::POWER },
                                                            { "negate", Operator::NEGATE } };

    class STMP_API Operation;

    class STMP_API MathProblem
    {
    public:
        MathProblem();
        MathProblem(std::string str);
        ~MathProblem();

        long double answer();
        Operation getElement(int index) const;
        Operation getLastElement() const;
        std::string getString(Format format = Format::None) const;
        long double solve();
        ErrorCode getErrorCode() const;
        std::string getErrorText() const;

        static Operator defineOperator(std::string op);
	    static Operator defineOperator(char op);

        static long double parseAndSolve(std::string str);

        void operator=(const MathProblem& other);

    private:         
        // string will be changed during execution of the function
        static std::vector<Operation> findOperations(std::string &str, unsigned int &opCount); 
        // string will be changed during execution of the function
        static std::vector<Operation> findBraces(std::string &str, unsigned int &opCount); 
        // string will be changed during execution of the function
        static std::vector<Operation> findFunctions(std::string &str, unsigned int &opCount); 
        static std::vector<Operation> addPower(const std::string &pow, unsigned int &opCount);

        bool m_answerReady = false;
        ErrorCode m_errorCode = ErrorCode::None;
        std::string m_str, m_errorText = "";
        std::vector<Operation> m_array;
        long double m_answer;
    };

    class STMP_API Operation
    {    
        friend class STMP_API MathProblem;

    public:
        Operator getOperator() const;

    private:
        Operation();
        Operation(double num1, double num2, Operator op);
        Operation(unsigned int num1, double num2, Operator op);
        Operation(double num1, unsigned int num2, Operator op);
        Operation(unsigned int num1, unsigned int num2, Operator op);
        Operation(double num, Operator func);
        Operation(unsigned int num, Operator func);
        Operation(unsigned int num, int power, Operator func = Operator::POWER);
        Operation(double num, int power, Operator func = Operator::POWER);
        long double answer(const MathProblem &it) const;

        double m_number1, m_number2;
        unsigned int m_index1, m_index2;
        int m_power;
        bool is1num, is2num;
        Operator m_operator;
    };
}
