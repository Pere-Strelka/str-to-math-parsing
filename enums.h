#pragma once

namespace stmp {
    enum class Operator {
        MULTIPLY,
        DIVIDE,
        ADD,
        SUBTRACT,
        SQRT,
        SQR,
        CBRT,
        EXP,
        LOGE,
        LOG10,
        LOG2,
        POWER,
        NEGATE,
        NONE
        
    };

    enum class STMP_API Format {
        None = 1,
        Spaces = 2,
        NoNegate = 4,
        HTMLSymbols = 8,     
    };

    inline Format operator|(Format a, Format b)
    {
        return static_cast<Format>(static_cast<int>(a) | static_cast<int>(b));
    }

    enum class STMP_API SymbolFormat {
        None = 0,
        HTML = 1,
        Unicode = 2
    };

    enum class STMP_API ErrorCode {
        None,
        Success,
        IndexOutOfRange,
        InvalidFunction,
        InvalidBraces,
        UnknownException,
    };
}

