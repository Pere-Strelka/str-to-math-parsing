#include "pch.h"
#include "stmpLib.h"
#include "functions.h"
#include "exceptions.h"

#include <exception>

namespace stmp
{
    MathProblem::MathProblem() {}
    MathProblem::~MathProblem() {}

    MathProblem::MathProblem(std::string str)
    {
        setExpression(str);
    }

    void MathProblem::setExpression(std::string str)
    {
        m_str = str;

        m_array.clear();
        m_answerReady = false;
        m_errorCode = ErrorCode::None;
        m_errorText = "";

        if (str.empty())
            return;
        unsigned int plug = 0;

        try {
            m_array += findOperations(str, plug);
        } catch (const std::out_of_range& oor) {
            m_errorCode = ErrorCode::IndexOutOfRange;
            m_errorText = oor.what();
            return;
        } catch (const InvalidFunctionException &ife) {
            m_errorCode = ErrorCode::InvalidFunction;
            m_errorText = ife.what();
            return;
        } catch (const InvalidBracesUsageException &ibue) {
            m_errorCode = ErrorCode::InvalidBraces;
            m_errorText = ibue.what();
            return;
        } catch (const std::exception &e) {
            m_errorCode = ErrorCode::UnknownException;
            m_errorText = e.what();
            return;
        } catch (...) {
            m_errorCode = ErrorCode::UnknownException;
            m_errorText = "Unknown error occured.";
            return;
        }
        m_errorCode = ErrorCode::Success;
    }

    long double MathProblem::answer() 
    {
        return m_answerReady ? m_answer : solve();
    }

    long double MathProblem::solve()
    {
        m_answer = m_array.back().answer(*this);
        m_answerReady = true;
        return m_answer;
    }

    void MathProblem::operator=(const MathProblem& other)
    {
        m_array = other.m_array;
        m_str = other.m_str;
        m_answer = other.m_answer;
        m_answerReady = other.m_answerReady;
    }

    Operation MathProblem::getElement(int index) const
    {
        if (index < 0 || index >= m_array.size())
            throw std::out_of_range(std::string("Index " + std::to_string(index) + " is out of range"));
        return m_array[index];
    }

    Operation MathProblem::getLastElement() const
    {
        return m_array.at(m_array.size() - 1);
    }

    std::string MathProblem::getString(Format format) const
    {
        switch (format) {
        case Format::SpacesOnly:
            return makeSpacesOnly(m_str);
        case Format::SpacesAndNoNegate:
            return makeSpacesAndNoNegate(m_str);
        default:
            return m_str;
        }
    }

    ErrorCode MathProblem::getErrorCode() const
    {
        return m_errorCode;
    }

    std::string MathProblem::getErrorText() const
    {
        return m_errorText;
    }

    std::vector<Operation> MathProblem::addPower(const std::string &pow, unsigned int &opCount)
    {
        std::vector<Operation> array;
        auto i = pow.find(',');
        if (i == std::string::npos)
            throw std::exception("Invalid MathProblem::power() usage: no comma is detected");

        int power = std::stoi(pow.substr(i + 1, pow.length() - i - 1));

        // if it is not just a number that we need to raise, then call findOperations to deal with that shit
        for (int j = 0; j < i; j++) {
            if (pow[j] == '-' || pow[j] == '+' || pow[j] == '/' || pow[j] == '*' || std::islower(pow[j])) {        
                std::string str = pow.substr(0, i);
                array += findOperations(str, opCount);
                array += Operation(opCount-1, power, Operator::POWER);
                return array;
            }             
        }
        double num = std::stod(pow.substr(0, i));
        array += Operation(num, power, Operator::POWER);
        return array;
    }

    Operator MathProblem::defineOperator(std::string op)
    {
        if (g_operators.contains(op))
            return g_operators.at(op);
        else
            throw InvalidFunctionException("Invalid function " + op);
    }

    Operator MathProblem::defineOperator(char op)
    {
        auto s = std::to_string(op);
        return defineOperator(s);
    }

    // This function allows to parse and solve expression without creating an object of the class;
    // Warning: it does create the object of the class within itself and also doesn't handle any 
    // exceptions unlike MathProblem(std::string) does
    long double MathProblem::parseAndSolve(std::string str)
    {
        MathProblem pr = MathProblem();
        unsigned int plug = 0;
        pr.m_array += findOperations(str, plug);
        long double answer = pr.m_array.back().answer(pr);
        return answer;
    }

