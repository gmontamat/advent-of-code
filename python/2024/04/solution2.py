#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(puzzle, word="MAS"):
    total = 0
    height = len(puzzle)
    width = len(puzzle[0])
    coordinates_r = []  # \
    coordinates_l = []  # /
    # Xes
    for r in range(height - len(word) + 1):
        for c in range(width - len(word) + 1):
            coordinates_r.append([(r + i, c + i) for i in range(len(word))])
            coordinates_l.append(
                [(r + len(word) - i - 1, c + i) for i in range(len(word))]
            )
    for coordinate_r, coordinate_l in zip(coordinates_r, coordinates_l):
        # Build word
        candidate_r = "".join(puzzle[r][c] for r, c in coordinate_r)
        candidate_l = "".join(puzzle[r][c] for r, c in coordinate_l)
        if (candidate_r == word or candidate_r[::-1] == word) and (
            candidate_l == word or candidate_l[::-1] == word
        ):
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
