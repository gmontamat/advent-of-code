# --- Part Two ---

# Thanks in part to your analysis, the Elves have figured out a little bit about the issue. They now know that the
# problematic data path passes through both dac (a digital-to-analog converter) and fft (a device which performs a fast
# Fourier transform).

# They're still not sure which specific path is the problem, and so they now need you to find every path from svr (the
# server rack) to out. However, the paths you find must all also visit both dac and fft (in any order).

# For example:

# svr: aaa bbb
# aaa: fft
# fft: ccc
# bbb: tty
# tty: ccc
# ccc: ddd eee
# ddd: hub
# hub: fff
# eee: dac
# dac: fff
# fff: ggg hhh
# ggg: out
# hhh: out

# This new list of devices contains many paths from svr to out:

# svr,aaa,fft,ccc,ddd,hub,fff,ggg,out
# svr,aaa,fft,ccc,ddd,hub,fff,hhh,out
# svr,aaa,fft,ccc,eee,dac,fff,ggg,out
# svr,aaa,fft,ccc,eee,dac,fff,hhh,out
# svr,bbb,tty,ccc,ddd,hub,fff,ggg,out
# svr,bbb,tty,ccc,ddd,hub,fff,hhh,out
# svr,bbb,tty,ccc,eee,dac,fff,ggg,out
# svr,bbb,tty,ccc,eee,dac,fff,hhh,out

# However, only 2 paths from svr to out visit both dac and fft.

# Find all of the paths that lead from svr to out. How many of those paths visit both dac and fft?

import sys
from collections import deque


def dfs(nodes, path, goal, max_depth, total):
    if path[-1] == goal:
        total += 1
        return total
    elif len(path) == max_depth:
        return total
    else:
        for _next in nodes[path[-1]]:
            if _next not in path:  # Avoid cycles
                total = dfs(nodes, path + [_next], goal, max_depth, total)
        return total


def dfs_check(nodes, path, goal, max_depth, total):
    if path[-1] == goal:
        if "dac" in path or "fft" in path:
            total += 1
        return total
    elif len(path) == max_depth:
        return total
    else:
        for _next in nodes[path[-1]]:
            if _next not in path:  # Avoid cycles
                total = dfs_check(nodes, path + [_next], goal, max_depth, total)
        return total


if __name__ == "__main__":
    # nodes piped to sys.stdin
    nodes = {}
    if not sys.stdin.isatty():
        for line in sys.stdin:
            origin = line.strip().split(":")[0]
            dest = line.strip().split(":")[1].strip().split(" ")
            nodes[origin] = dest
    nodes["out"] = []
    # advent of graphs
    # the graph has a clear structure, "funnel" nodes all over the place, so I'll exploit that fact
    in_degree = {node: 0 for node in nodes.keys()}
    out_degree = {}
    for node in nodes.keys():
        for _next in nodes[node]:
            try:
                in_degree[_next] += 1
            except KeyError:
                pass
        out_degree[node] = len(nodes[node])
    popularity = []
    for node in nodes.keys():
        popularity.append((node, in_degree[node] + out_degree[node]))
    popularity = sorted(popularity, key=lambda x: -x[1])
    # print(popularity)
    funnel_nodes = [node for node, degree in popularity if degree >= 14]
    # print(funnel_nodes)
    # BFS with the funnels + limited DFS to reach the next funnel
    funnel_paths = []
    simple_paths = deque([["svr", dest] for dest in nodes["svr"]])
    while deque:
        try:
            simple_path = simple_paths.popleft()
        except IndexError:
            break
        if dfs(nodes, [simple_path[-1]], "out", 8, 0):
            funnel_paths.append(simple_path + ["out"])
            print(simple_path + ["out"])
        else:
            for funnel in funnel_nodes:
                if funnel not in simple_path:
                    if dfs(nodes, [simple_path[-1]], funnel, 8, 0):
                        simple_paths.append(simple_path + [funnel])
    # Reconstruct paths using funnel paths counting dac and fft
    all_paths = 0
    for funnel_path in funnel_paths:
        funnel_path = funnel_path[1:]  # Ignore srv
        # assumes dac and fft are found in steps 1 and 4 of the funnel paths
        paths = 1
        for i, origin in enumerate(funnel_path[:-1]):
            dest = funnel_path[i + 1]
            if i in [1, 4]:
                total = dfs_check(nodes, [origin], dest, 8, 0)
            else:
                total = dfs(nodes, [origin], dest, 8, 0)
            paths *= total
        all_paths += paths
    print(all_paths)
