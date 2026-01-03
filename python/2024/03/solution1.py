#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys
import re


def main(memory):
    # Advent of Regex
    regex = r"mul\([0-9]+,[0-9]+\)"
    total = 0
    matches = re.findall(regex, memory)
    for match in matches:
        num1, num2 = match[4:-1].split(",")
        total += int(num1) * int(num2)
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    memory = ""
    with open(file_path, "r") as fin:
        for line in fin:
            memory += line.strip()
    print(main(memory))
