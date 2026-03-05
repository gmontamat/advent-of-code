#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import itertools
import sys

door = [
    ["7", "8", "9"],
    ["4", "5", "6"],
    ["1", "2", "3"],
    [None, "0", "A"],
]

robot = [
    [None, "^", "A"],
    ["<", "v", ">"],
]


def get_paths(start, end, keypad):
    steps = []
    row_start = [i for i, row in enumerate(keypad) if start in row][0]
    col_start = keypad[row_start].index(start)
    row_end = [i for i, row in enumerate(keypad) if end in row][0]
    col_end = keypad[row_end].index(end)
    if col_end > col_start:
        steps += [">"] * (col_end - col_start)
    elif col_end < col_start:
        steps += ["<"] * (col_start - col_end)
    if row_start > row_end:
        steps += ["^"] * (row_start - row_end)
    elif row_start < row_end:
        steps += ["v"] * (row_end - row_start)
    valid_paths = []
    for path in set(itertools.permutations(steps)):
        path = "".join(path)
        # Check that path doesn't go through None
        valid = True
        if len(keypad) > 2:
            invalid_pos = (3, 0)
        else:
            invalid_pos = (0, 0)
        current_pos = (row_start, col_start)
        for step in path:
            if step == "^":
                current_pos = (current_pos[0] - 1, current_pos[1])
            elif step == "v":
                current_pos = (current_pos[0] + 1, current_pos[1])
            elif step == "<":
                current_pos = (current_pos[0], current_pos[1] - 1)
            elif step == ">":
                current_pos = (current_pos[0], current_pos[1] + 1)
            if current_pos == invalid_pos:
                valid = False
                break
        if valid:
            valid_paths.append(path + "A")  # go to key and press it
    return valid_paths


def main(codes):
    # dynamic programming solution
    hash_table = {}
    # construct (robot#, start, end) -> minimum presses you press for robot to go from start to end and press it
    # last robot - trivial (you move your finger and press)
    for start in ["^", "<", "v", ">", "A"]:
        for end in ["^", "<", "v", ">", "A"]:
            hash_table[(3, start, end)] = 1
    # second to last robot - find all paths and use sequence that minimizes last robot
    for start in ["^", "<", "v", ">", "A"]:
        for end in ["^", "<", "v", ">", "A"]:
            if start == end:
                hash_table[(2, start, end)] = 1  # press A
                continue
            paths = get_paths(start, end, robot)
            min_presses = float("inf")
            for path in paths:
                presses = 0
                head = "A"  # stores position of controlling robot
                for k in path:
                    if head == k:
                        presses += 1  # press A
                    else:
                        presses += hash_table[
                            (3, head, k)
                        ]  # presses so that controlling robot moves to k and presses
                        head = k
                if presses < min_presses:
                    min_presses = presses
            hash_table[(2, start, end)] = min_presses
    # third robot - same
    for start in ["^", "<", "v", ">", "A"]:
        for end in ["^", "<", "v", ">", "A"]:
            if start == end:
                hash_table[(1, start, end)] = 1
                continue
            paths = get_paths(start, end, robot)
            min_presses = float("inf")
            for path in paths:
                presses = 0
                head = "A"
                for k in path:
                    if k == head:
                        presses += 1
                    else:
                        presses += hash_table[(2, head, k)]
                        head = k
                if presses < min_presses:
                    min_presses = presses
            hash_table[(1, start, end)] = min_presses
    # keypad
    for start in [str(i) for i in range(10)] + ["A"]:
        for end in [str(i) for i in range(10)] + ["A"]:
            if start == end:
                hash_table[(0, start, end)] = 1
                continue
            paths = get_paths(start, end, door)
            min_presses = float("inf")
            for path in paths:
                presses = 0
                head = "A"
                for k in path:
                    if k == head:
                        presses += 1
                    else:
                        presses += hash_table[(1, head, k)]
                        head = k
                if presses < min_presses:
                    min_presses = presses
            hash_table[(0, start, end)] = min_presses
    # print(hash_table)
    total = 0
    for code in codes:
        num = int("".join([d for d in code if d.isdigit()]))
        presses = 0
        head = "A"
        for c in code:
            presses += hash_table[(0, head, c)]
            head = c
        # print(num, presses)
        total += num * presses
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    codes = []
    with open(file_path, "r") as fin:
        for line in fin:
            codes.append(line.strip())
    print(main(codes))
