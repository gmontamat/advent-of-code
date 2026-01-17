#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def dfs(tmap, y, x, ends):
    current = tmap[y][x]
    if current == 9:
        ends.append((y, x))
        return
    # up
    if y > 0 and tmap[y - 1][x] == current + 1:
        dfs(tmap, y - 1, x, ends)
    # down
    if y < len(tmap) - 1 and tmap[y + 1][x] == current + 1:
        dfs(tmap, y + 1, x, ends)
    # left
    if x > 0 and tmap[y][x - 1] == current + 1:
        dfs(tmap, y, x - 1, ends)
    # right
    if x < len(tmap[0]) - 1 and tmap[y][x + 1] == current + 1:
        dfs(tmap, y, x + 1, ends)


def main(tmap):
    height = len(tmap)
    width = len(tmap[0])
    trailheads = []
    for y in range(height):
        for x in range(width):
            if tmap[y][x] == 0:
                # trailhead
                trailheads.append((y, x))
    # get score of each
    total = 0
    for y, x in trailheads:
        ends = []  # map positions where trail ends
        dfs(tmap, y, x, ends)
        total += len(set(ends))
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    tmap = []
    with open(file_path, "r") as fin:
        for line in fin:
            tmap.append([int(d) for d in line.strip()])
    print(main(tmap))
