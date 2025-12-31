#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(list1, list2):
    total = 0
    list1.sort()
    list2.sort()
    for a, b in zip(list1, list2):
        total += abs(a - b)
    return total


if __name__ == "__main__":
    # get input file from 1st argument
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
    file_path = sys.argv[1]
    list1 = []
    list2 = []
    with open(file_path, "r") as fin:
        for line in fin:
            l1, l2 = line.strip().split()
            list1.append(int(l1))
            list2.append(int(l2))
    print(main(list1, list2))
