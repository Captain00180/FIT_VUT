## @package Projekt_ivs_test
# @file projekt_ivs_test.py
# @brief Test for mathematical library called matlib.py app.
# @author Martin Gerža

import matlib
from math import *
import pytest

## @fn test_summation()
# @brief Tests summation of two numbers.
def test_summation():
    for i in range(-100, 100):
        for j in range(-100, 100):
            assert matlib.sum(i, j) == i + j


## @fn test_subtraction()
# @brief Tests subtraction of two numbers.
def test_subtraction():
    for i in range(-100, 100):
        for j in range(-100, 100):
            assert matlib.diff(i, j) == i - j


## @fn test_multiplication()
# @brief Tests multiplication of two numbers
def test_multiplication():
    for i in range(-100, 100):
        for j in range(-100, 100):
            assert matlib.mul(i, j) == i * j


## @fn test_division()
# @brief Tests division of two numbers
def test_division():
    for i in range(-100, 100):
        for j in range(-100, 100):
            if j != 0:
                assert matlib.div(i, j) == i / j
            else:
                assert matlib.div(i, j) == None


## @fn test_factorial()
# @brief Tests factorial of given number.
def test_factorial():
    for i in range(-10, 100):
        if i >= 0:
            assert matlib.fact(i) == factorial(i)
        else:
            assert matlib.fact(i) == None


## @fn test_power()
# @brief Tests power of two numbers
def test_power():
    for i in range(-100, 100):
        for j in range(100):
            assert matlib.exp(i, j) == i ** j


## @fn test_root()
# @brief Tests root of two numbers.
def test_root():
    for i in range(100):
        for j in range(-100, 100):
            if j == 0 or i < 0 or (i == 0 and j < 0):
                assert matlib.nroot(i, j) == None
            else:
                assert matlib.nroot(i, j) == i ** (1 / j)

## @fn test_absolut_value()
# @brief Tests absolut value of given number
def test_absolut_value():
    for i in range(-100, 100):
        assert matlib.abs(i) == abs(i)

## @fn test_modulo()
# @brief Tests modulo of two numbers
def test_modulo():
    for i in range(-100, 100):
        for j in range(-100, 100):
            if j != 0:
                assert matlib.mod(i, j) == i % j
            else:
                assert matlib.mod(i, j) == None
