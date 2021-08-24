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
        LOGARITHM,
        NEGATE,
        NONE
    };

    enum class STMP_API Format {
        None,
        SpacesOnly,
        SpacesAndNoNegate
    };
}

