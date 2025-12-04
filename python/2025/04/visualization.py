# --- Part Two ---
#
# Now, the Elves just need help accessing as much of the paper as they can.
#
# Once a roll of paper can be accessed by a forklift, it can be removed. Once a roll of paper is removed, the forklifts
# might be able to access more rolls of paper, which they might also be able to remove. How many total rolls of paper
# could the Elves remove if they keep repeating this process?
#
# Starting with the same example as above, here is one way you could remove as many rolls of paper as possible, using
# highlighted @ to indicate that a roll of paper is about to be removed, and using x to indicate that a roll of paper
# was just removed:
#
# Initial state:
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
# Remove 13 rolls of paper:
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
# Remove 12 rolls of paper:
# .......x..
# .@@.x.x.@x
# x@@@@...@@
# x.@@@@..x.
# .@.@@@@.x.
# .x@@@@@@.x
# .x.@.@.@@@
# ..@@@.@@@@
# .x@@@@@@@.
# ....@@@...
#
# Remove 7 rolls of paper:
# ..........
# .x@.....x.
# .@@@@...xx
# ..@@@@....
# .x.@@@@...
# ..@@@@@@..
# ...@.@.@@x
# ..@@@.@@@@
# ..x@@@@@@.
# ....@@@...
#
# Remove 5 rolls of paper:
# ..........
# ..x.......
# .x@@@.....
# ..@@@@....
# ...@@@@...
# ..x@@@@@..
# ...@.@.@@.
# ..x@@.@@@x
# ...@@@@@@.
# ....@@@...
#
# Remove 2 rolls of paper:
# ..........
# ..........
# ..x@@.....
# ..@@@@....
# ...@@@@...
# ...@@@@@..
# ...@.@.@@.
# ...@@.@@@.
# ...@@@@@x.
# ....@@@...
#
# Remove 1 roll of paper:
# ..........
# ..........
# ...@@.....
# ..x@@@....
# ...@@@@...
# ...@@@@@..
# ...@.@.@@.
# ...@@.@@@.
# ...@@@@@..
# ....@@@...
#
# Remove 1 roll of paper:
# ..........
# ..........
# ...x@.....
# ...@@@....
# ...@@@@...
# ...@@@@@..
# ...@.@.@@.
# ...@@.@@@.
# ...@@@@@..
# ....@@@...
#
# Remove 1 roll of paper:
# ..........
# ..........
# ....x.....
# ...@@@....
# ...@@@@...
# ...@@@@@..
# ...@.@.@@.
# ...@@.@@@.
# ...@@@@@..
# ....@@@...
#
# Remove 1 roll of paper:
# ..........
# ..........
# ..........
# ...x@@....
# ...@@@@...
# ...@@@@@..
# ...@.@.@@.
# ...@@.@@@.
# ...@@@@@..
# ....@@@...
#
# Stop once no more rolls of paper are accessible by a forklift. In this example, a total of 43 rolls of paper can be
# removed.
#
# Start with your original diagram. How many rolls of paper in total can be removed by the Elves and their forklifts?

import sys
import matplotlib.pyplot as plt
import numpy as np


def save_grid_png(cur_rolls, i):
    """
    Save the cur_rolls grid as a PNG image using matplotlib.
    "@" will be green, "." will be red.
    The image will be saved as {i:04d}.png in the current directory.
    """
    # Map "@" to 1 (green), "." to 0 (red)
    color_map = {"@": 1, ".": 0}
    arr = np.array([[color_map.get(cell, 0) for cell in row] for row in cur_rolls])
    # Create a custom color map: 0=red, 1=green
    from matplotlib.colors import ListedColormap
    cmap = ListedColormap(["black", "green"])
    plt.figure(figsize=(8, 8), dpi=100)
    plt.imshow(arr, cmap=cmap, interpolation='none')
    plt.axis('off')
    plt.tight_layout(pad=0)
    plt.savefig(f"{i:04d}.png", bbox_inches='tight', pad_inches=0)
    plt.close()


if __name__ == "__main__":
    # paper rolls piped to sys.stdin
    rolls = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            rolls.append([c for c in line.strip()])
    # main loop - convolutions! - numpy?
    accessible = 1
    iteration = 0
    all_accessible = []  # To keep track of each iteration
    while accessible > 0:
        cur_rolls = [cur_row[:] for cur_row in rolls]  # Deep copy of rolls
        iteration += 1
        save_grid_png(cur_rolls, iteration)
        accessible = 0
        for i in range(len(rolls)):
            for j in range(len(rolls[0])):
                if cur_rolls[i][j] != "@":
                    continue
                conv = 0
                conv += 1 if i - 1 >= 0 and j - 1 >= 0 and cur_rolls[i - 1][j - 1] == "@" else 0
                conv += 1 if j - 1 >= 0 and cur_rolls[i][j - 1] == "@" else 0
                conv += 1 if i + 1 < len(rolls) and j - 1 >= 0 and cur_rolls[i + 1][j - 1] == "@" else 0
                conv += 1 if i - 1 >= 0 and cur_rolls[i - 1][j] == "@" else 0
                conv += 1 if i + 1 < len(rolls) and cur_rolls[i + 1][j] == "@" else 0
                conv += 1 if i - 1 >= 0 and j + 1 < len(rolls[0]) and cur_rolls[i - 1][j + 1] == "@" else 0
                conv += 1 if j + 1 < len(rolls[0]) and cur_rolls[i][j + 1] == "@" else 0
                conv += 1 if i + 1 < len(rolls) and j + 1 < len(rolls[0]) and cur_rolls[i + 1][j + 1] == "@" else 0
                if conv < 4:
                    accessible += 1
                    # Does not modify cur_rolls
                    # We can still iterate in place and get the right answer
                    rolls[i][j] = "."
        all_accessible.append(accessible)
    print(sum(all_accessible))
