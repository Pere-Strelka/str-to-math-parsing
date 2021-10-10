#include "pch.h"
#include "invalidfunctionexception.h"

namespace stmp {

    InvalidFunctionException::InvalidFunctionException(std::string str) : std::exception() 
    {
        m_what = str.c_str();
    }

    const char* InvalidFunctionException::what() const noexcept
    {
        return m_what;
    }
}