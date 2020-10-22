
## @package calc_main
# @author David Hurta
# @file calc_main.py
# @brief This file is for launching the calculator app.


from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication
from calc_controller import Calculator_Controller
import sys

app = QApplication(sys.argv)
mainWindow = Calculator_Controller()

sys.exit(app.exec_())
