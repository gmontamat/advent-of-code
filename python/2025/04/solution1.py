# --- Day 4: Printing Department ---
#
# You ride the escalator down to the printing department. They're clearly getting ready for Christmas; they have lots of
# large rolls of paper everywhere, and there's even a massive printer in the corner (to handle the really big print
# jobs).
#
# Decorating here will be easy: they can make their own decorations. What you really need is a way to get further into
# the North Pole base while the elevators are offline.
#
# "Actually, maybe we can help with that," one of the Elves replies when you ask for help. "We're pretty sure there's a
# cafeteria on the other side of the back wall. If we could break through the wall, you'd be able to keep moving. It's
# too bad all of our forklifts are so busy moving those big rolls of paper around."
#
# If you can optimize the work the forklifts are doing, maybe they would have time to spare to break through the wall.
#
# The rolls of paper (@) are arranged on a large grid; the Elves even have a helpful diagram (your puzzle input)
# indicating where everything is located.
#
# For example:
#
# ..@@.@@@@.
# @@@.@.@.@@
# @@@@@.@.@@
# @.@@@@..@.
# @@.@@@@.@@
# .@@@@@@@.@
# .@.@.@.@@@
# @.@@@.@@@@
# .@@@@@@@@.
# @.@.@@@.@.
#
# The forklifts can only access a roll of paper if there are fewer than four rolls of paper in the eight adjacent
# positions. If you can figure out which rolls of paper the forklifts can access, they'll spend less time looking and
# more time breaking down the wall to the cafeteria.
#
# In this example, there are 13 rolls of paper that can be accessed by a forklift (marked with x):
#
# ..xx.xx@x.
# x@@.@.@.@@
# @@@@@.x.@@
# @.@@@@..@.
# x@.@@@@.@x
# .@@@@@@@.@
# .@.@.@.@@@
# x.@@@.@@@@
# .@@@@@@@@.
# x.x.@@@.x.
#
# Consider your complete diagram of the paper roll locations. How many rolls of paper can be accessed by a forklift?

import sys

if __name__ == "__main__":
    # paper rolls piped to sys.stdin
    rolls = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            rolls.append([c for c in line.strip()])
    # main loop - convolutions! - numpy?
    accessible = 0
    for i in range(len(rolls)):
        for j in range(len(rolls[0])):
            if rolls[i][j] != "@":
                continue
            conv = 0
            conv += 1 if i - 1 >= 0 and j - 1 >= 0 and rolls[i - 1][j - 1] == "@" else 0
            conv += 1 if j - 1 >= 0 and rolls[i][j - 1] == "@" else 0
            conv += 1 if i + 1 < len(rolls) and j - 1 >= 0 and rolls[i + 1][j - 1] == "@" else 0
            conv += 1 if i - 1 >= 0 and rolls[i - 1][j] == "@" else 0
            conv += 1 if i + 1 < len(rolls) and rolls[i + 1][j] == "@" else 0
            conv += 1 if i - 1 >= 0 and j + 1 < len(rolls[0]) and rolls[i - 1][j + 1] == "@" else 0
            conv += 1 if j + 1 < len(rolls[0]) and rolls[i][j + 1] == "@" else 0
            conv += 1 if i + 1 < len(rolls) and j + 1 < len(rolls[0]) and rolls[i + 1][j + 1] == "@" else 0
            if conv < 4:
                accessible += 1
    print(accessible)
