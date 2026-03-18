#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "networkx",
# ]
# ///

import sys

import networkx as nx


def to_decimal(variable, output_map):
    nodes = [node for node in output_map.keys() if node[0] == variable]
    power = len(nodes) - 1
    decimal = 0
    for node in sorted(nodes, reverse=True):
        if output_map[node]:
            decimal += 2**power
        power -= 1
    return decimal


def main(output_map, operations):
    # Build DAG with operations
    dag = nx.DiGraph()
    for output, operation in operations.items():
        input1 = operation["input1"]
        input2 = operation["input2"]
        dag.add_edge(input1, output)
        dag.add_edge(input2, output)
    # Solve precedence using topological sorting
    top_sort = list(nx.topological_sort(dag))
    for node in top_sort:
        if node not in output_map:
            input1 = output_map[operations[node]["input1"]]
            input2 = output_map[operations[node]["input2"]]
            operand = operations[node]["operand"]
            if operand == "AND":
                output_map[node] = input1 & input2
            elif operand == "OR":
                output_map[node] = input1 | input2
            elif operand == "XOR":
                output_map[node] = input1 ^ input2
    return to_decimal("z", output_map)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    output_map = {}
    operations = {}
    loading_inputs = True
    with open(file_path, "r") as fin:
        for line in fin:
            if not line.strip():
                loading_inputs = False
                continue
            if loading_inputs:
                name = line.strip().split(":")[0]
                value = line.strip().split(" ")[-1]
                output_map[name] = bool(int(value))
            else:
                output = line.strip().split(" -> ")[-1]
                input1 = line.strip().split(" ")[0]
                input2 = line.strip().split(" ")[2]
                operand = line.strip().split(" ")[1]
                operations[output] = {
                    "input1": input1,
                    "input2": input2,
                    "operand": operand,
                }
    print(main(output_map, operations))
