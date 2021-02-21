from PyQt5 import uic, QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow, QDialog, QActionGroup, QButtonGroup

from ui_mainwindow import Ui_Pexesoland
from ui_playscreen import Ui_MainWindow as Ui_PlayWindow
from ui_localDi import Ui_Change_Username as Ui_LocalDialog
from backend import user

STYLESHEET_BG = "background-color: qradialgradient(spread:pad, cx:0.545, cy:0.0568182, " \
                "radius:1.39, fx:0.528249, fy:0.336, stop:0.102273 rgba(92, 92, 92, 255)," \
                " stop:0.994318 rgba(56, 56, 56, 255));"


class LocalDialog(QDialog, Ui_LocalDialog):
    def __init__(self, parent):
        super().__init__()
        self.setupUi(self)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint)
        self.show()
        self.parent = parent
        self.buttonBox.accepted.connect(self.goBack)

    def goBack(self):
        user.setUsername(self.lineEdit.text())
        self.parent.Username.setText(self.lineEdit.text())
        self.close()


class PlayWindow(QMainWindow, Ui_PlayWindow):
    def __init__(self, parent, mode):
        super().__init__()
        self.setupUi(self)
        self.parent = parent

        # Download data from the server
        self.gameData = user.game.getData()

        self.mode = self.gameData["mode"]
        self.difficulty = self.gameData["difficulty"]
        self.pushButton.clicked.connect(self.switchMain)

        self.label_5.setText(self.gameData["playerOne"])
        if self.mode == 0:
            self.label_4.setText("CPU " + self.difficulty)
        else:
            self.label_5.setText("Player 1")
            self.label_4.setText("Player 2")

        self.label_7.setText("SCORE\n0")
        self.label_8.setText("SCORE\n0")

        self.score_1 = 0
        self.score_2 = 0

        # Whose turn it is
        self.turn = 0

        self.frame.setStyleSheet(self.frame.styleSheet() + "border: 2px solid rgb(6, 205, 227);")

        # cards

        # a monstrous list of all buttons in the playing field. I hate it
        self.cards = [self.pushButton_1, self.pushButton_2 ,
                          self.pushButton_3 , self.pushButton_4 , self.pushButton_5 , self.pushButton_6 ,
                          self.pushButton_7 , self.pushButton_8 , self.pushButton_9, self.pushButton_10 ,
                          self.pushButton_11 , self.pushButton_12 , self.pushButton_13 , self.pushButton_14 ,
                          self.pushButton_15 , self.pushButton_16, self.pushButton_17 , self.pushButton_18 ,
                          self.pushButton_19 , self.pushButton_20 , self.pushButton_21 , self.pushButton_22 ,
                          self.pushButton_23, self.pushButton_24 , self.pushButton_25 , self.pushButton_26 ,
                          self.pushButton_27 , self.pushButton_28 , self.pushButton_29 , self.pushButton_30 ,
                          self.pushButton_31 , self.pushButton_32 , self.pushButton_33 , self.pushButton_34 ,
                          self.pushButton_35 , self.pushButton_36]

        # initialize all card backs
        for i in range(36):
            self.cards[i].setStyleSheet("image: url(" + self.gameData["cardBack"] + ");")
            self.cards[i].clicked.connect(self.uncover)

        self.pick_1 = None
        self.pick_2 = None

    def uncover(self):
        button = self.sender()
        # first pick
        if self.pick_1 is None:
            self.pick_1 = button
            idx = self.cards.index(button)
            front = self.gameData["cardSet"][idx]["picture"]
            # reveal the card
            button.setStyleSheet("image: url(" + front + ");")
        # second pick
        elif self.pick_2 is None and button is not self.pick_1:
            self.pick_2 = button
            idx2 = self.cards.index(button)
            front = self.gameData["cardSet"][idx2]["picture"]
            # reveal the card
            button.setStyleSheet("image: url(" + front + ");")

            # short timer
            self.pushButton.setEnabled(False)
            loop = QtCore.QEventLoop()
            QtCore.QTimer.singleShot(2000, loop.quit)
            loop.exec_()
            self.pushButton.setEnabled(True)

            idx1 = self.cards.index(self.pick_1)
            # Check the pair
            if user.game.evaluateMove(idx1, idx2):
                # update data
                self.gameData = user.game.getData()
                self.score_1 = self.gameData["score_1"]
                self.score_2 = self.gameData["score_2"]

                if self.turn == 0:
                    self.label_7.setText("SCORE\n" + str(self.score_1))
                else:
                    self.label_8.setText("SCORE\n" + str(self.score_2))

                self.pick_1.setStyleSheet("")
                self.pick_1.setEnabled(False)
                self.pick_2.setEnabled(False)
                self.pick_2.setStyleSheet("")
            else:
                # pair doesn't match
                self.gameData = user.game.getData()
                self.score_1 = self.gameData["score_1"]
                self.score_2 = self.gameData["score_2"]

                self.pick_1.setStyleSheet("image: url(" + self.gameData["cardBack"] + ");")
                self.pick_2.setStyleSheet("image: url(" + self.gameData["cardBack"] + ");")
                if self.turn == 0:
                    self.label_7.setText("SCORE\n" + str(self.score_1))
                else:
                    self.label_8.setText("SCORE\n" + str(self.score_2))

                # update the turn
                self.turn = self.gameData["turn"]
                if self.turn == 0:
                    self.frame.setStyleSheet(STYLESHEET_BG + "border: 2px solid rgb(6, 205, 227)")
                    self.frame_2.setStyleSheet(STYLESHEET_BG)
                else:
                    self.frame_2.setStyleSheet(STYLESHEET_BG + "border: 2px solid rgb(6, 205, 227)")
                    self.frame.setStyleSheet(STYLESHEET_BG)

                    # Generate AI move
                    if self.mode == 0:
                        while self.turn == 1 and not user.game.checkEnd():
                            self.AIMove()

            self.pick_1 = None
            self.pick_2 = None

            # check if game is done
            if user.game.checkEnd():
                # Update data
                self.gameData = user.game.getData()
                self.pushButton.setText("Return ")
                if self.gameData["winner"] != "Tie":
                    self.label_8.setText(self.gameData["winner"]  + " Wins!")
                    self.label_7.setText(self.gameData["winner"]  + " Wins!")
                else:
                    self.label_8.setText("Tie!")
                    self.label_7.setText("Tie!")
                for butt in self.cards:
                    butt.setEnabled(False)

    def AIMove(self):
        picks = user.game.CPUMove()
        pick_1 = self.cards[picks[0]]
        pick_2 = self.cards[picks[1]]

        # reveal
        front_1 = self.gameData["cardSet"][picks[0]]["picture"]
        front_2 = self.gameData["cardSet"][picks[1]]["picture"]

        pick_1.setStyleSheet("image: url(" + front_1 + ");")
        pick_2.setStyleSheet("image: url(" + front_2 + ");")

        # short timer
        self.pushButton.setEnabled(False)
        loop = QtCore.QEventLoop()
        QtCore.QTimer.singleShot(2000, loop.quit)
        loop.exec_()
        self.pushButton.setEnabled(True)

        # check the pair
        if user.game.evaluateMove(picks[0], picks[1]):
            # CPU Hit
            # update data
            self.gameData = user.game.getData()
            self.score_2 = self.gameData["score_2"]

            self.label_8.setText("SCORE\n" + str(self.score_2))

            pick_1.setStyleSheet("")
            pick_1.setEnabled(False)
            pick_2.setStyleSheet("")
            pick_2.setEnabled(False)
        # Pair doesn't match
        else:
            # update data
            self.gameData = user.game.getData()
            self.score_2 = self.gameData["score_2"]

            self.label_8.setText("SCORE\n" + str(self.score_2))
            pick_1.setStyleSheet("image: url(" + self.gameData["cardBack"] + ");")
            pick_2.setStyleSheet("image: url(" + self.gameData["cardBack"] + ");")

            self.frame.setStyleSheet(STYLESHEET_BG + "border: 2px solid rgb(6, 205, 227)")
            self.frame_2.setStyleSheet(STYLESHEET_BG)

            #update turn
            self.turn = self.gameData["turn"]
            self.frame.setStyleSheet(STYLESHEET_BG + "border: 2px solid rgb(6, 205, 227)")
            self.frame_2.setStyleSheet(STYLESHEET_BG)

    def switchMain(self):
        self.parent.playerData = self.parent.getData()
        xp = self.parent.playerData["XP"]
        level = self.parent.playerData["level"]
        self.parent.XpBar.setValue(xp)
        self.parent.XpBar.setMaximum(level * 120)
        self.parent.Level.setText("Level " + str(level))

        self.parent.show()
        self.close()


