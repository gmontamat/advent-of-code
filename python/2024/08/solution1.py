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
            if grid[row][col] != ".":
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
                antinode1 = r1 - (r2 - r1), c1 - (c2 - c1)
                antinode2 = r2 + (r2 - r1), c2 + (c2 - c1)
                if 0 <= antinode1[0] < height and 0 <= antinode1[1] < width:
                    antinodes.add(antinode1)
                if 0 <= antinode2[0] < height and 0 <= antinode2[1] < width:
                    antinodes.add(antinode2)
    return len(antinodes)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    grid = []
    with open(file_path, "r") as fin:
        for line in fin:
            grid.append([c for c in line.strip()])
    print(main(grid))
