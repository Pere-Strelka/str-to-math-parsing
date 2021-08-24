#include "pch.h"
#include "stmpLib.h"
#include "functions.h"

namespace stmp
{
    MathProblem::MathProblem(std::string str) : m_str{ str}
    {
        if (str.empty())
            return;
        unsigned int plug = 0;
        m_array += findOperations(str, plug);
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
            throw std::out_of_range(std::string("Index " + std::to_string(index) + " is out of range"));
        return m_array[index];
    }

    template <class T>
    auto MathProblem::iteratorAt(std::deque<T>& arr, unsigned int index)
    {
        auto it = arr.begin();
        std::advance(it, index);
        return it;
    }

    std::vector<Operation> MathProblem::findOperations(std::string& str, unsigned int& opCount)
    {
        std::vector<Operation> array;
        array += std::vector<Operation>(findFunctions(str, opCount));
        array += std::vector<Operation>(findBraces(str, opCount));

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
                        leftSymbolOfOperation > 0; leftSymbolOfOperation--) {
                    }

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
                        str[rightSymbolOfOperation] != '}' && rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {
                    }
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
                        rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {
                    }
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
                int leftSymbolOfOperation = 0, rightSymbolOfOperation; // left symbol of operation is always 0th

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
                        rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {
                    }
                    std::string strCopy = str;

                    // removing right excess symbols first, then left and converting to int (it's index)
                    opLink2 = std::stoi(strCopy.erase(rightSymbolOfOperation, str.length() - rightSymbolOfOperation + 1).erase(0, i + 2));
                    is2op = true;
                }
                else {
                    // we need to count only right symbol for this
                    for (rightSymbolOfOperation = i + 1; str[rightSymbolOfOperation] != '-' &&
                        str[rightSymbolOfOperation] != '+' &&
                        rightSymbolOfOperation < str.length(); rightSymbolOfOperation++) {
                    }

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

    std::vector<Operation> MathProblem::findBraces(std::string& str, unsigned int& opCount)
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

    std::vector<Operation> MathProblem::findFunctions(std::string& str, unsigned int& opCount)
    {
        std::string strCopy = str;
        std::vector<Operation> arr;
        for (int i = 0; i < strCopy.length(); i++) {
            if (std::islower(strCopy[i])) {
                // we need info about braces here as well as in findBraces()
                std::string func;
                Operator op;
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

                // but here we do also add rightSymbolOfFunction
                for (rightSymbolOfFunction = i;
                    std::islower(strCopy[rightSymbolOfFunction]) && rightSymbolOfFunction < strCopy.length();
                    rightSymbolOfFunction++) {
                }

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
                func = strCopy;
                func.erase(rightSymbolOfFunction + 1, strCopy.length() - rightSymbolOfFunction).erase(0, leftSymbolOfOperation);
                op = defineOperator(func);

                // sending the problem inside the function's braces into findOperations()
                strCopy.erase(rightSymbolOfOperation, strCopy.length() - rightSymbolOfOperation).erase(0, rightSymbolOfFunction + 2);
                arr += std::vector<Operation>(findOperations(strCopy, opCount));
                arr.push_back(Operation(opCount - 1, op));

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