# Main menu window. Spawns child windows when needed.
class MainWindow(QMainWindow, Ui_Pexesoland):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        # Download data from the server, save it in the form of a dictionary variable
        self.playerData = self.getData()

        # Initialize player data
        self.Level.setText(str(self.playerData["level"]))
        self.XpBar.setMaximum(self.playerData["level"] * 120)
        self.XpBar.setValue(self.playerData["XP"])
        self.Username.setText(self.playerData["userName"])
        self.difficultySetting = self.playerData["difficulty"]

        self.resize(1500, 1000)
        self.playWin = None

        self.LocalPlayButton.clicked.connect(self.play)
        self.CPUPlayButton.clicked.connect(self.play)
        self.actionChange_Username.triggered.connect(self.changeUsername)

        # Menubar actions setup
        self.actionExit_to_Desktop.triggered.connect(self.close)
        self.actionFullscreen.changed.connect(self.toggleFullscreen)

        self.difficultyActionGroup = QActionGroup(self)
        self.difficultyActionGroup.addAction(self.actionEasy)
        self.difficultyActionGroup.addAction(self.actionMedium)
        self.difficultyActionGroup.addAction(self.actionHard)
        self.difficultyActionGroup.setExclusive(True)

        self.actionEasy.triggered.connect(self.changeDifficulty)
        self.actionMedium.triggered.connect(self.changeDifficulty)
        self.actionHard.triggered.connect(self.changeDifficulty)

        # Card fronts and back selection
        self.cardFrontGroup = QButtonGroup(self)
        self.cardFrontGroup.addButton(self.checkBox, 0)
        self.cardFrontGroup.addButton(self.checkBox_3, 1)
        self.cardFrontGroup.addButton(self.checkBox_4, 2)
        self.cardFrontGroup.addButton(self.checkBox_2, 3)
        self.cardFrontGroup.setExclusive(True)

        self.checkBox.stateChanged.connect(self.changeCardFront)
        self.checkBox_3.stateChanged.connect(self.changeCardFront)
        self.checkBox_4.stateChanged.connect(self.changeCardFront)
        self.checkBox_2.stateChanged.connect(self.changeCardFront)

        self.cardBackGroup = QButtonGroup()
        self.cardBackGroup.addButton(self.checkBox_5, 2)
        self.cardBackGroup.addButton(self.checkBox_6, 1)
        self.cardBackGroup.setExclusive(True)

        self.checkBox_6.stateChanged.connect(self.changeCardBack)
        self.checkBox_5.stateChanged.connect(self.changeCardBack)

        self.changeDifficulty()
        self.changeCardBack()
        self.changeCardFront()

        self.changeDialog = None

    def getData(self):
        return user.getData()

    def changeDifficulty(self):
        self.difficultySetting = self.difficultyActionGroup.checkedAction().text()
        user.setDifficulty(self.difficultySetting)

    def changeCardBack(self):
        but_name = self.cardBackGroup.checkedButton().objectName()
        num = 0 if but_name == "checkBox_5" else 1
        user.setCardBack(num)

    def changeCardFront(self):
        button = self.cardFrontGroup.checkedButton().objectName()
        num = 0
        if button == "checkBox":
            num = 0
        elif button == "checkBox_3":
            num = 1
        elif button == "checkBox_4":
            num = 2
        elif button == "checkBox_2":
            num = 3
        user.setCardFront(num)

    def changeUsername(self):
        if self.changeDialog is not None:
            self.changeDialog.deleteLater()
        self.changeDialog = LocalDialog(self)

    def toggleFullscreen(self):
        if self.actionFullscreen.isChecked():
            self.showFullScreen()
        else:
            self.showNormal()

    def play(self):
        mode = 0
        if self.sender() is self.LocalPlayButton:
            mode = 1

        self.playerData = self.getData()
        user.playGame(mode)
        if self.playWin is not None:
            self.playWin.deleteLater()
        self.playWin = PlayWindow(self, mode)
        if self.actionFullscreen.isChecked():
            self.playWin.showFullScreen()
        else:
            self.playWin.showNormal()
        self.hide()
