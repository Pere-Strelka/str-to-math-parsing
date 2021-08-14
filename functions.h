#pragma once

#include "stmrLib.h"

namespace stmr
{
	std::vector<Operation> findFunctions(std::string& str, unsigned int& opCount);
	std::vector<Operation> findBraces(std::string& str, unsigned int& opCount);
	std::vector<Operation> findOperations(std::string& str, unsigned int& opCount);
}

