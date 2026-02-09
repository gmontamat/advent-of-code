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


def get_neighbors(grid, position, orientation):
    x, y = position
    neighbors = []
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        if (-dx, -dy) == orientation:
            continue  # can't go backwards
        nx, ny = x + dx, y + dy
        if 0 <= ny < grid.shape[0] and 0 <= nx < grid.shape[1]:
            if grid[ny, nx] in [".", "E"]:
                neighbors.append(((nx, ny), (dx, dy)))
    return neighbors


def estimate_distance(position, end):
    """Manhattan distance + 1 penalty
    """
    x, y = position
    x_end, y_end = end
    if abs(y - y_end) > 0 and abs(x - x_end) > 0:
        penalty = 1000
    else:
        penalty = 0
    return abs(y - y_end) + abs(x - x_end) + penalty


def astar(grid, start, end):
    """Based on pseudocode from
    https://en.wikipedia.org/wiki/A*_search_algorithm
    """
    open_set = []
    # initial orientation (1, 0) facing east
    heapq.heappush(open_set, (estimate_distance(start, end), start, (1, 0)))
    f_score = {start: estimate_distance(start, end)}
    g_score = {start: 0}
    # came_from = {}
    while open_set:
        f, position, orientation = heapq.heappop(open_set)
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
        for new_position, new_orientation in get_neighbors(grid, position, orientation):
            penalty = 1000 if orientation != new_orientation else 0
            new_g = g_score[position] + 1 + penalty
            if new_position not in g_score or new_g < g_score[new_position]:
                # came_from[new_position] = position
                g_score[new_position] = new_g
                f_score[new_position] = new_g + estimate_distance(new_position, end)
                if new_position not in open_set:
                    heapq.heappush(
                        open_set, (f_score[new_position], new_position, new_orientation)
                    )
    return np.inf


def main(grid):
    """Advent of pathfinding (A*)"""
    start = np.where(grid == "S")
    y_start, x_start = int(start[0][0]), int(start[1][0])
    end = np.where(grid == "E")
    y_end, x_end = int(end[0][0]), int(end[1][0])
    return astar(grid, (x_start, y_start), (x_end, y_end))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    grid = []
    with open(file_path, "r") as fin:
        for line in fin:
            grid.append([c for c in line.strip()])
    print(main(np.array(grid)))
