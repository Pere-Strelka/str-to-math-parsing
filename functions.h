#pragma once

#include "stmpLib.h"

namespace stmp
{
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    std::vector<Operation, std::allocator<Operation>> second);
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, Operation second);

    
    template <class T>
    auto iteratorAt(std::deque<T> &arr, unsigned int index)
    {
        auto it = arr.begin();
        std::advance(it, index);
        return it;
    }

	Operator defineOperator(std::string& op);
	Operator defineOperator(char op);

    std::string makeSpacesOnly(const std::string &str);
    std::string makeSpacesAndNoNegate(const std::string &str);
}

