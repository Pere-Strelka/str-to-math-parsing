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

    std::string makeSpaces(const std::string &str)
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

    std::string makeNoNegate(const std::string &str)
    {
        std::string strCopy = str;
        for (int i = 1; i < strCopy.size(); i++)
            if (strCopy[i] == 'n')
                if (strCopy.substr(i, 6) == "negate")
                    strCopy.replace(i, 6, 1, '-');           
        return strCopy;
    }

    std::string makeSymbols(const std::string &str, const std::map<std::string, std::string> &map)
    {
        std::string strCopy = str;

        for (auto symbols_it = g_symbolsHTML.begin(); symbols_it != g_symbolsHTML.end(); ++symbols_it)
        {
            while (1)
            {
                auto temp = strCopy.find(symbols_it->first);
                if (temp == std::string::npos)
                    break;

                strCopy.replace(temp, symbols_it->first.length(), symbols_it->second);
            }
        }
        return strCopy;
    }

    std::string makeFormatting(const std::string &str, bool spaces, 
                               bool noNegate, SymbolFormat smbFormat)
    {
        std::string strCopy = str;
        if (spaces)
            strCopy = makeSpaces(strCopy);
        if (noNegate)
            strCopy = makeNoNegate(strCopy);
        switch (smbFormat)
        {
            case SymbolFormat::HTML:
                strCopy = makeSymbols(strCopy, g_symbolsHTML);
                break;
            // case SymbolFormat::Unicode:
            //     strCopy = makeSymbols(strCopy, )
            default:
                return strCopy;
        }
              
        return strCopy;
    }
}
