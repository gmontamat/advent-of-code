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


def main(grid_size, falling_bytes):
    """Advent of pathfinding again like 2 days ago"""
    y_start, x_start = 0, 0
    y_end, x_end = grid_size - 1, grid_size - 1
    for i in range(0 if grid_size == 7 else 1024, len(falling_bytes)):
        grid = np.full((grid_size, grid_size), ".", dtype="<U1")
        for j in range(i):
            x, y = falling_bytes[j]
            grid[y, x] = "#"
        if astar(grid, (x_start, y_start), (x_end, y_end)) == np.inf:
            return falling_bytes[i - 1]
    return falling_bytes[-1]


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    if os.path.basename(file_path) == "input":
        grid_size = 71
    else:
        grid_size = 7
    falling = []
    with open(file_path, "r") as fin:
        for line in fin:
            x, y = line.strip().split(",")
            x, y = int(x), int(y)
            falling.append((int(x), int(y)))
    print(",".join(str(i) for i in main(grid_size, falling)))
