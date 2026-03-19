#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(locks, keys):
    lock_vals = []
    for lock in locks:
        lock_value = []
        for column in range(5):
            height = 0
            for row in lock[1:]:
                if row[column] == ".":
                    lock_value.append(height)
                    break
                else:
                    height += 1
        lock_vals.append(lock_value)
    key_vals = []
    for _key in keys:
        key_value = []
        for column in range(5):
            height = 0
            for row in _key[::-1][1:]:
                if row[column] == ".":
                    key_value.append(height)
                    break
                else:
                    height += 1
        key_vals.append(key_value)
    fits = 0
    for lock in lock_vals:
        for _key in key_vals:
            if all([l + k < 6 for l, k in zip(lock, _key)]):
                fits += 1
    return fits


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    locks = []
    keys = []
    with open(file_path, "r") as fin:
        current = []
        for line in fin:
            if not line.strip():
                if all([c == "#" for c in current[0]]):
                    locks.append(current)
                elif all([c == "#" for c in current[-1]]):
                    keys.append(current)
                else:
                    raise IOError
                current = []
            else:
                current.append([c for c in line.strip()])
        if all([c == "#" for c in current[0]]):
            locks.append(current)
        elif all([c == "#" for c in current[-1]]):
            keys.append(current)
        else:
            raise IOError
    print(main(locks, keys))
