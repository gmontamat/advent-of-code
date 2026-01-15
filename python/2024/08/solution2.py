#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(grid):
    height = len(grid)
    width = len(grid[0])
    antennas = {}
    antinodes = set()
    for row in range(height):
        for col in range(width):
            if grid[row][col] not in ["."]:
                antenna_type = grid[row][col]
                if antenna_type not in antennas:
                    antennas[antenna_type] = []
                antennas[antenna_type].append((row, col))
    # Get antinodes
    for antenna_type, positions in antennas.items():
        for i in range(len(positions)):
            for j in range(i + 1, len(positions)):
                r1, c1 = positions[i]
                r2, c2 = positions[j]
                dr = r2 - r1
                dc = c2 - c1
                r = 0
                c = 0
                while 0 <= r1 - r < height and 0 <= c1 - c < width:
                    antinodes.add((r1 - r, c1 - c))
                    r += dr
                    c += dc
                r = 0
                c = 0
                while 0 <= r2 + r < height and 0 <= c2 + c < width:
                    antinodes.add((r2 + r, c2 + c))
                    r += dr
                    c += dc
    return len(antinodes)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    grid = []
    with open(file_path, "r") as fin:
        for line in fin:
            grid.append([c for c in line.strip()])
    print(main(grid))
