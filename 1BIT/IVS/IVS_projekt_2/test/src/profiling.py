# @cond EXC
#!/usr/bin/env python3
# @endcond EXC
## @file profiling.py
# @brief This is a program to make profiling app.
# @details Used to test the math library and provide grounds for future improvement.
# @author Martin Gerža



import matlib
import random


##
# @brief Calculates the sample standard deviation of NUMBERS.
# @param numbers Array of numbers received as input.
# @return Value of Sample Standard Deviation
def SampleStandardDeviation(numbers):
    ap = ArithmeticallAverage(numbers)
    for i in range(len(numbers)):
        numbers[i] = matlib.exp(numbers[i], 2)
    summ = Summation(numbers)
    apExp = matlib.exp(ap, 2)
    diff = matlib.diff(summ, matlib.mul(len(numbers), apExp))
    div = matlib.div(1, matlib.diff(len(numbers), 1))
    result = matlib.nroot(matlib.mul(div, diff), 2)
    return result


##
# @brief Makes summation of NUMBERS.
# @param numbers Array of numbers.
# @return Sum of all numbers in the 'numbers' array.
def Summation(numbers):
    result = 0
    for num in numbers:
        result = matlib.sum(result, num)
    return result


##
# @brief Makes arithmetic average of given NUMBERS.
# @param numbers Array of numbers.
# @return Arithmetical average of numbers in the 'numbers' array.
def ArithmeticallAverage(numbers):
    summ = Summation(numbers)
    return matlib.div(summ, len(numbers))


numbers=[]
## Variable holding the raw string input
string = input().split()
for i in range(len(string)):
   numbers.append(int(string[i]))

# for i in range(1000):
#    numbers.append(random.randint(-10000, 10000))

print(SampleStandardDeviation(numbers))
