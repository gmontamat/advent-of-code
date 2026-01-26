#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def floodfill(grid, start, items):
    row, col = start
    items.append(start)
    element = grid[row][col]
    # up
    if row + 1 < len(grid) and (row + 1, col) not in items and grid[row + 1][col] == element:
        floodfill(grid, (row + 1, col), items)
    # down
    if row > 0 and (row - 1, col) not in items and grid[row - 1][col] == element:
        floodfill(grid, (row - 1, col), items)
    # left
    if col > 0 and (row, col - 1) not in items and grid[row][col - 1] == element:
        floodfill(grid, (row, col - 1), items)
    # right
    if col + 1 < len(grid[row]) and (row, col + 1) not in items and grid[row][col + 1] == element:
        floodfill(grid, (row, col + 1), items)


def compute_perimeter(region):
    perimeter = 0
    for x, y in region:
        if (x + 1, y) not in region:
            perimeter += 1
        if (x - 1, y) not in region:
            perimeter += 1
        if (x, y + 1) not in region:
            perimeter += 1
        if (x, y - 1) not in region:
            perimeter += 1
    return perimeter


def main(garden):
    total = 0
    for row in range(len(garden)):
        for col in range(len(garden[0])):
            if garden[row][col]:
                # Obtain region with flood-fill
                region_items = []
                floodfill(garden, (row, col), region_items)
                area = len(region_items)
                perimeter = compute_perimeter(region_items)
                total += area * perimeter
                # Clear region
                for i, j in region_items:
                    garden[i] = [None if j == k else plant for k, plant in enumerate(garden[i])]
    return total


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
