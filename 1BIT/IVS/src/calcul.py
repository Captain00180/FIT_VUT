## @file calcul.py
# @package calcul
# @author Vojtěch Malý
# @brief Package for comunication with calculator's GUI.
# This package provides function's, that emulate string to integer, make basic mathematical operation using mathematical library and retrns answer. In case of invalid operation or invalid combination of operators returns error message.
from matlib import *

## @fn conv(a)
# @brief Returns the string a in integer or float instance.
# @param[in] a String that need's to be converted.
# @param[out] out Integer or float, depends on a.
def conv(a):
    if a == "":
        return ""
    else:
        try:
            b = int(a)
        except ValueError:
            b = float(a)
        return b

## @fn invalid(a)
# @brief Returns error, if a is None type.
# @param[in] a Accepts every instance.
# @param[out] a Return's same input parameter, if it wasn't type: None.
def invalid(a):
    if a == None:
        return "Invalid expression"
    else:
        return a

## @fn evaluate(inp, sig, anp)
# @brief Main function for evaluating expresion.
# @param[in] inp First string consisting of first inputed number.
# @param[in] sig String containing sign that represent's requested operation.
# @param[in] anp Second string consisting of second inputed number.
# Only function used with GUI. First strings are converted to integer or float instance and checked for valid types. Then there is everything checked for requested operation and if everything was successful, answer is returned.
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
