#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "networkx",
# ]
# ///

import sys
import json
import random

import networkx as nx


def to_decimal(variable, output_map):
    nodes = [node for node in output_map.keys() if node[0] == variable]
    power = len(nodes) - 1
    decimal = 0
    for node in sorted(nodes, reverse=True):
        if output_map[node]:
            decimal += 2 ** power
        power -= 1
    return decimal


def to_binary(decimal, prefix="z"):
    result = {}
    i = 0
    while i < 45:
        result[f"{prefix}{i:02d}"] = True if decimal % 2 == 1 else False
        decimal = decimal // 2
        i += 1
    return result

def to_string(binary, prefix="z"):
    return "".join(["1" if binary[f"{prefix}{i:02d}"] else "0" for i in range(45)])


def build_dag(operations):
    # Build DAG with operations
    dag = nx.DiGraph()
    for output, operation in operations.items():
        input1 = operation["input1"]
        input2 = operation["input2"]
        dag.add_edge(input1, output)
        dag.add_edge(input2, output)
    # Solve precedence using topological sorting
    return list(nx.topological_sort(dag))


def run(output_map, operations, top_sort):
    output_map = json.loads(json.dumps(output_map))  # copy map to not affect it
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
    return {k: v for k, v in output_map.items() if k[0] == "z"}


def main(output_map, operations, n=100):
    """
    'Montecarlo Simulation' approach:
      - Simulate N xs and ys (and compute correct sum z)
      - For all pairs of cables
      - Compute total bits incorrect (obtained z vs correct z)
      - Select pair which minimizes incorrect bits
      - Repeat
    Required improvement: filter the pairs of gates to be swapped
    """
    # Create N different inputs
    output_maps = []
    correct_zs = []
    for _ in range(100):
        new_map = {}
        for j in range(45):
            new_map[f"x{j:02d}"] = random.choice([True, False])
            new_map[f"y{j:02d}"] = random.choice([True, False])
        # new_map[f"x00"] = True       # x == 1
        # new_map[f"y{i:02d}"] = True  # y == 1, 2, 4, 8, 16, 32, 64, ...
        output_maps.append(new_map)
        correct_zs.append(to_decimal("x", new_map) + to_decimal("y", new_map))
    # Find which swaps I should make
    # all_swaps =[]
    # top_sort = build_dag(operations)
    # for i, (output_map, correct_z) in enumerate(zip(output_maps, correct_zs)):
    #     z = run(output_map, operations, top_sort)
    #     if to_decimal("z", z) != correct_z:
    #         print(i)
    #         print(correct_z, to_decimal("z", z))
    #         possible_swaps = [f"z{i:02d}"]
    #         idx = 0
    #         while idx < len(possible_swaps):
    #             if possible_swaps[idx] in operations:
    #                 if operations[possible_swaps[idx]]["input1"] not in possible_swaps:
    #                     possible_swaps.append(operations[possible_swaps[idx]]["input1"])
    #                 if operations[possible_swaps[idx]]["input2"] not in possible_swaps:
    #                     possible_swaps.append(operations[possible_swaps[idx]]["input2"])
    #             idx += 1
    #         print(possible_swaps)
    #         possible_swaps = [node for node in possible_swaps if node in operations]
    #         all_swaps.append(possible_swaps[:32])
    swapped = []
    # for swap in all_swaps:
    for _ in range(4):
        # For each pair of cables
        minimum_errors = float("inf")
        best_pair = None
        for node1 in operations.keys():
            for node2 in operations.keys():
                if node1 == node2:
                    continue
                # if node1 in swapped or node2 in swapped:
                #     continue
                cumulative_errors = 0
                # Swap output cables
                # fixed_operations = copy.deepcopy(operations)
                swapped_operations = json.loads(json.dumps(operations))
                swapped_operations[node1], swapped_operations[node2] = \
                    swapped_operations[node2], swapped_operations[node1]
                try:
                    top_sort = build_dag(swapped_operations)
                except nx.exception.NetworkXUnfeasible:
                    # we introduced a cycle, so we skip this swap
                    continue
                for output_map, correct_z in zip(output_maps, correct_zs):
                    z = run(output_map, swapped_operations, top_sort)
                    if to_decimal("z", z) != correct_z:
                        valid_z = to_binary(correct_z)
                        cumulative_errors += sum([
                            1 if z[f"z{i:02d}"] != valid_z[f"z{i:02d}"] else 0
                            for i in range(45)
                        ])
                # print(node1, node2, cumulative_errors, minimum_errors)
                # Check if minimum
                if cumulative_errors < minimum_errors:
                    minimum_errors = cumulative_errors
                    best_pair = (node1, node2)
        swapped.append(best_pair[0])
        swapped.append(best_pair[1])
        # print(best_pair, minimum_errors)
        operations[best_pair[0]], operations[best_pair[1]] = \
            operations[best_pair[1]], operations[best_pair[0]]
    return ",".join(sorted(swapped))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
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
                    "operand": operand
                }
    print(main(output_map, operations))
