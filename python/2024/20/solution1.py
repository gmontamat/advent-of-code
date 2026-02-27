#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "numpy",
# ]
# ///

import heapq
import sys

import numpy as np


def get_neighbors(grid, position):
    x, y = position
    neighbors = []
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nx, ny = x + dx, y + dy
        if 0 <= ny < grid.shape[0] and 0 <= nx < grid.shape[1]:
            if grid[ny, nx] == ".":
                neighbors.append((nx, ny))
    return neighbors


def estimate_distance(position, end):
    """Manhattan distance"""
    x, y = position
    x_end, y_end = end
    return abs(y - y_end) + abs(x - x_end)


def astar(grid, start, end):
    """Based on pseudocode from
    https://en.wikipedia.org/wiki/A*_search_algorithm
    """
    open_set = []
    heapq.heappush(open_set, (estimate_distance(start, end), start))
    f_score = {start: estimate_distance(start, end)}
    g_score = {start: 0}
    # came_from = {}
    while open_set:
        f, position = heapq.heappop(open_set)
        if position == end:
            # node = end
            # draw = grid.copy()
            # while node != start:
            #     print(node)
            #     draw[node[1], node[0]] = "O"
            #     node = came_from[node]
            # print(node)
            # draw[node[1], node[0]] = "O"
            # print(draw)
            return f
        for new_position in get_neighbors(grid, position):
            new_g = g_score[position] + 1
            if new_position not in g_score or new_g < g_score[new_position]:
                # came_from[new_position] = position
                g_score[new_position] = new_g
                f_score[new_position] = new_g + estimate_distance(new_position, end)
                if new_position not in open_set:
                    heapq.heappush(open_set, (f_score[new_position], new_position))
    return np.inf


def main(grid, min_save):
    """Advent of pathfinding again like 2 days ago"""
    # A* is overkill here because they say only 1 path is possible but meh...
    # Slower code, but I had to change little from day 16 & 18
    start = np.where(grid == "S")
    y_start, x_start = int(start[0][0]), int(start[1][0])
    end = np.where(grid == "E")
    y_end, x_end = int(end[0][0]), int(end[1][0])
    grid[y_start][x_start] = "."
    grid[y_end][x_end] = "."
    picos_max = astar(grid, (x_start, y_start), (x_end, y_end))
    count = 0
    # Find all horizontal shortcuts
    for row in range(1, grid.shape[0] - 1):
        for col in range(1, grid.shape[1] - 1):
            try:
                if (
                    grid[row][col] in "."
                    and grid[row][col + 1] == "#"
                    and grid[row][col + 2] == "."
                ):
                    sc_grid = grid.copy()
                    sc_grid[row][col + 1] = "."
                    picos = astar(sc_grid, (x_start, y_start), (x_end, y_end))
                    if picos_max - picos >= min_save:
                        count += 1
            except IndexError:
                pass
            try:
                if (
                    grid[row][col] == "."
                    and grid[row + 1][col] == "#"
                    and grid[row + 2][col] == "."
                ):
                    sc_grid = grid.copy()
                    sc_grid[row + 1][col] = "."
                    picos = astar(sc_grid, (x_start, y_start), (x_end, y_end))
                    if picos_max - picos >= min_save:
                        count += 1
            except IndexError:
                pass
    return count


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    grid = []
    with open(file_path, "r") as fin:
        for line in fin:
            grid.append([c for c in line.strip()])
    if "example" in file_path:
        min_picos = 2
    else:
        min_picos = 100
    print(main(np.array(grid), min_picos))
