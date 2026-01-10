#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "numpy",
# ]
# ///

import sys

import numpy as np

ORIENTATIONS = [(-1, 0), (0, 1), (1, 0), (0, -1)]


def main(original_map):
    """
    A loop is found when the same position (x, y) and
    orientation are found twice while navigating.
    Optimization: only try "O" in the solution1's Xs
    """
    height, width = original_map.shape
    positions = 0  # Track positions where we can put a "O"
    for y in range(height):
        for x in range(width):
            _map = original_map.copy()
            if _map[y, x] == ".":
                _map[y, x] = "#"  # This is the "O" we put
            else:
                continue
            # Navigate
            visited = set()
            idx = 0
            current_y, current_x = np.argwhere(_map == "^")[0]
            while True:
                if (int(current_y), int(current_x), idx) in visited:
                    positions += 1
                    break  # loop found
                visited.add((int(current_y), int(current_x), idx))
                _map[current_y, current_x] = "X"
                # Move
                next_y = current_y + ORIENTATIONS[idx][0]
                next_x = current_x + ORIENTATIONS[idx][1]
                if next_y < 0 or next_y >= height or next_x < 0 or next_x >= width:
                    break  # no loop
                if _map[next_y, next_x] == "#":
                    idx = (idx + 1) % len(ORIENTATIONS)
                else:
                    current_y, current_x = next_y, next_x
    return positions


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    _map = []
    with open(file_path, "r") as fin:
        for line in fin:
            row = [c for c in line.strip()]
            _map.append(row)
    _map = np.array(_map)
    print(main(_map))
