#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "numpy",
# ]
# ///

import sys

import numpy as np


def main(grid, moves):
    height, width = grid.shape
    y, x = np.where(grid == "@")
    y, x = int(y[0]), int(x[0])
    for move in moves:
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
        elif move == "v":
            y_new = y
            while True:
                y_new += 1
                if grid[y_new, x] == ".":
                    # Move down
                    for i in range(y_new, y, -1):
                        grid[i, x] = grid[i - 1, x]
                    grid[y, x] = "."
                    y += 1
                    break
                elif grid[y_new, x] == "#":
                    break
        elif move == "^":
            y_new = y
            while True:
                y_new -= 1
                if grid[y_new, x] == ".":
                    # Move up
                    for i in range(y_new, y):
                        grid[i, x] = grid[i + 1, x]
                    grid[y, x] = "."
                    y -= 1
                    break
                elif grid[y_new, x] == "#":
                    break
    # print(grid)
    ys, xs = np.where(grid == "O")
    result = 0
    for y, x in zip(ys, xs):
        result += 100 * y + x
    return result


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    grid = []
    moves = []
    load_grid = True
    with open(file_path, "r") as fin:
        for line in fin:
            if load_grid:
                if line.strip() == "":
                    load_grid = False
                    continue
                grid.append([c for c in line.strip()])
            else:
                for c in line.strip():
                    moves.append(c)
    print(main(np.array(grid), moves))
