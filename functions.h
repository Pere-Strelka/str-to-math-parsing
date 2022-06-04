#pragma once

#include "stmpLib.h"

namespace stmp
{  
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    std::vector<Operation, std::allocator<Operation>> second);
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, Operation second);

    std::deque<unsigned int>::iterator iteratorAt(std::deque<unsigned int>& arr, int index);

    std::string makeSpaces(const std::string &str);
    std::string makeNoNegate(const std::string &str);
    std::string makeSymbols(const std::string& str, const std::map<std::string, std::string>& map);
    std::string makeFormatting(const std::string &str, 
                                   bool spaces = true, 
                                   bool noNegate = true, SymbolFormat smbFormat = SymbolFormat::None);
}

