## @file projekt_ivs_test.py
# @brief Test for mathematical library called matlib.py.
# @details All tests are done with a 'brute-force'-like method. Numbers from a large interval are tested in every combination,
# including edge cases and special operand combinations for individual operators. Every test results in over 100 000 combinations tested.
# Tests utilize the 'pytest' library, based on simple assert cases.
# @author Martin Gerža

import matlib
from math import *
import pytest

## @brief Tests summation of two numbers.
# Tests every combination from an interval of (-100, 100).
def test_summation():
    for i in range(-100, 100):
        for j in range(-100, 100):
            assert matlib.sum(i, j) == i + j


## @brief Tests subtraction of two numbers.
# Tests every combination from an interval of (-100, 100)
def test_subtraction():
    for i in range(-100, 100):
        for j in range(-100, 100):
            assert matlib.diff(i, j) == i - j


## @brief Tests multiplication of two numbers.
# Tests every combination from an interval of (-100, 100)
def test_multiplication():
    for i in range(-100, 100):
        for j in range(-100, 100):
            assert matlib.mul(i, j) == i * j


## @brief Tests division of two numbers.
# Tests every combination from an interval of (-100, 100), including special cases, where the second operand is 0.
def test_division():
    for i in range(-100, 100):
        for j in range(-100, 100):
            if j != 0:
                assert matlib.div(i, j) == i / j
            else:
                assert matlib.div(i, j) == None


## @brief Tests factorial of given number.
# Tests an interval of (-10, 100), expecting error with negative numbers.
def test_factorial():
    for i in range(-10, 100):
        if i >= 0:
            assert matlib.fact(i) == factorial(i)
        else:
            assert matlib.fact(i) == None


## @brief Tests power of two numbers.
# Tests  an interval of (-100, 100) to the power of interval (0, 100).
def test_power():
    for i in range(-100, 100):
        for j in range(100):
            assert matlib.exp(i, j) == i ** j


## @brief Tests root of two numbers.
# Tests an interval of (0, 100) to the root of interval (-100, 100), including multiple special cases.
def test_root():
    for i in range(100):
        for j in range(-100, 100):
            if j == 0 or i < 0 or (i == 0 and j < 0):
                assert matlib.nroot(i, j) == None
            else:
                assert matlib.nroot(i, j) == i ** (1 / j)

## @brief Tests absolute value of given number.
# Tests an interval of (-100, 100)
def test_absolute_value():
    for i in range(-100, 100):
        assert matlib.abs(i) == abs(i)

## @brief Tests modulo of two numbers.
# Tests every combination from an interval of (-100, 100), expecting error when second operand is 0.
def test_modulo():
    for i in range(-100, 100):
        for j in range(-100, 100):
            if j != 0:
                assert matlib.mod(i, j) == i % j
            else:
                assert matlib.mod(i, j) == None