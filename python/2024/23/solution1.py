#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(graph):
    triplets = set()
    for x in graph:
        for y in graph[x]:
            for z in graph[y]:
                if z in graph[x]:
                    nodes = [x, y, z]
                    nodes.sort()
                    triplets.add(tuple(nodes))
    total = 0
    for x, y, z in triplets:
        if x[0] == "t" or y[0] == "t" or z[0] == "t":
            total += 1
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    pairs = []
    with open(file_path, "r") as fin:
        for line in fin:
            pairs.append(line.strip().split("-"))
    graph = {}
    for x, y in pairs:
        if x not in graph:
            graph[x] = {y}
        else:
            graph[x].add(y)
        if y not in graph:
            graph[y] = {x}
        else:
            graph[y].add(x)
    print(main(graph))
