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


def astar(grid, start, end, initial_orientation):
    """Based on pseudocode from
    https://en.wikipedia.org/wiki/A*_search_algorithm
    """
    open_set = []
    # initial orientation (1, 0) facing east
    heapq.heappush(open_set, (estimate_distance(start, end), start, initial_orientation))
    f_score = {start: estimate_distance(start, end)}
    g_score = {start: 0}
    while open_set:
        f, position, orientation = heapq.heappop(open_set)
        if position == end:
            return f
        for new_position, new_orientation in get_neighbors(grid, position, orientation):
            penalty = 1000 if orientation != new_orientation else 0
            new_g = g_score[position] + 1 + penalty
            if new_position not in g_score or new_g < g_score[new_position]:
                g_score[new_position] = new_g
                f_score[new_position] = new_g + estimate_distance(new_position, end)
                if new_position not in open_set:
                    heapq.heappush(
                        open_set, (f_score[new_position], new_position, new_orientation)
                    )
    return np.inf


def dfs(grid, path, end, orientation, score, max_score, all_paths):
    if path[-1] == end:
        all_paths.append(list(path))
        return
    for new_position, new_orientation in get_neighbors(grid, path[-1], orientation):
        new_score = score + 1 + (1000 if new_orientation != orientation else 0)
        if new_score + astar(grid, new_position, end, new_orientation) <= max_score:
            dfs(grid, path + (new_position,), end, new_orientation, new_score, max_score, all_paths)


def main(grid):
    start = np.where(grid == "S")
    y_start, x_start = int(start[0][0]), int(start[1][0])
    end = np.where(grid == "E")
    y_end, x_end = int(end[0][0]), int(end[1][0])
    # Use A* to get optimal score
    max_score = astar(grid, (x_start, y_start), (x_end, y_end), (1, 0))
    # Use DFS to get all paths
    all_paths = []
    dfs(
        grid,
        ((x_start, y_start),),
        (x_end, y_end),
        (1, 0),
        0,
        max_score,
        all_paths
    )
    nodes = set([])
    for path in all_paths:
        for node in path:
            nodes.add(node)
    return len(nodes)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    grid = []
    with open(file_path, "r") as fin:
        for line in fin:
            grid.append([c for c in line.strip()])
    print(main(np.array(grid)))
