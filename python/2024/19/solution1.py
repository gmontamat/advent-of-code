#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def dfs(pattern, towels):
    if pattern == "":
        return True
    else:
        for towel in towels:
            if towel == pattern[: len(towel)]:
                return dfs(pattern[len(towel) :], towels)
    return False


def main(towels, patterns):
    count = 0
    for pattern in patterns:
        current = pattern
        found = False
        # Fast option 1 (largest match from the left)
        length = len(pattern)
        while length > 0:
            if pattern[0:length] in towels:
                pattern = pattern[length:]
                length = len(pattern)
                if pattern == "":
                    found = True
                    break
            else:
                length -= 1
        if found:
            count += 1
            continue
        # Fast option 2 (largest match from the right)
        pattern = current
        length = len(pattern)
        while length > 0:
            if pattern[-length:] in towels:
                pattern = pattern[: len(pattern) - length]
                length = len(pattern)
                if pattern == "":
                    found = True
                    break
            else:
                length -= 1
        if found:
            count += 1
            continue
        # Slow alternative if still not found: DFS
        if dfs(current, [towel for towel in towels if towel in current]):
            count += 1
    return count


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
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
