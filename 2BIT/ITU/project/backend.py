from random import shuffle, randint
import json
# Lists of paths to card pictures. Set of cards is divided into two lists, where same index means those cards are a pair
set_words_1 = ["Sets/Words/" + str(x) + 'a' + '.jpg' for x in range(18)]
set_words_2 = ["Sets/Words/" + str(x) + 'b' + '.jpg' for x in range(18)]
set_body_1 = ["Sets/Body/" + str(x) + 'a' + '.jpg' for x in range(18)]
set_body_2 = ["Sets/Body/" + str(x) + 'b' + '.jpg' for x in range(18)]
set_flags_1 = ["Sets/Flags/" + str(x) + 'a' + '.jpg' for x in range(18)]
set_flags_2 = ["Sets/Flags/" + str(x) + 'b' + '.jpg' for x in range(18)]
set_shapes_1 = ["Sets/Shapes/" + str(x) + 'a' + '.jpg' for x in range(18)]
set_shapes_2 = ["Sets/Shapes/" + str(x) + 'b' + '.jpg' for x in range(18)]

# Picture for the back of a card
back_question = "Sets/Backs/back_01.png"
back_cards = "Sets/Backs/back_02.png"

class Player:
    def __init__(self):
        self.userName = "Player 1"
        self.XP = 0
        self.level = 1
        self.difficulty = "Medium"
        # Two halves of card sets. cardSet_1[idx] is a pair with cardSet_2[idx]
        self.cardSet_1 = set_words_1
        self.cardSet_2 = set_words_2
        # list of all cards in a card set
        self.cardFront = self.cardSet_1 + self.cardSet_2
        # back of the cards
        self.cardBack = back_cards
        # gameState object - gets created each time a new game is played
        self.game = None

        self.data = {
                "userName": self.userName,
                "XP": self.XP,
                "level": self.level,
                "difficulty": self.difficulty,
                "cardSet_1": self.cardSet_1,
                "cardSet_2": self.cardSet_2,
                "cardFront": self.cardFront,
                "cardBack": self.cardBack
                }
        # Read saved data
        self.readData()

    #Returns data as a dictionary
    def getData(self):
        self.updateData()
        return self.data

    # Updates the dictionary of data with current values
    def updateData(self):
        self.data = {
            "userName": self.userName,
            "XP": self.XP,
            "level": self.level,
            "difficulty": self.difficulty,
            "cardSet_1": self.cardSet_1,
            "cardSet_2": self.cardSet_2,
            "cardFront": self.cardFront,
            "cardBack": self.cardBack
        }
        self.saveData()

    # difficulty = ["Easy", "Medium", "Hard"]
    def setDifficulty(self, difficulty):
        self.difficulty = difficulty
        self.updateData()

    # back = number representing the back of cards
    def setCardBack(self, back):
        if back == 0:
            self.cardBack = back_cards
        elif back == 1:
            self.cardBack = back_question
        self.updateData()

    # front = number representing the set of cards
    def setCardFront(self, front):
        if front == 0:
            self.cardSet_1 = set_words_1
            self.cardSet_2 = set_words_2
            self.cardFront = set_words_1 + set_words_2
        elif front == 1:
            self.cardSet_1 = set_shapes_1
            self.cardSet_2 = set_shapes_2
            self.cardFront = set_shapes_1 + set_shapes_2
        elif front == 2:
            self.cardSet_1 = set_body_1
            self.cardSet_2 = set_body_2
            self.cardFront = set_body_1 + set_body_2
        elif front == 3:
            self.cardSet_1 = set_flags_1
            self.cardSet_2 = set_flags_2
            self.cardFront = set_flags_1 + set_flags_2
        self.updateData()

    def setUsername(self, name):
        self.userName = name
        self.updateData()

    # Saves data to a file
    def saveData(self):
        file = open("data.json", "w")
        file.write(str(self.data))
        file.close()

    # Reads data from a file
    def readData(self):
        try:
            file = open("data.json", "r")
        except IOError:
            self.saveData()
            return
        content = file.read().rstrip()
        content = content.replace("'", '"')
        content = json.loads(content)
        self.data = content

        self.userName = content["userName"]
        self.XP = content["XP"]
        self.level = content["level"]
        self.difficulty = content["difficulty"]
        self.cardSet_1 = content["cardSet_1"]
        self.cardSet_2 = content["cardSet_2"]
        self.cardFront = content["cardFront"]
        self.cardBack = content["cardBack"]

    # Creates a GameState object, initialises it to players data
    # mode = number. 0 means game against CPU, anything else is local multiplayer
    def playGame(self, mode):
        self.game = None
        self.game = GameState(self.data, mode)


