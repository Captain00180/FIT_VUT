## @package MatLib
# @brief This is a mathematical library for handling operations in our Calculator app.
# @author Filip Januška
# @file matlib.py


## @fn sum(a, b)
# @brief Returns the sum of two numbers.
# @param[in] a First inputed number.
# @param[in] b Second inputed number.
# @param[out] out Result of mathematical addition.
def sum(a, b):
    return a + b


## @fn diff(a, b)
# @brief Returns the difference of two numbers.
# @param[in] a First inputed number.
# @param[in] b Second inputed number.
# @param[out] out Result of mathematical subtraction.
def diff(a, b):
     return a - b


## @fn mul(a, b)
# @brief Returns the product of two numbers.
# @param[in] a First inputed number.
# @param[in] b Second inputed number.
# @param[out] out Result of mathematical multiplication.
def mul(a, b):
     return a * b


## @fn div(a, b)
# @brief Returns the result of division of two numbers.
# @param[in] a First inputed number.
# @param[in] b Second inputed number.
# @param[out] out Result of mathematical division. In case of dividing by zero returns None type.
def div(a, b):
    if b != 0:
        return a / b
    else:
        return None

## @fn fact(a)
# @brief Returns the value of factorial(a).
# @param[in] a First inputed number.
# @param[out] out Result of mathematical factorial. In case of invalid number returns None type.
def fact(a):
    if a < 0:
        return None
    if a == 0:
        return 1
    counter = a - 1
    while(counter > 1):
        a *= counter
        counter -= 1
    return a


## @fn exp(a, b)
# @brief Returns the value of 'a' to the power of 'b'
# @param[in] a First inputed number.
# @param[in] b Second inputed number.
# @param[out] out Result of mathematical squaring. In case of invalid numbers returns None type.
def exp(a, b):
    if (b % 1) != 0 or b < 0:
        return None
    return a ** b

## @fn nroot(a, b)
# @brief Returns the value of b-th root of a.
# @param[in] a First inputed number.
# @param[in] b Second inputed number.
# @param[out] out Result of mathematical root. In case of invalid numbers returns None type.
def nroot(a, b):
    if a < 0 or b == 0 or (a == 0 and b < 0):
        return None
    return a ** (1/b)


## @fn abs(a)
# @brief Returns the absolute value.
# @param[in] a First inputed number.
# @param[out] out Result of absolute value.
def abs(a):
    if a < 0:
        return -a
    return a


## @fn mod(a, b)
# @brief Returns remainder after division of a/b.
# @param[in] a First inputed number.
# @param[in] b Second inputed number.
# @param[out] out Return remaining value after divison. In case of invalid numbers returns None type.
def mod(a,b):
    if b == 0:
        return None
    else:
        return a % b
