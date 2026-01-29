#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import re
import sys


def main(robots, height=7, width=11, seconds=100):
    for _ in range(seconds):
        for robot in robots:
            robot["px"] += robot["vx"]
            robot["px"] %= width
            robot["py"] += robot["vy"]
            robot["py"] %= height
    qx = width // 2  # effectively ignores center
    qy = height // 2
    # validate
    # for row in range(height):
    #     r = ""
    #     for col in range(width):
    #         count = 0
    #         for robot in robots:
    #             if robot["px"] == col and robot["py"] == row:
    #                 count += 1
    #         r += str(count if count > 0 else ".")
    #     print(r)
    # Count robots in each quadrant
    q1, q2, q3, q4 = 0, 0, 0, 0
    for robot in robots:
        x = robot["px"]
        y = robot["py"]
        if x < qx and y < qy:
            q1 += 1
        elif x >= qx + 1 and y < qy:
            q2 += 1
        elif x < qx and y >= qy + 1:
            q3 += 1
        elif x >= qx + 1 and y >= qy + 1:
            q4 += 1
    return q1 * q2 * q3 * q4


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    robots = []
    with open(file_path, "r") as fin:
        for line in fin:
            parsed = re.fullmatch(
                r"p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+)", line.strip()
            )
            px, py, vx, vy = map(int, parsed.groups())
            robots.append(
                {
                    "px": px,
                    "py": py,
                    "vx": vx,
                    "vy": vy,
                }
            )
    if "example" in file_path:
        height, width = 7, 11
    else:
        height, width = 103, 101
    print(main(robots, height=height, width=width))