class GameState:
    def __init__(self, data, mode):
        self.playerOne = data["userName"]
        self.playerTwo = "Player 2"

        self.score_1 = 0
        self.score_2 = 0
        # 0 == vs CPU. This is used to generate CPU moves
        self.mode = mode
        self.turn = 0
        self.aiHits = 0
        self.cardsGuessed = 0
        self.difficulty = data["difficulty"]
        if self.mode == 0:
            self.playerTwo = "CPU " + self.difficulty
        # Saves the name of the winner after game is over
        self.winner = ""

        self.cardBack = data["cardBack"]
        self.cardSet_1 = data["cardSet_1"]
        self.cardSet_2 = data["cardSet_2"]

        # List of paired cards
        self.cards = [{"picture": self.cardSet_1[idx],
                       "pair": self.cardSet_2[idx],
                       "guessed": False} for idx in range(len(self.cardSet_1))] + \
                     [{"picture": self.cardSet_2[idx],
                       "pair": self.cardSet_1[idx],
                       "guessed": False} for idx in range(len(self.cardSet_1))]
        shuffle(self.cards)

        self.gameData = {}

    def getData(self):
        self.gameData = {
            "playerOne": self.playerOne,
            "playerTwo": self.playerTwo,
            "score_1": self.score_1,
            "score_2": self.score_2,
            "mode": self.mode,
            "turn": self.turn,
            "cardsGuessed": self.cardsGuessed,
            "difficulty": self.difficulty,
            "cardSet": self.cards,
            "cardBack": self.cardBack,
            "winner": self.winner
        }
        return self.gameData

    # Checks if game is over and sets the winner if it is
    # IF a player won against CPU, it adds XP and levels up if necessary
    def checkEnd(self):
        if self.cardsGuessed >= 36:
            # game is over
            self.winner = "Tie"
            if self.score_1 > self.score_2:
                self.winner = self.playerOne
            elif self.score_2 > self.score_1:
                self.winner = self.playerTwo
            # Add XP if player won against CPU
            if self.mode == 0 and self.winner == self.playerOne:
                user.XP += 40
                if user.XP >= user.level * 120:
                    # level up
                    user.XP -= user.level * 120
                    user.level += 1

            return True
        return False

    # Checks if two cards with given indices are a pair
    def checkPair(self, idx_1, idx_2):
        return self.cards[idx_1]["pair"] == self.cards[idx_2]["picture"]

    # Determines if chosen cards are a pair and modifies the game accordingly - adjust score, pass the turn
    # Returns True if cards match, False otherwise
    def evaluateMove(self, idx_1, idx_2):
        # Cards are a pair
        if self.checkPair(idx_1, idx_2):
            self.cards[idx_1]["guessed"] = True
            self.cards[idx_2]["guessed"] = True
            self.cardsGuessed += 2
            # Add score
            if self.turn == 0:
                self.score_1 += 5
            else:
                self.score_2 += 5
            return True
        # Cards are not a match
        else:
            # Subtract points, if the player is at least 15 points ahead
            if self.turn == 0:
                self.score_1 = (self.score_1 - 3) if self.score_1 > (15 + self.score_2) else self.score_1
            else:
                self.score_2 = (self.score_2 - 3) if self.score_2 > (15 + self.score_1) else self.score_2
            # Pass the turn
            self.turn = 1 - self.turn
            return False

    # Generates a CPU move based on difficulty
    # Returns the indices of cards CPU chose - they need to be checked by the app
    def CPUMove(self):
        pick_1 = None
        pick_2 = None
        chance = 15
        if self.difficulty == "Medium":
            chance = 25
        elif self.difficulty == "Hard":
            chance = 40
        # Pick a random card
        pick_1 = randint(0, 35)
        while  self.cards[pick_1]["guessed"]:
            pick_1 = randint(0, 35)
        
        # Determine if the CPU will hit a pair or not
        rand_num = randint(0, 100) + 10 * self.aiHits
        if rand_num < chance:
            # Hit
            self.aiHits += 1
            pick_2 = next(it for it in self.cards if it["picture"] == self.cards[pick_1]["pair"])
            pick_2 = self.cards.index(pick_2)
        else:
            self.aiHits = 0
            # Pick a random card
            pick_2 = randint(0, 35)
            while self.cards[pick_2]["guessed"] or pick_2 == pick_1:
                pick_2 = randint(0, 35)
        return [pick_1, pick_2]

user = Player()
user.saveData()
