#pragma once
#include "stmpLib.h"

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
        None,
        SpacesOnly,
        SpacesAndNoNegate
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

