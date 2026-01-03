#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(puzzle, word="XMAS"):
    total = 0
    height = len(puzzle)
    width = len(puzzle[0])
    coordinates = []
    # horizontal
    for r in range(height):
        for c in range(width - len(word) + 1):
            coordinates.append([(r, c + i) for i in range(len(word))])
    # vertical
    for c in range(width):
        for r in range(height - len(word) + 1):
            coordinates.append([(r + i, c) for i in range(len(word))])
    # diagonal \
    for r in range(height - len(word) + 1):
        for c in range(width - len(word) + 1):
            coordinates.append([(r + i, c + i) for i in range(len(word))])
    # diagonal /
    for r in range(height - len(word) + 1):
        for c in range(len(word) - 1, width):
            coordinates.append([(r + i, c - i) for i in range(len(word))])
    for coordinate in coordinates:
        # Build word
        candidate = "".join(puzzle[r][c] for r, c in coordinate)
        if candidate == word or candidate[::-1] == word:
            total += 1
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    word_puzzle = []
    with open(file_path, "r") as fin:
        for line in fin:
            word_puzzle.append([letter for letter in line.strip()])
    print(main(word_puzzle))
