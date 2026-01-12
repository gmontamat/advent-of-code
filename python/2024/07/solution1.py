#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def dfs(result, numbers, count):
    if len(numbers) > 0:
        for operand in ["+", "*"]:
            if operand == "+":
                if result - numbers[-1] > 0:
                    count = dfs(result - numbers[-1], numbers[:-1], count)
                elif result - numbers[-1] == 0:
                    count += 1
                    return count
                else:
                    return count
            elif operand == "*":
                if result % numbers[-1] == 0:
                    if result // numbers[-1] == 1:
                        count += 1
                        return count
                    else:
                        count = dfs(result // numbers[-1], numbers[:-1], count)
                else:
                    return count
    return count


def main(results, numbers):
    total = 0
    for result, nums in zip(results, numbers):
        if dfs(result, nums, 0) > 0:
            total += result
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    results = []
    numbers = []
    with open(file_path, "r") as fin:
        for line in fin:
            results.append(int(line.strip().split(":")[0]))
            numbers.append([int(i) for i in line.strip().split(":")[1].split()])
    print(main(results, numbers))
