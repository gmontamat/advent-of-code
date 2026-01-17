#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(disk):
    size = sum(disk)
    block_sizes = disk[::2]
    space_sizes = [d for d in disk[1::2] if d > 0]
    disk_ids = []  # -1 if empty, id of block if data
    block_id = 0
    flag_block = True
    for d in disk:
        if flag_block:
            for _ in range(d):
                disk_ids.append(block_id)
            block_id += 1
            flag_block = False
        else:
            for _ in range(d):
                disk_ids.append(-1)
            flag_block = True
    assert block_id == len(block_sizes) == max(disk_ids) + 1
    # defrag
    current_id = max(disk_ids)
    current_size_idx = -1
    while current_id > 0:
        # print("".join(str(d) if d >= 0 else "." for d in disk_ids))
        next_space_start = 0
        current_size = block_sizes[current_size_idx]
        current_block_start = disk_ids.index(current_id)
        for i, space_size in enumerate(space_sizes):
            current_space_start = disk_ids.index(-1, next_space_start)
            if current_space_start > current_block_start:
                break
            if current_size <= space_size:
                for j in range(current_size):
                    disk_ids[current_block_start + j] = -1
                    disk_ids[current_space_start + j] = current_id
                if current_size == space_size:  # entire space used
                    space_sizes = space_sizes[:i] + space_sizes[i+1:]
                else:
                    space_sizes[i] = space_size - current_size
                break
            next_space_start = current_space_start + space_size
        current_size_idx -= 1
        current_id -= 1
    # print("".join(str(d) if d >= 0 else "." for d in disk_ids))
    # checksum
    checksum = 0
    for i, block_id in enumerate(disk_ids):
        if block_id < 0:
            continue
        checksum += i * block_id
    return checksum


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    with open(file_path, "r") as fin:
        for line in fin:
            disk = [int(d) for d in line.strip()]
    print(main(disk))
