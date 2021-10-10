#include "pch.h"
#include "functions.h"
#include "stmpLib.h"

namespace stmp
{
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    std::vector<Operation, std::allocator<Operation>> second)
    {
        if (first.empty()) {
            first = second;
        } else {
            for (auto it = second.begin(); it != second.end(); it++) 
                first.push_back(*it);
        }           
    }

    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    Operation second)
    { first.push_back(second); }

    std::deque<unsigned int>::iterator iteratorAt(std::deque<unsigned int>& arr, int index)
    {
        std::deque<unsigned int>::iterator it = arr.begin();
        std::advance(it, index);
        return it;
    }

    std::string makeSpacesOnly(const std::string &str)
    {
        std::string strCopy = str;
        for (int i = 1; i < strCopy.size(); i++)
        {
            if (strCopy[i] == '+' || strCopy[i] == '-' || strCopy[i] == '/' || strCopy[i] == '*')
            {
                strCopy.insert(strCopy.begin()+i+1, ' ');
                strCopy.insert(strCopy.begin()+i, ' ');
                i++;
            }            
        }
        return strCopy;
    }

    std::string makeSpacesAndNoNegate(const std::string &str)
    {
        std::string strCopy = makeSpacesOnly(str);
        for (int i = 1; i < strCopy.size(); i++)
            if (strCopy[i] == 'n')
                if (strCopy.substr(i, 6) == "negate")
                    strCopy.replace(i, 6, 1, '-');           
        return strCopy;
    }
}
