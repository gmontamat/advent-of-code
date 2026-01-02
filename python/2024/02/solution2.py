#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def is_safe(report):
    if report == sorted(report):
        for i, _next in enumerate(report[1:]):
            if _next - report[i] == 0:
                break
            elif _next - report[i] > 3:
                break
        else:
            return True
    elif report == sorted(report, reverse=True):
        for i, _next in enumerate(report[1:]):
            if _next - report[i] == 0:
                break
            elif report[i] - _next > 3:
                break
        else:
            return True
    return False


def main(reports):
    safe = 0
    for report in reports:
        if is_safe(report):
            safe += 1
        else:
            for i in range(len(report)):
                report_2 = report[:i] + report[i+1:]
                if is_safe(report_2):
                    safe += 1
                    break
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
