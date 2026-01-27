#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# dependencies = [
#     "scipy",
# ]
# ///

import sys

import numpy as np
from scipy.optimize import Bounds, LinearConstraint, milp


def main(problems):
    # min 3 * a + 1 * b
    # st.
    # X <= x_a * a + x_b * b <= X
    # Y <= y_a * a + y_b * b <= Y
    # int a, b
    # lazy me didn't know it's a 2x2 linear system
    tokens = 0
    for problem in problems:
        # print(problem)
        c = np.array([3, 1])
        A = np.array(
            [[problem["x_a"], problem["x_b"]], [problem["y_a"], problem["y_b"]]]
        )
        b = [problem["X"], problem["Y"]]
        constraints = LinearConstraint(A, b, b)
        bounds = Bounds(lb=0, ub=100)
        result = milp(
            c=c, constraints=constraints, bounds=bounds, integrality=np.ones_like(c)
        )
        if result.success:
            tokens += int(result.fun)
    return tokens


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    problems = []
    line_ctr = 0
    with open(file_path, "r") as fin:
        for line in fin:
            if line_ctr % 4 == 0:
                x_a = int(line.strip().split(":")[1].strip().split(",")[0][2:])
                y_a = int(line.strip().split(":")[1].split(",")[1].strip()[2:])
            elif line_ctr % 4 == 1:
                x_b = int(line.strip().split(":")[1].strip().split(",")[0][2:])
                y_b = int(line.strip().split(":")[1].split(",")[1].strip()[2:])
            elif line_ctr % 4 == 2:
                x = int(line.strip().split(",")[0].split("=")[1])
                y = int(line.strip().split(",")[1].split("=")[1])
                problems.append(
                    {"x_a": x_a, "x_b": x_b, "y_a": y_a, "y_b": y_b, "X": x, "Y": y}
                )
            elif line_ctr % 4 == 3:
                assert line.strip() == ""
            line_ctr += 1
    print(main(problems))
