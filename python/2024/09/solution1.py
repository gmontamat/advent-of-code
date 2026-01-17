#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(disk):
    size = sum(disk)
    disk_data = []  # -1 if empty, 1 if data
    disk_ids = []  # -1 if empty, id of block if data
    block_id = 0
    flag_block = True
    for d in disk:
        if flag_block:
            for _ in range(d):
                disk_ids.append(block_id)
                disk_data.append(1)
            block_id += 1
            flag_block = False
        else:
            for _ in range(d):
                disk_ids.append(-1)
                disk_data.append(-1)
            flag_block = True
    # defrag
    first_empty = disk_data.index(-1)
    last_block = size - disk_data[::-1].index(1) - 1
    while first_empty < last_block:
        # print("".join(str(d) if d >= 0 else "." for d in disk_ids))
        # Re-arrange
        disk_data[first_empty] = 1
        disk_data[last_block] = -1
        disk_ids[first_empty] = disk_ids[last_block]
        disk_ids[last_block] = -1
        first_empty = disk_data.index(-1)
        last_block = size - disk_data[::-1].index(1) - 1
    # print("".join(str(d) if d >= 0 else "." for d in disk_ids))
    # checksum
    checksum = 0
    for i, block_id in enumerate(disk_ids):
        if block_id < 0:
            break
        checksum += i * block_id
    return checksum


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    with open(file_path, "r") as fin:
        for line in fin:
            disk = [int(d) for d in line.strip()]
    print(main(disk))
