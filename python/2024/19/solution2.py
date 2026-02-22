#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def memoize(func):
    cache = {}

    def wrapper(*args):
        if args in cache:
            return cache[args]
        result = func(*args)
        cache[args] = result
        return result

    return wrapper


@memoize
def dfs(pattern, towels):
    if pattern == "":
        return 1
    else:
        total = 0
        for towel in towels:
            if towel == pattern[: len(towel)]:
                total += dfs(pattern[len(towel) :], towels)
        return total


def main(towels, patterns):
    count = 0
    for pattern in patterns:
        filtered = tuple(towel for towel in towels if towel in pattern)
        count += dfs(pattern, filtered)
    return count


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    patterns = []
    with open(file_path, "r") as fin:
        first = True
        for line in fin:
            if first:
                towels = line.strip().split(", ")
                first = False
            else:
                if line.strip() != "":
                    patterns.append(line.strip())
    print(main(towels, patterns))
