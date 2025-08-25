from enum import Enum
from pathlib import Path
from dataclasses import dataclass

INPUT_FILE = 'input.txt'

class TYPE(Enum):
    HIGH_CARD = 1
    PAIR = 2
    TWO_PAIR = 3
    THREE_OF_A_KIND = 4
    FULL_HOUSE = 5
    FOUR_OF_A_KIND = 6
    FIVE_OF_A_KIND = 7

cardWeights = {
    "J": 1,
    "2": 2,
    "3": 3,
    "4": 4,
    "5": 5,
    "6": 6,
    "7": 7,
    "8": 8,
    "9": 9,
    "T": 10,
    # "J": 11,
    "Q": 12,
    "K": 13,
    "A": 14
}

@dataclass
class Deck():
    def __init__(cls, cards = "", value = 0, range = 0, figure = TYPE.HIGH_CARD) -> None:
        cls.cards = cards
        cls.value = value
        cls.range = range
        cls.figure = figure
    cards: str
    value: int

    range: int
    figure: TYPE

    def __str__(self) -> str:
        # s = f"{self.range:3}, {self.cards}: {self.value}\t{self.figure}"
        s = f"{self.range},{self.cards},{self.value},{self.figure}"
        return s
    


class Hand():
    decks: list[Deck]
    def __init__(self) -> None:
        self.decks = []
        self.readDeck(INPUT_FILE)
        self.addType()


    def readDeck(self, path: Path) -> None:
        with open(path, "r") as file:
            for line in file.readlines():
                line = line.strip("\n").split(' ')
                deck = Deck()
                deck.cards = line[0]
                deck.value = int(line[1])
                self.decks.append(deck)

    def addType(self):
        high_card       = []
        pair            = []
        two_pair        = []
        three_of_kind   = []
        full_house      = []
        four_of_kind    = []
        five_of_kind    = []


        for i, deck in enumerate(self.decks):
            dic, jokers = self.countCard(deck)
            # if jokers != 0:
                # print(f"Deck: {deck.cards}")


            if (5 - jokers) in dic.values() or jokers == 5:
                self.decks[i].figure = TYPE.FIVE_OF_A_KIND
                five_of_kind.append(i)
            elif (4 - jokers) in dic.values() or jokers == 4:
                self.decks[i].figure = TYPE.FOUR_OF_A_KIND
                four_of_kind.append(i)
            elif len(dic) == 2:
            # elif ((((3-jokers) in dic.values() and 2 in dic.values())
            #     or
            #     (3 in dic.values() and (2-jokers) in dic.values()))
            #     and 
            #     len(dic) == 2
            # ):
                # print(f"len of Dic: {len(dic)}")
                self.decks[i].figure = TYPE.FULL_HOUSE
                full_house.append(i)
            elif (3 - jokers) in dic.values() or jokers == 3:
                self.decks[i].figure = TYPE.THREE_OF_A_KIND
                three_of_kind.append(i)
            elif (2 - jokers) in dic.values() and len(dic) == (3 - jokers):
                self.decks[i].figure = TYPE.TWO_PAIR
                two_pair.append(i)
            elif (2 - jokers) in dic.values() or jokers == 2:
                self.decks[i].figure = TYPE.PAIR
                pair.append(i)
            else:
                high_card.append(i)
            # print(deck)

        last_range = 0
        last_range = self.sortedFigure(high_card, last_range)
        last_range = self.sortedFigure(pair, last_range)
        last_range = self.sortedFigure(two_pair, last_range)
        last_range = self.sortedFigure(three_of_kind, last_range)
        last_range = self.sortedFigure(full_house, last_range)
        last_range = self.sortedFigure(four_of_kind, last_range)
        last_range = self.sortedFigure(five_of_kind, last_range)
        

    def sortedFigure(self, indexes: list, last_range: int) -> int:
        if len(indexes) == 0: return last_range

        isHigher = [0] * len(indexes)
        for i, index in enumerate(indexes):
            for j in range(0, len(indexes)):
                if self.getHigher(self.decks[index], self.decks[indexes[j]]):
                    isHigher[i] = isHigher[i] + 1
                # else:
                #     isHigher[j] = isHigher[j] + 1
            # print(f"Is higher than: {isHigher[i]}")
            # print("Next")
        
        sortedList = [0] * len(indexes)

        for i, j in enumerate(isHigher):
            sortedList[j] = indexes[i]

        for i in sortedList:
            last_range = last_range + 1
            self.decks[i].range = last_range
            # print(f"{self.decks[i]}")

        return last_range
        
        
    def countCard(self, deck: Deck) -> tuple[dict[str, int], int]:
            jokers = 0
            dic = {}
            for card in deck.cards:
                if card == "J":
                    jokers = jokers + 1
                else:
                    try:
                        dic[card] = dic[card] + 1
                    except KeyError:
                        dic[card] = 1

            return dic, jokers




    def getHigher(self, left: Deck, right: Deck) -> bool:
        # print(f"{left.cards} : {right.cards}")
        for i in range(len(left.cards)):
            if cardWeights[left.cards[i]] == cardWeights[right.cards[i]]:
                continue

            if cardWeights[left.cards[i]] > cardWeights[right.cards[i]]:
                # print("^^^^^ :")
                return True
            else:
                # print("      : ^^^^^")
                return False
            
        return False


            

    def getSum(self):
        sumOf = 0
        for deck in self.decks:
            sumOf = sumOf + deck.value * deck.range
        return sumOf

    def __str__(self) -> str:
        s = ""
        for deck in self.decks:
            s += f"\n{deck}"

        return s [1:]


if __name__ == "__main__":
    hand = Hand()
    # print(hand)
    print(f"Sum of: {hand.getSum()}")
