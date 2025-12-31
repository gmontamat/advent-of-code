#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(list1, list2):
    similarity = 0
    for number in list1:
        count = list2.count(number)
        similarity += number * count
    return similarity


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
