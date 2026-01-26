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


def compute_sides(region):
    x_right = set()
    x_left = set()
    y_up = set()
    y_down = set()
    for x, y in region:
        if (x + 1, y) not in region:
            x_right.add((x, y))
        if (x - 1, y) not in region:
            x_left.add((x, y))
        if (x, y + 1) not in region:
            y_up.add((x, y))
        if (x, y - 1) not in region:
            y_down.add((x, y))
    # de-duplicate continuous
    sides = 0
    for lines in [x_right, x_left]:
        xs = set([x for x, y in lines])
        for x in xs:
            ys = sorted(y for _x, y in lines if x == _x)
            sides += 1  # at least 1 side here
            for y_prev, y_next in zip(ys[:-1], ys[1:]):
                if y_next - y_prev > 1:
                    sides += 1
    for lines in [y_up, y_down]:
        ys = set([y for x, y in lines])
        for y in ys:
            xs = sorted(x for x, _y in lines if y == _y)
            sides += 1  # at least 1 side here
            for x_prev, x_next in zip(xs[:-1], xs[1:]):
                if x_next - x_prev > 1:
                    sides += 1
    return sides


def main(garden):
    total = 0
    for row in range(len(garden)):
        for col in range(len(garden[0])):
            if garden[row][col]:
                # Obtain region with flood-fill
                region_items = []
                floodfill(garden, (row, col), region_items)
                area = len(region_items)
                sides = compute_sides(region_items)
                # print(area, sides)
                total += area * sides
                # Clear region
                for i, j in region_items:
                    garden[i] = [None if j == k else plant for k, plant in enumerate(garden[i])]
    return total


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
