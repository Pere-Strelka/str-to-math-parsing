#pragma once

#include "stmpLib.h"

namespace stmp
{
    void operator+=(std::vector<Operation, std::allocator<Operation>> &first, 
                    std::vector<Operation, std::allocator<Operation>> second);

	Operator defineOperator(std::string& op);
	Operator defineOperator(char op);

    std::string makeSpacesOnly(const std::string &str);
    std::string makeSpacesAndNoNegate(const std::string &str);
}

