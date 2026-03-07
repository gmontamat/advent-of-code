#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys

# algorithm BronKerbosch1(R, P, X) is
#     if P and X are both empty then
#         report R as a maximal clique
#     for each vertex v in P do
#         BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
#         P := P \ {v}
#         X := X ⋃ {v}


def bron_kerbosch(r, p, x, g, maximalc):
    if len(p) == 0 and len(x) == 0:
        maximalc.append(r)  # report r as maximal clique
    for v in list(p):
        bron_kerbosch(r | {v}, p & graph[v], x & graph[v], g, maximalc)
        p.remove(v)
        x = x | {v}
    return maximalc


def main(graph):
    maximal_cliques = []
    bron_kerbosch(set(), set(graph.keys()), set(), graph, maximal_cliques)
    clique_number = 0
    maximum_clique = []
    for clique in maximal_cliques:
        if len(clique) > clique_number:
            clique_number = len(clique)
            maximum_clique = list(clique)
    return ",".join(sorted(maximum_clique))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
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
