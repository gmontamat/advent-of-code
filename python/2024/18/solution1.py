#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "numpy",
# ]
# ///

import heapq
import os
import sys

import numpy as np


def get_neighbors(grid, position):
    x, y = position
    neighbors = []
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nx, ny = x + dx, y + dy
        if 0 <= ny < grid.shape[0] and 0 <= nx < grid.shape[1]:
            if grid[ny, nx] in ["."]:
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


def main(grid):
    """Advent of pathfinding again like 2 days ago"""
    y_start, x_start = 0, 0
    y_end, x_end = grid.shape[0] - 1, grid.shape[1] - 1
    return astar(grid, (x_start, y_start), (x_end, y_end))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    if os.path.basename(file_path) == "input":
        grid = np.full((71, 71), ".", dtype="<U1")
        max_bytes = 1024
    else:
        grid = np.full((7, 7), ".", dtype="<U1")
        max_bytes = 12
    with open(file_path, "r") as fin:
        count = 0
        for line in fin:
            x, y = line.strip().split(",")
            x, y = int(x), int(y)
            if count < max_bytes:
                grid[y, x] = "#"
                count += 1
    print(main(grid))
