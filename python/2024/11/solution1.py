#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(rocks, blinks=25):
    # print(rocks)
    for _ in range(blinks):
        new_rocks = []
        for rock in rocks:
            if rock == 0:
                new_rocks.append(1)
            elif len(str(rock)) % 2 == 0:
                new_rocks.append(int(str(rock)[: len(str(rock)) // 2]))
                new_rocks.append(int(str(rock)[len(str(rock)) // 2 :]))
            else:
                new_rocks.append(rock * 2024)
        rocks = new_rocks
        # print(rocks)
    return len(rocks)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    with open(file_path, "r") as fin:
        for line in fin:
            rocks = [int(d) for d in line.strip().split()]
    print(main(rocks))
