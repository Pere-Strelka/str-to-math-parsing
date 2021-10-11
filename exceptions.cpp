#include "pch.h"
#include "exceptions.h"

namespace stmp {

    InvalidFunctionException::InvalidFunctionException(std::string str) : std::exception() 
    {
        m_what = str.c_str();
    }

    const char* InvalidFunctionException::what() const noexcept
    {
        return m_what;
    }

    InvalidBracesUsageException::InvalidBracesUsageException(std::string str) : std::exception() 
    {
        m_what = str.c_str();
    }

    const char* InvalidBracesUsageException::what() const noexcept
    {
        return m_what;
    }
}