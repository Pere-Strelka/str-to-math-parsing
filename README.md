# str-to-math-recognition (stmr)

This is a dll project. It contains class MathProblem which can take a string and convert it to the math using class Operation and enum class Operator. Math expression requirements:

- no spaces
- only digits, signs of mathematical actions (+, -, /, *) and some functions (e.g. 'negate' for negative numbers)
Example: "32+negate(321)/2+(33-5*(45-9))"

MathProblem has a constructor taking std::string as an argument. After the initialization, method solve() will solve the expression and then you can just get the complete answer by answer() to avoid solving again. Both methods return long double.

Version 1.0 is supposed to have following features:

- support of most of the important standard math.h lib functions
- stability
- module for converting pure math string (like in the example above) into pretty mathematical expression (like you can make in MS Word using formulas) (? - maybe this feature will be in a separate branch or smth)
