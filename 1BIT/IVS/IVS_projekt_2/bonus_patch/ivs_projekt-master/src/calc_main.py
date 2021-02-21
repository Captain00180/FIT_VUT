## @file calc_main.py
# @brief This file is for launching the calculator app.
# @details It initializes the app, its window and handles its closing
# @author David Hurta

## @mainpage BC_Calc Documentation
#  This is the Doxygen generated documentation for our Calculator app.


from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication
from calc_controller import Calculator_Controller
import sys

## App object itself
app = QApplication(sys.argv)
## Application window object
mainWindow = Calculator_Controller()

sys.exit(app.exec_())
