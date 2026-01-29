#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "numpy",
#     "pillow",
# ]
# ///

import sys
import re
import zlib

import numpy as np
from PIL import Image



def compression_ratio(mask):
    """More random mask -> less compressible (closer to 1)"""
    b = np.ascontiguousarray(mask).tobytes()
    return len(zlib.compress(b)) / len(b)


def main(robots, height=7, width=11, seconds=9999):
    best_compression = 1.
    best_second = None
    for s in range(seconds):
        grid = np.zeros((height, width), dtype=np.uint8)
        for robot in robots:
            robot["px"] += robot["vx"]
            robot["px"] %= width
            robot["py"] += robot["vy"]
            robot["py"] %= height
            grid[robot["py"], robot["px"]] = 255
        if compression_ratio(grid) < best_compression:
            best_compression = compression_ratio(grid)
            best_second = s + 1
            # Draw and save
            Image.fromarray(grid, mode="L").save(f"output.png")
    return best_second


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    robots = []
    with open(file_path, "r") as fin:
        for line in fin:
            parsed = re.fullmatch(r"p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+)", line.strip())
            px, py, vx, vy = map(int, parsed.groups())
            robots.append({
                "px": px,
                "py": py,
                "vx": vx,
                "vy": vy,
            })
    if "example" in file_path:
        height, width = 7, 11
    else:
        height, width = 103, 101
    print(main(robots, height=height, width=width))
