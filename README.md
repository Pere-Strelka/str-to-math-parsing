# str-to-math-recognition
This is a dll project. It contains class MathProblem which can take a string and convert it to the math using class Operation and enum class Operator.
Math expression requirements:
- no spaces
- only digits, signs of mathematical actions (+, -, /, *) and some functions ('negate' for negative numbers) 

The list will update as the library is updated.
Example: "32+negate(321)/2+(33-5*(45-9))"

MathProblem has constructor taking std::string as an argument. 
After initialization method solve() will solve the problem and then to avoid solving again you can just get complete answer by answer().
Both methods return long double.
