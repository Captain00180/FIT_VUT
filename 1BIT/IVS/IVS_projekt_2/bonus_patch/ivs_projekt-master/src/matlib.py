## @file matlib.py
# @brief This is a mathematical library for handling operations in our Calculator app.
# @details Contains all mathematical functions used for evaluating expressions in the calculator app.
# @author Filip Januška



## 
# @brief Returns the sum of two numbers.
# @param a First operand.
# @param b Second operand.
# @return Result of mathematical addition (a + b).
def sum(a, b):
    return a + b


## 
# @brief Returns the difference of two numbers.
# @param a First operand.
# @param b Second operand.
# @return  Result of mathematical subtraction (a - b).
def diff(a, b):
     return a - b

##
# @brief Returns the product of two numbers.
# @param a First operand.
# @param b Second operand.
# @return  Result of mathematical multiplication (a * b).
def mul(a, b):
     return a * b

##
# @brief Returns the result of division of two numbers.
# @param a First operand.
# @param b Second operand - Can't be 0!
# @return  Result of mathematical division. In case of dividing by zero returns None type (a / b).
def div(a, b):
    if b != 0:
        return a / b
    else:
        return None

##
# @brief Returns the factorial of 'a'.
# @param a Operand - Must be positive!
# @return  Result of mathematical factorial. In case of invalid operand returns None type (a!).
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


##
# @brief Returns the value of 'a' to the power of 'b'
# @param a First operand.
# @param b Second operand - Must be a positive number!
# @return  Value of 'a' to the power of 'b'. In case of invalid operands returns None type (a ^ b).
def exp(a, b):
    if (b % 1) != 0 or b < 0:
        return None
    return a ** b

##
# @brief Returns the value of b-th root of a.
# @param a First operand.
# @param b Second operand - Can't be 0!
# @return  Result of mathematical root. In case of invalid operands returns None type.
def nroot(a, b):
    if a < 0 or b == 0 or (a == 0 and b < 0):
        return None
    return a ** (1/b)


##
# @brief Returns the absolute value of the operand.
# @param a Operand.
# @return  Absolute value of 'a' (|a|).
def abs(a):
    if a < 0:
        return -a
    return a


##
# @brief Returns remainder after division of a/b.
# @param a First operand.
# @param b Second operand - Can't be 0!
# @return  Return remaining value after divison. In case of invalid operands returns None type (a % b).
def mod(a,b):
    if b == 0:
        return None
    else:
        return a % b
