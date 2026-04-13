## Datamaker

    This tool I made spits out a csv containing the equations and answers used to train and test the AI. There are three values to change to alter the output to what you want: the number of equations, the difficulty, and the number of new operators. After changing these values, recompile datamaker.cpp and complexityDriver.cpp and run the executable to output the csv in the datamaker directory. These values will be at the top of main() in datamaker.cpp

# Easy:

    This difficulty will only create equations with two numbers and one operand acting on them. The numbers are only allowed to range from -9 to 9. Easy is also not allowed to use the modulo operator.
    *Total numbers = 2
    *Total operands = 1
    *Number range = (-10, 10)

# Medium:

    This difficulty will create equations with three numbers and two operands acting on them. The numbers are allowed to be in the range from -49 to 49. Medium is allowed to use the modulo operator
    *Total numbers = 3
    *Total operands = 2
    *Number range = (-50, 50)

# Hard:

    This difficulty will make equations with five numbers and four operands. Numbers are allowed to be in the range from -99 to 99. Hard is allowed to use the modulo operator
    *Total numbers = 5
    *Total operands = 4
    *Number range = (-100, 100)

## New Operands:

    a & b = a / (2 * b) (Happens last in order of operations, even after addition and subtraction)

    a $ b = b * (ceiling(b / a)) (Happens at the same priority as addition and subtraction in order of operations)

    a # b = a + ((3 + a) * b) (Happens at the same priority as multiplication and division in order of operations)

    a @ b = -a - (b * 5) (Happends at the same priority as exponents in order of operations)

    These operators will be added in that order, so if you allow 2 new operators, & and $ are added.