# Main python script. Launches the application
import sys
from PyQt5 import QtWidgets, uic
from mainwindow_controller import MainWindow

app = QtWidgets.QApplication(sys.argv)

window = MainWindow()
window.showFullScreen()

sys.exit(app.exec())

