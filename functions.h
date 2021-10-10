#pragma once

#include "stmpLib.h"

namespace stmp
{
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    std::vector<Operation, std::allocator<Operation>> second);
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, Operation second);

    std::deque<unsigned int>::iterator iteratorAt(std::deque<unsigned int>& arr, int index);

    std::string makeSpacesOnly(const std::string &str);
    std::string makeSpacesAndNoNegate(const std::string &str);
}

