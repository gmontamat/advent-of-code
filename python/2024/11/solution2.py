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
def rocks_generated(number, blinks_left):
    """Returns the number of rocks generated with
    current rock number and number of blinks.
    """
    if blinks_left == 0:
        return 1
    else:
        if number == 0:
            return rocks_generated(1, blinks_left - 1)
        elif len(str(number)) % 2 == 0:
            return rocks_generated(
                int(str(number)[: len(str(number)) // 2]), blinks_left - 1
            ) + rocks_generated(
                int(str(number)[len(str(number)) // 2 :]), blinks_left - 1
            )
        else:
            return rocks_generated(number * 2024, blinks_left - 1)


def main(rocks, blinks=75):
    total = 0
    for number in rocks:
        total += rocks_generated(number, blinks)
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    # advent of recursion with memoization
    with open(file_path, "r") as fin:
        for line in fin:
            rocks = [int(d) for d in line.strip().split()]
    print(main(rocks))
