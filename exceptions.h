#pragma once

#include <exception>
#include <string>

namespace stmp {

    class InvalidFunctionException : std::exception
    {
    public:
        InvalidFunctionException(std::string str);

        const char* what() const noexcept;

    private:
        const char* m_what;
    };

    class InvalidBracesUsageException : std::exception
    {
    public:
        InvalidBracesUsageException(std::string str);

        const char* what() const noexcept;

    private:
        const char* m_what;
    };
}