    // further functions are the main parsers; they are divided into three functions to add priority and encapsulate their work
    // every function returns std::vector<Operation> so that they are recursive and can be used with complicated math expressions

    std::vector<Operation> MathProblem::findOperations(std::string &str, unsigned int &opCount)
    {
        std::vector<Operation> array;
        array += findFunctions(str, opCount);
        array += findBraces(str, opCount);

        for (int i = 1; i < str.length(); i++) {
            if (str[i] == '*' || str[i] == '/') {
                Operator op;
                unsigned int opLink1, opLink2;
                double num1, num2;
                bool is1op, is2op;
                unsigned int leftSymbolOfOperation, rightSymbolOfOperation;

                if (str[i] == '*')
                    op = Operator::MULTIPLY;
                else
                    op = Operator::DIVIDE;

                if (str[i - 1] == '}') { // if there is another operation on the left, we'll get its index
                    // cycle is needed to initialize leftSymbolOfOperation variable
                    for (leftSymbolOfOperation = i - 1; str[leftSymbolOfOperation] != '{'; leftSymbolOfOperation--) {}
                    std::string strCopy = str;

                    // removing right excess symbols first, then left and converting to int (it's index)
                    opLink1 = std::stoi(strCopy.erase(i - 1, strCopy.length() - i + 1).erase(0, leftSymbolOfOperation + 1));
                    is1op = true;
                }
                else {
                    // cycle again (there cant be '*' and '/' on the left because all of them already were replaced with {}
                    for (leftSymbolOfOperation = i - 1; 
                        str[leftSymbolOfOperation] != '-' && str[leftSymbolOfOperation] != '+' &&
                        leftSymbolOfOperation > 0; leftSymbolOfOperation--) {}

                    // here we need to make variable one point more if it represents some operator's index ('-', '+')
                    if (leftSymbolOfOperation != 0)
                        leftSymbolOfOperation++;
                    std::string strCopy = str;

                    // this if prevents str from 'out of index'
                    if (leftSymbolOfOperation == 0)
                        num1 = std::stod(strCopy.erase(i, strCopy.length() - i));
                    else
                        // removing right excess symbols first, then left and converting to double
                        num1 = std::stod(strCopy.erase(i, strCopy.length() - i).erase(0, leftSymbolOfOperation));
                    is1op = false;
                }

                if (str[i + 1] == '{') {
                    // cycle is needed to initialize rightSymbolOfOperation variable
                    for (rightSymbolOfOperation = i + 1; 
                        str[rightSymbolOfOperation] != '}' && rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {}
                    std::string strCopy = str;

                    // removing right excess symbols first, then left and converting to int (it's index)
                    opLink2 = std::stoi(strCopy.erase(rightSymbolOfOperation, strCopy.length() - rightSymbolOfOperation).erase(0, i + 2));
                    is2op = true;
                }
                else {
                    // there may be '*' and '/' on the right
                    for (rightSymbolOfOperation = i + 1; 
                        str[rightSymbolOfOperation] != '/' && str[rightSymbolOfOperation] != '*' &&
                        str[rightSymbolOfOperation] != '-' && str[rightSymbolOfOperation] != '+' &&
                        rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {}
                    if (rightSymbolOfOperation != str.length() - 1)
                        rightSymbolOfOperation--;
                    std::string strCopy = str;

                    // this if prevents str from 'out of index'
                    if (rightSymbolOfOperation == str.length() - 1)
                        num2 = std::stod(strCopy.erase(0, i + 1));
                    else
                        // removing right excess symbols first, then left and converting to double
                        num2 = std::stod(strCopy.erase(rightSymbolOfOperation + 1, strCopy.length() - rightSymbolOfOperation - 1).erase(0, i + 1));
                    is2op = false;
                }
                Operation operation;
                if (is1op && is2op)
                    operation = Operation(opLink1, opLink2, op);
                else if (is1op)
                    operation = Operation(opLink1, num2, op);
                else if (is2op)
                    operation = Operation(num1, opLink2, op);
                else
                    operation = Operation(num1, num2, op);
                array.push_back(operation);

                // now we're replacing read operation with {opCount}
                std::string replaceStr = std::string("{" + std::to_string(opCount) + "}");
                str.replace(leftSymbolOfOperation, (rightSymbolOfOperation - leftSymbolOfOperation + 1), replaceStr);
                opCount++;
                i = 0;
            }
        }

        for (int i = 1; i < str.length(); i++) {
            if (str[i] == '+' || str[i] == '-') {
                Operator op;
                unsigned int opLink1, opLink2;
                double num1, num2;
                bool is1op, is2op;
                int leftSymbolOfOperation = 0, rightSymbolOfOperation; // left symbol of operation is always 0th as '+' and '-' have the lowest priority

                if (str[i] == '-')
                    op = Operator::SUBTRACT;
                else
                    op = Operator::ADD;

                if (str[i - 1] == '}') {               // if there is another operation on the left, we'll get its index in the array
                    std::string strCopy = str;

                    // removing right excess symbols first, then left and converting to int (it's index)
                    opLink1 = std::stoi(strCopy.erase(i - 1, strCopy.length() - i + 1).erase(0, 1));
                    is1op = true;
                }
                else {                                  // or there is number on the left
                    std::string strCopy = str;

                    // there cant be another operations on the left
                    std::string temp = strCopy.substr(0, i);
                    num1 = std::stod(temp);
                    is1op = false;
                }

                if (str[i + 1] == '{') {               // if there is another operation on the right...
                    // we need to count only right symbol for this
                    for (rightSymbolOfOperation = i + 1; str[rightSymbolOfOperation] != '}' &&
                        rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {}
                    std::string strCopy = str;

                    // removing right excess symbols first, then left and converting to int (it's index)
                    opLink2 = std::stoi(strCopy.erase(rightSymbolOfOperation, str.length() - rightSymbolOfOperation + 1).erase(0, i + 2));
                    is2op = true;
                }
                else {
                    // we need to count only right symbol for this
                    for (rightSymbolOfOperation = i + 1; str[rightSymbolOfOperation] != '-' &&
                        str[rightSymbolOfOperation] != '+' &&
                        rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {}

                    // this is for variant when cycle stops on '-' or '*' - then we need to step back
                    if (rightSymbolOfOperation != str.length() - 1)
                        rightSymbolOfOperation--;

                    std::string strCopy = str;

                    // this if is for preventing remove() from 'index out of range'
                    if (rightSymbolOfOperation == str.length() - 1)
                        num2 = std::stod(strCopy.erase(0, i + 1));
                    else
                        num2 = std::stod(strCopy.erase(rightSymbolOfOperation + 1, strCopy.length() - rightSymbolOfOperation - 1).erase(0, i + 1));
                    is2op = false;
                }
                Operation operation;
                if (is1op && is2op)
                    operation = Operation(opLink1, opLink2, op);
                else if (is1op)
                    operation = Operation(opLink1, num2, op);
                else if (is2op)
                    operation = Operation(num1, opLink2, op);
                else
                    operation = Operation(num1, num2, op);
                array.push_back(operation);

                // now we're replacing read operation with {opCount}
                std::string replaceStr = std::string("{" + std::to_string(opCount) + "}");
                str.replace(leftSymbolOfOperation, (rightSymbolOfOperation - leftSymbolOfOperation + 1), replaceStr);
                opCount++;
                i = 0;
            }
        }

        if (array.empty()) {
            double num = std::stod(str);
            Operation op = Operation(num, Operator::NONE);
            array.push_back(op);
            std::string replaceStr = std::string("{" + std::to_string(opCount) + "}");
            opCount++;
            str.replace(0, str.length(), replaceStr);
        }
        return array;
    }

    std::vector<Operation> MathProblem::findBraces(std::string &str, unsigned int &opCount)
    {
        std::vector<Operation> arr;
        while (true) {
            std::string strCopy = str;

            // at first we need info about all the braces in the problem
            std::deque<unsigned int> openBracesIndexs;
            std::deque<unsigned int> closeBracesIndexs;
            unsigned int i = 0;
            for (; i < strCopy.length(); i++) {
                if (strCopy[i] == '(')
                    openBracesIndexs.push_back(i);
            }
            if (openBracesIndexs.empty())
                break;
            for (i = 0; i < strCopy.length(); i++) {
                if (strCopy[i] == ')')
                    closeBracesIndexs.push_back(i);
            }

            if (openBracesIndexs.size() != closeBracesIndexs.size())
                throw InvalidBracesUsageException("Some braces are not paired.");

            // now  we need to remove all the braces inside main pair
            for (i = openBracesIndexs[0] + 1; i < closeBracesIndexs[0]; i++) {
                if (strCopy[i] == '(') {
                    closeBracesIndexs.pop_front();
                    openBracesIndexs.erase(iteratorAt(openBracesIndexs, 1));
                }
            }

            // sending the problem inside the pair of the braces in findOperations() and replacing it all with new operation then
            strCopy.erase(closeBracesIndexs[0], strCopy.length() - closeBracesIndexs[0]).erase(0, openBracesIndexs[0] + 1);
            arr += std::vector<Operation>(findOperations(strCopy, opCount));
            str.replace(openBracesIndexs[0], closeBracesIndexs[0] - openBracesIndexs[0] + 1, strCopy);
        }
        return arr;
    }

    std::vector<Operation> MathProblem::findFunctions(std::string &str, unsigned int &opCount)
    {
        std::string strCopy = str;
        std::vector<Operation> arr;
        for (int i = 0; i < strCopy.length(); i++) {
            if (std::islower(strCopy[i])) {
                Operator op;
                // we need info about braces here as well as in findBraces()
                std::deque<unsigned int> openBracesIndexs;
                std::deque<unsigned int> closeBracesIndexs;
                unsigned int rightSymbolOfFunction, rightSymbolOfOperation, leftSymbolOfOperation = i;

                for (unsigned int j = 0; j < strCopy.length(); j++) {
                    if (strCopy[j] == '(')
                        openBracesIndexs.push_back(j);
                }

                for (unsigned int j = 0; j < strCopy.length(); j++) {
                    if (strCopy[j] == ')')
                        closeBracesIndexs.push_back(j);
                }

                if (openBracesIndexs.size() != closeBracesIndexs.size())
                    throw InvalidBracesUsageException("Some braces are not paired.");

                // but here we do also add rightSymbolOfFunction
                for (rightSymbolOfFunction = i;
                    std::islower(strCopy[rightSymbolOfFunction]) && rightSymbolOfFunction < strCopy.length();
                    rightSymbolOfFunction++) {}

                if (rightSymbolOfFunction != strCopy.length() - 1)
                    rightSymbolOfFunction--;

                // it is important to remove not only extra braces IN the main pair but OUTSIDE too, so we have two cycles in this exact order
                while (openBracesIndexs[0] < rightSymbolOfFunction) {
                    openBracesIndexs.pop_front();
                    closeBracesIndexs.pop_back();
                }

                for (i = openBracesIndexs[0] + 1; i < closeBracesIndexs[0]; i++) {
                    if (strCopy[i] == '(') {
                        closeBracesIndexs.pop_front();
                        openBracesIndexs.erase(iteratorAt(openBracesIndexs, 1));
                    }
                }

                rightSymbolOfOperation = closeBracesIndexs[0];

                // now here function's text and then its definition in Operator
                std::string *func = new std::string(strCopy);
                func->erase(rightSymbolOfFunction + 1, strCopy.length() - rightSymbolOfFunction).erase(0, leftSymbolOfOperation);
                op = defineOperator(*func);
                delete func;

                strCopy.erase(rightSymbolOfOperation, strCopy.length() - rightSymbolOfOperation).erase(0, rightSymbolOfFunction + 2);       
                if(op == Operator::POWER) {
                    arr += addPower(strCopy, opCount);
                } else {
                    // sending the problem inside the function's braces into findOperations() 
                    arr += findOperations(strCopy, opCount);
                    arr.push_back(Operation(opCount - 1, op));
                }

                // now we're replacing read function with {opCount}
                std::string replaceStr = std::string("{" + std::to_string(opCount) + "}");
                str.replace(leftSymbolOfOperation, rightSymbolOfOperation - leftSymbolOfOperation + 1, replaceStr);
                opCount++;
                i = 0;
                strCopy = str;
            }
        }
        return arr;
    }
}
