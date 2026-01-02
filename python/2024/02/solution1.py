#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(reports):
    safe = 0
    for report in reports:
        if report == sorted(report):
            for i, _next in enumerate(report[1:]):
                if _next - report[i] == 0:
                    break
                elif _next - report[i] > 3:
                    break
            else:
                safe += 1
        elif report == sorted(report, reverse=True):
            for i, _next in enumerate(report[1:]):
                if _next - report[i] == 0:
                    break
                elif report[i] - _next > 3:
                    break
            else:
                safe += 1
    return safe


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    reports = []
    with open(file_path, "r") as fin:
        for line in fin:
            reports.append([int(n) for n in line.strip().split()])
    print(main(reports))
