from os import environ

f = open("input.txt", "r")
input = f.read()

def main():
    part = environ.get('part')

    
    totalScore = 0
    for i in input.splitlines():
        opponent = i[0]
        you = i[2]

        if part == 'part2':
            yourMove = getMove(opponent, you)
            totalScore += getScore(opponent, yourMove)
        else:
            totalScore += getScore(opponent, you)
        
    print(totalScore)

def getMove(opponent, outcome):
    if outcome == "X":
        if opponent == "A":
            return "Z"
        if opponent == "B":
            return "X"
        if opponent == "C":
            return "Y"

    if outcome == "Y":
        if opponent == "A":
            return "X"
        if opponent == "B":
            return "Y"
        if opponent == "C":
            return "Z"

    if outcome == "Z":
        if opponent == "A":
            return "Y"
        if opponent == "B":
            return "Z"
        if opponent == "C":
            return "X"



def getScore(opponent, you):
    if opponent == "A":
        if you == "X":
            return 4  # rock (1) draw (3)
        if you == "Y":
            return 8  # paper (2) win (6)
        if you == "Z":
            return 3  # scissor (3) loss (0)
    
    if opponent == "B":
        if you == "X":
            return 1  # rock (1) loss (0)
        if you == "Y":
            return 5  # paper (2) draw (3)
        if you == "Z":
            return 9  # scissor (3) win (6)
            
    if opponent == "C":
        if you == "X":
            return 7  # rock (1) win (6)
        if you == "Y":
            return 2  # paper (2) loss (0)
        if you == "Z":
            return 6  # scissor (3) draw (3)

    

main()


# A for Rock, B for Paper, and C for Scissors
# X for Rock, Y for Paper, and Z for Scissors
