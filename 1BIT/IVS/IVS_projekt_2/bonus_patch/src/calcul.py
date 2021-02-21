## @file calcul.py
# @brief Package for comunication with calculator's GUI.
# @details This file provides functions, that parse calculator input, convert it from its string format into numbers,
# evaluates the expression, calculates the result, if possible.
# @author Vojtěch Malý

from matlib import *
##  Converts the string 'a' to an integer or float
# @param a String that needs to be converted.
# @return Contents of 'a' converted to a number.
def conv(a):
    if a == "":
        return ""
    else:
        try:
            b = int(a)
        except ValueError:
            b = float(a)
        return b

##
# Returns error, if 'a' parameter is None type
# @param a Variable to be checked.
# @return Returns either error message, or parameter 'a'.
def invalid(a):
    if a == None:
        return "Invalid expression"
    else:
        return a

##
# Main function for evaluating input expresion.
# @param inp First string consisting of first inputed number.
# @param sig String containing sign that represents requested operation.
# @param anp Second string consisting of second inputed number.
# @return Result of the expresion, or an error message in case of an invalid expression
# @details Only function used with GUI. Evaluates the epxression and checks its validity. First strings are converted to integer or float instance and checked for valid types.
# Then everything is checked for requested operation and if everything was successful, result is returned.
def evaluate(inp, sig, anp):
    inp = conv(inp)
    anp = conv(anp)
    if anp == "":
        if sig == "!":
            answ = fact(inp)
            return invalid(answ)
        elif sig == "abs":
            return abs(inp)
    else:
        if sig == "+":
            return sum(inp, anp)
        elif sig == "-":
            return diff(inp, anp)
        elif sig == "*":
            return mul(inp, anp)
        elif sig == "/":
            answ = div(inp, anp)
            return invalid(answ)
        elif sig == "^":
            answ = exp(inp, anp)
            return invalid(answ)
        elif sig == "√":
            answ = nroot(inp, anp)
            return invalid(answ)
        elif sig == "%":
            return mod(inp, anp)
