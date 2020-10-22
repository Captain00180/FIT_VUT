#!/usr/bin/env python3
## @package Profiling
# @file profiling.py
# @author Martin Gerža
# @brief This is a program to make profiling app.


import matlib
import random


## @fn SampleStandardDeviation(numbers)
# @brief Returns the result of mathematical sample standard deviation of NUMBERS.
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


## @fn Summation(numbers)
# @brief Makes summation of NUMBERS.
def Summation(numbers):
    result = 0
    for num in numbers:
        result = matlib.sum(result, num)
    return result


## @fn ArithmeticallAverage(numbers)
# @brief Makes arithmetic average of given NUMBERS.
def ArithmeticallAverage(numbers):
    summ = Summation(numbers)
    return matlib.div(summ, len(numbers))

numbers=[]

string = input().split()
for i in range(len(string)):
   numbers.append(int(string[i]))

#for i in range(1000):
#    numbers.append(random.randint(-10000, 10000))

print(SampleStandardDeviation(numbers))
