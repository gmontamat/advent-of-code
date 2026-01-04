#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "networkx",
# ]
# ///

import sys

import networkx as nx


def main(edges, seqs):
    # Treating as a topological sorting problem
    total = 0
    for sequence in seqs:
        g_edges = [(a, b) for a, b in edges if a in sequence and b in sequence]
        graph = nx.DiGraph(g_edges)
        try:
            all_sorts_generator = nx.all_topological_sorts(graph)
            list_of_sorts = list(all_sorts_generator)
        except networkx.exception.NetworkXUnfeasible:
            # There is a cycle!
            print("cycle?!")
        if sequence not in list_of_sorts:
            # in-valid!
            if len(list_of_sorts) > 1:
                print(
                    "need to figure out shortest distance from sequence to topological sort!"
                )
            else:
                total += list_of_sorts[0][len(sequence) // 2]
    return total


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    edges = []
    sequences = []
    load_graph = True
    with open(file_path, "r") as fin:
        for line in fin:
            if not line.strip():
                load_graph = False
                continue
            if load_graph:
                n1, n2 = line.strip().split("|")
                edges.append((int(n1), int(n2)))
            else:
                sequences.append([int(n) for n in line.strip().split(",")])
    print(main(edges, sequences))
