#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys
import re


def main(memory):
    # Advent of Regex
    memory += "do()"  # for the last match
    regex = r"mul\([0-9]+,[0-9]+\)"
    total = 0
    matches = re.findall(regex, memory)
    for match in matches:
        num1, num2 = match[4:-1].split(",")
        total += int(num1) * int(num2)
    regex_neg = r"don't\(\).*?do\(\)"
    matches = re.findall(regex_neg, memory)
    for match in matches:
        neg_matches = re.findall(regex, match)
        for neg_match in neg_matches:
            num1, num2 = neg_match[4:-1].split(",")
            total -= int(num1) * int(num2)
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
