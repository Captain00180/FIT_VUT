
##
# @file calc_controller.py
# @author David Hurta
# @brief This file includes class for handling calculator


from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
from calc_ui import Ui_MainWindow_Calculator
from calc_help_ui import Ui_windowHelp
from calcul import *


## @class Calculator_Controller
# @brief Class handles controlling calculator UI, which it initializes, when its object is created.
# @details It reacts to events, mainly pressing buttons (numbers, operators...) and handles them accordingly.
class Calculator_Controller(QMainWindow, Ui_MainWindow_Calculator):
    ## Class initializing function
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.show()

        # Window including help
        self.actionHelp.triggered.connect(self.showWindowHelp)

        # Numbers
        self.btnZero.clicked.connect(self.numberClicked)
        self.btnOne.clicked.connect(self.numberClicked)
        self.btnTwo.clicked.connect(self.numberClicked)
        self.btnThree.clicked.connect(self.numberClicked)
        self.btnFour.clicked.connect(self.numberClicked)
        self.btnFive.clicked.connect(self.numberClicked)
        self.btnSix.clicked.connect(self.numberClicked)
        self.btnSeven.clicked.connect(self.numberClicked)
        self.btnEight.clicked.connect(self.numberClicked)
        self.btnNine.clicked.connect(self.numberClicked)
        self.btnDot.clicked.connect(self.dotClicked)

        # Operators and etc.
        self.btnNeg.clicked.connect(self.negClicked)
        self.btnPlus.clicked.connect(self.binaryOperatorClicked)
        self.btnMinus.clicked.connect(self.binaryOperatorClicked)
        self.btnMul.clicked.connect(self.binaryOperatorClicked)
        self.btnDiv.clicked.connect(self.binaryOperatorClicked)
        self.btnMod.clicked.connect(self.binaryOperatorClicked)
        self.btnPower.clicked.connect(self.binaryOperatorClicked)
        self.btnSquareRoot.clicked.connect(self.binaryOperatorClicked)
        self.btnFactorial.clicked.connect(self.unaryOperatorClicked)
        self.btnAbsolute.clicked.connect(self.unaryOperatorClicked)
        self.btnEqual.clicked.connect(self.equalClicked)
        self.btnClear.clicked.connect(self.clearClicked)

        # Setting up details in a new window
        self.textBoxDisplay.setPlainText("0")
        self.textBoxDisplay.setAlignment(QtCore.Qt.AlignRight)

        # Initializing global variables
        ## Determines which mathematical operation is required
        self.operator = self.btnPlus
        ## First operand
        self.operand1 = 0
        ## Second operand
        self.operand2 = 0
        ## Checks if the equal sign was pressed
        self.wasEqualPressed = False


    ## Shows window including help for user
    def showWindowHelp(self):
        ## Help window widget
            self.windowHelp = QtWidgets.QWidget()
        ## UI window widget
            self.ui = Ui_windowHelp()
            self.ui.setupUi(self.windowHelp)
            self.windowHelp.show()


    ##  Handles clicking on numbers buttons
    def numberClicked(self):
        buttonClicked = self.sender()
        display = self.textBoxDisplay

        if self.wasEqualPressed == True:
            self.wasEqualPressed = False
            display.setPlainText("0")

        if display.toPlainText() != "0":
            display.setPlainText(display.toPlainText() + buttonClicked.text())
        else:
            display.setPlainText(buttonClicked.text())

        # Sets alignment and keeps scrollbar to the right
        display.setAlignment(QtCore.Qt.AlignRight)
        display.horizontalScrollBar().setValue(display.horizontalScrollBar().maximum())


    ##  Handles clicking on dot button
    def dotClicked(self):
        buttonClicked = self.sender()
        display = self.textBoxDisplay

        if display.toPlainText() == "Invalid expression":
            return

        if buttonClicked.text() not in display.toPlainText():
            display.setPlainText(display.toPlainText() + buttonClicked.text())

            # Sets alignment and keeps scrollbar to the right
            display.setAlignment(QtCore.Qt.AlignRight)
            display.horizontalScrollBar().setValue(display.horizontalScrollBar().maximum())


    ## Handles negating current value in display
    def negClicked(self):
        display = self.textBoxDisplay

        if display.toPlainText() == "Invalid expression":
            return

        if display.toPlainText() == "0":
            return

        if "-" not in display.toPlainText():
            display.setPlainText("-" + display.toPlainText())
        else:
            display.setPlainText(display.toPlainText()[1:])

        # Sets alignment and keeps scrollbar to the left
        display.setAlignment(QtCore.Qt.AlignRight)
        display.horizontalScrollBar().setValue(display.horizontalScrollBar().minimum())


    ## Handles clicking on unary operator's button
    def unaryOperatorClicked(self):
        buttonClicked = self.sender()
        display = self.textBoxDisplay

        if display.toPlainText() == "Invalid expression":
            return

        number = display.toPlainText()
        result = 0

        if buttonClicked == self.btnAbsolute:
            result = evaluate(number, "abs", "")
        elif buttonClicked == self.btnFactorial:
            result = evaluate(number, "!", "")

        display.setPlainText(str(result))
        display.setAlignment(QtCore.Qt.AlignRight)
        display.horizontalScrollBar().setValue(display.horizontalScrollBar().minimum())



    ## Handles clicking on binary operator's button
    def binaryOperatorClicked(self):
        display = self.textBoxDisplay

        if display.toPlainText() == "Invalid expression":
            return

        self.operator = self.sender()
        self.operand1 = (str)(display.toPlainText())

        display.setPlainText("0")
        display.setAlignment(QtCore.Qt.AlignRight)


    ## Handles clicking on equal button
    def equalClicked(self):
        if self.wasEqualPressed == True:
            return

        display = self.textBoxDisplay

        if display.toPlainText() == "Invalid expression":
            return

        result = 0
        operand1 = (str)(self.operand1)
        operand2 = (str)(display.toPlainText())

        if self.operator == self.btnPlus:
            result = evaluate(operand1, "+", operand2)
        elif self.operator == self.btnMinus:
            result = evaluate(operand1, "-", operand2)
        elif self.operator == self.btnMul:
            result = evaluate(operand1, "*", operand2)
        elif self.operator == self.btnDiv:
            result = evaluate(operand1, "/", operand2)
        elif self.operator == self.btnMod:
            result = evaluate(operand1, "%", operand2)
        elif self.operator == self.btnSquareRoot:
            result = evaluate(operand2, "√", operand1)
        elif self.operator == self.btnPower:
            result = evaluate(operand1, "^", operand2)

        if result == "Invalid expression":
            self.wasEqualPressed = False
            self.operator = self.btnPlus
            self.operand1 = 0
            self.operand2 = 0

        self.wasEqualPressed = True
        display.setPlainText(str(result))
        display.setAlignment(QtCore.Qt.AlignRight)
        display.horizontalScrollBar().setValue(display.horizontalScrollBar().minimum())


    ## Handles clicking on clear button
    def clearClicked(self):
        self.textBoxDisplay.setPlainText("0")
        self.textBoxDisplay.setAlignment(QtCore.Qt.AlignRight)
        self.wasEqualPressed = False
        self.operator = self.btnPlus
        self.operand1 = 0
        self.operand2 = 0
