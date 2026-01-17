#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def dfs(tmap, y, x, total):
    current = tmap[y][x]
    if current == 9:
        total += 1
        return total
    # up
    if y > 0 and tmap[y - 1][x] == current + 1:
        total = dfs(tmap, y - 1, x, total)
    # down
    if y < len(tmap) - 1 and tmap[y + 1][x] == current + 1:
        total = dfs(tmap, y + 1, x, total)
    # left
    if x > 0 and tmap[y][x - 1] == current + 1:
        total = dfs(tmap, y, x - 1, total)
    # right
    if x < len(tmap[0]) - 1 and tmap[y][x + 1] == current + 1:
        total = dfs(tmap, y, x + 1, total)
    return total


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
    rank = 0
    for y, x in trailheads:
        rank += dfs(tmap, y, x, 0)
    return rank


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    tmap = []
    with open(file_path, "r") as fin:
        for line in fin:
            tmap.append([int(d) for d in line.strip()])
    print(main(tmap))
