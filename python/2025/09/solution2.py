# --- Part Two ---
#
# The Elves just remembered: they can only switch out tiles that are red or green. So, your rectangle can only include
# red or green tiles.
#
# In your list, every red tile is connected to the red tile before and after it by a straight line of green tiles. The
# list wraps, so the first red tile is also connected to the last red tile. Tiles that are adjacent in your list will
# always be on either the same row or the same column.
#
# Using the same example as before, the tiles marked X would be green:
#
# ..............
# .......#XXX#..
# .......X...X..
# ..#XXXX#...X..
# ..X........X..
# ..#XXXXXX#.X..
# .........X.X..
# .........#X#..
# ..............
#
# In addition, all of the tiles inside this loop of red and green tiles are also green. So, in this example, these are
# the green tiles:
#
# ..............
# .......#XXX#..
# .......XXXXX..
# ..#XXXX#XXXX..
# ..XXXXXXXXXX..
# ..#XXXXXX#XX..
# .........XXX..
# .........#X#..
# ..............
#
# The remaining tiles are never red nor green.
#
# The rectangle you choose still must have red tiles in opposite corners, but any other tiles it includes must now be
# red or green. This significantly limits your options.
#
# For example, you could make a rectangle out of red and green tiles with an area of 15 between 7,3 and 11,1:
#
# ..............
# .......OOOOO..
# .......OOOOO..
# ..#XXXXOOOOO..
# ..XXXXXXXXXX..
# ..#XXXXXX#XX..
# .........XXX..
# .........#X#..
# ..............
#
# Or, you could make a thin rectangle with an area of 3 between 9,7 and 9,5:
#
# ..............
# .......#XXX#..
# .......XXXXX..
# ..#XXXX#XXXX..
# ..XXXXXXXXXX..
# ..#XXXXXXOXX..
# .........OXX..
# .........OX#..
# ..............
#
# The largest rectangle you can make in this example using only red and green tiles has area 24. One way to do this is
# between 9,5 and 2,3:
#
# ..............
# .......#XXX#..
# .......XXXXX..
# ..OOOOOOOOXX..
# ..OOOOOOOOXX..
# ..OOOOOOOOXX..
# .........XXX..
# .........#X#..
# ..............
#
# Using two red tiles as opposite corners, what is the largest area of any rectangle you can make using only red and
# green tiles?

import sys

import numpy as np
from tqdm import tqdm


def get_area(coord1, coord2):
    return (abs(coord1[0] - coord2[0]) + 1) * (abs(coord1[1] - coord2[1]) + 1)


def rectangle_area(x_min, y_min, x_max, y_max):
    return np.sum(grid[y_min : y_max + 1, x_min : x_max + 1])


if __name__ == "__main__":
    # coordinates piped to sys.stdin
    coords = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            coords.append(tuple(int(n) for n in line.strip().split(",")))
    # print(coords)
    # Attempt that didn't work:
    # -------------------------
    # I represent the grid in a matrix (numpy array), draw the borders and used
    # flood-fill to get all the LEDs. Flood-fill didn't scale with the size of the
    # input (recursion depth).
    # Attempt that worked:
    # --------------------
    # Represent the grid in a matrix (numpy array), draw vertical lines (with fix for corners)
    # and do horizontal ray-casting to fill it up.
    grid_width = max(x for x, y in coords) + 1
    grid_height = max(y for x, y in coords) + 1
    grid = np.zeros((grid_height, grid_width), dtype=np.uint8)
    # Draw vertical lines
    last_coord = coords[0]
    for coord in coords[1:] + [coords[0]]:
        if coord[0] == last_coord[0]:
            y_max = max(coord[1], last_coord[1])
            y_min = min(coord[1], last_coord[1])
            grid[y_min : y_max + 1, coord[0]] = 1
        last_coord = coord
    # print(grid)
    # print()
    # Fix corners first for proper ray-casting
    for y in tqdm(range(grid_height)):
        if np.sum(grid[y, :]) % 2 == 1:
            crosses = 0
            for x in range(0, grid_width):
                if grid[y, x] == 1:
                    crosses += 1
                if crosses % 2 == 0:
                    grid[y, x] = 0
    # print(grid)
    # print()
    # Throw rays
    for y in tqdm(range(grid_height)):
        # Get index of x == 1's
        xs = np.where(grid[y, :] == 1)[0]
        last = 0
        fill = False
        for x in xs:
            if fill:
                grid[y, last : x + 1] = 1
                fill = False
            else:
                fill = True
            last = x
        if fill:
            grid[y, last : grid_width + 1] = 1
        # Slower inner loop
        # crosses = 0
        # for x in range(0, grid_width):
        #     if grid[y, x] == 1:
        #         crosses += 1
        #     elif crosses % 2 == 1:
        #         grid[y, x] = 1
    # print(grid)
    # main loop
    # O(n^2) is slow (30 mins), probably needs more pruning of the search space
    max_area = 0
    for i, coord1 in tqdm(enumerate(coords), total=len(coords)):
        for j, coord2 in enumerate(coords):
            if i >= j:
                continue
            area = get_area(coord1, coord2)
            if area > max_area:
                x_min = min(coord1[0], coord2[0])
                x_max = max(coord1[0], coord2[0])
                y_min = min(coord1[1], coord2[1])
                y_max = max(coord1[1], coord2[1])
                if (
                    grid[y_min, x_min] == 1
                    and grid[y_min, x_max] == 1
                    and grid[y_max, x_max] == 1
                    and grid[y_max, x_min] == 1
                ):
                    if area == rectangle_area(x_min, y_min, x_max, y_max):
                        max_area = area
    print(max_area)
