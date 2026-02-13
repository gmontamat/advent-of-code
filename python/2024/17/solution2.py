#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import re
import sys
from operator import xor


def run(reg_a, reg_b, reg_c, program):

    def adv(op):
        return reg_a // 2**op

    def bxl(op):
        return xor(reg_b, op)

    def bst(op):
        return op % 8

    def bxc(op):
        return xor(reg_b, reg_c)

    out = []
    pointer = 0
    while pointer < len(program):
        instruction = program[pointer]
        literal = program[pointer + 1]
        if literal == 4:
            combo = reg_a
        elif literal == 5:
            combo = reg_b
        elif literal == 6:
            combo = reg_c
        else:
            combo = literal
        if instruction == 0:
            reg_a = adv(combo)
        elif instruction == 1:
            reg_b = bxl(literal)
        elif instruction == 2:
            reg_b = bst(combo)
        elif instruction == 3:
            if reg_a != 0:
                pointer = literal
                continue
        elif instruction == 4:
            reg_b = bxc(None)
        elif instruction == 5:
            out.append(combo % 8)
        elif instruction == 6:
            reg_b = adv(combo)
        elif instruction == 7:
            reg_c = adv(combo)
        pointer += 2
    # print(",".join(str(i) for i in out))
    return out


def main(reg_a, reg_b, reg_c, program):
    reg_a = 35184372088832  # smallest number that produces output of len(program)
    # found it by increasing reg_a *= 2 and then brute-forcing
    n = len(program)
    while n > -1:
        while program[n - 1] != run(reg_a, reg_b, reg_c, program)[n - 1]:
            reg_a += 8 ** (n - 1)
        n -= 1
    while program != run(reg_a, reg_b, reg_c, program):
        reg_a += 1
    return reg_a


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    # Read file to a string
    with open(file_path, "r") as fin:
        content = fin.read()
    res = re.search("Register A: [0-9]+", content)
    reg_a = int(res.group().split(":")[-1].strip())
    res = re.search("Register B: [0-9]+", content)
    reg_b = int(res.group().split(":")[-1].strip())
    res = re.search("Register C: [0-9]+", content)
    reg_c = int(res.group().split(":")[-1].strip())
    res = re.search("Program: [0-7,]+", content)
    program = [int(x) for x in res.group().split(":")[-1].strip().split(",")]
    print(main(reg_a, reg_b, reg_c, program))
