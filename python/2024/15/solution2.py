#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "numpy",
# ]
# ///

import sys

import numpy as np

np.set_printoptions(linewidth=np.inf)


def main(grid, moves):
    height, width = grid.shape
    y, x = np.where(grid == "@")
    y, x = int(y[0]), int(x[0])
    for move in moves:
        # user = input("...")
        # if user == "w":
        #     move = "^"
        # elif user == 's':
        #     move = "v"
        # elif user == 'a':
        #     move = "<"
        # elif user == 'd':
        #     move = ">"
        # elif user == 'q':
        #     break
        # else:
        #     continue
        # Logic is the same for horizontal moves
        if move == ">":
            x_new = x
            while True:
                x_new += 1
                if grid[y, x_new] == ".":
                    # Move right
                    for i in range(x_new, x, -1):
                        grid[y, i] = grid[y, i - 1]
                    grid[y, x] = "."
                    x += 1
                    break
                elif grid[y, x_new] == "#":
                    break
        elif move == "<":
            x_new = x
            while True:
                x_new -= 1
                if grid[y, x_new] == ".":
                    # Move left
                    for i in range(x_new, x):
                        grid[y, i] = grid[y, i + 1]
                    grid[y, x] = "."
                    x -= 1
                    break
                elif grid[y, x_new] == "#":
                    break
        # For vertical moves, track columns affected each row
        elif move == "v":
            moving_columns = [[x]]
            y_new = y
            while True:
                y_new += 1
                blocked = False
                new_columns = set()
                for column in moving_columns[-1]:
                    if grid[y_new, column] == "]":
                        new_columns.add(column)
                        new_columns.add(column - 1)
                    elif grid[y_new, column] == "[":
                        new_columns.add(column)
                        new_columns.add(column + 1)
                    elif grid[y_new, column] == "#":
                        blocked = True
                        break
                if blocked:
                    break
                if new_columns:
                    moving_columns.append(list(new_columns))
                else:
                    if np.all(grid[y_new, moving_columns[-1]] == "."):
                        # Move down
                        k = len(moving_columns)
                        for i, columns in enumerate(moving_columns[::-1]):
                            grid[y + k - i, columns] = grid[y + k - i - 1, columns]
                            grid[y + k - i - 1, columns] = "."
                        grid[y, x] = "."
                        y += 1
                        break
                    elif np.any(grid[y_new, moving_columns[-1]] == "#"):
                        break
        elif move == "^":
            moving_columns = [[x]]
            y_new = y
            while True:
                y_new -= 1
                blocked = False
                new_columns = set()
                for column in moving_columns[-1]:
                    if grid[y_new, column] == "]":
                        new_columns.add(column)
                        new_columns.add(column - 1)
                    elif grid[y_new, column] == "[":
                        new_columns.add(column)
                        new_columns.add(column + 1)
                    elif grid[y_new, column] == "#":
                        blocked = True
                        break
                if blocked:
                    break
                if new_columns:
                    moving_columns.append(list(new_columns))
                else:
                    if np.all(grid[y_new, moving_columns[-1]] == "."):
                        # Move up
                        k = len(moving_columns)
                        for i, columns in enumerate(moving_columns[::-1]):
                            grid[y - k + i, columns] = grid[y - k + i + 1, columns]
                            grid[y - k + i + 1, columns] = "."
                        grid[y, x] = "."
                        y -= 1
                        break
                    elif np.any(grid[y_new, moving_columns[-1]] == "#"):
                        break
        # for r in grid:
        #     print("".join(r.tolist()))
        # print()
        # print()
    ys, xs = np.where(grid == "[")
    result = 0
    for y, x in zip(ys, xs):
        result += 100 * y + x
    return result


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    grid = []
    moves = []
    load_grid = True
    mapping = {
        "#": "##",
        "O": "[]",
        ".": "..",
        "@": "@.",
    }
    with open(file_path, "r") as fin:
        for line in fin:
            if load_grid:
                if line.strip() == "":
                    load_grid = False
                    continue
                row = "".join([mapping[c] for c in line.strip()])
                grid.append([c for c in row])
            else:
                for c in line.strip():
                    moves.append(c)
    print(main(np.array(grid), moves))
