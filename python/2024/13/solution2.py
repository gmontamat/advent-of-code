#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def main(problems):
    # min 3 * a + 1 * b
    # st.
    #   x_a * a + x_b * b = X
    #   y_a * a + y_b * b = Y
    # int a, b
    # note the problem is technically a 2x2 system with 2 unknowns
    # thus it's a matter of solving the linear system and checking
    # if the solutions are integers
    tokens = 0
    for problem in problems:
        # print(problem)
        # Cramer's rule
        x_a = problem['x_a']
        x_b = problem['x_b']
        y_a = problem['y_a']
        y_b = problem['y_b']
        X = problem['X']
        Y = problem['Y']
        determinant = x_a * y_b - y_a * x_b
        if determinant == 0:
            # No unique solution
            print("foo")
        a = (X * y_b - Y * x_b) // determinant
        b = (x_a * Y - y_a * X) // determinant
        if a * x_a + b * x_b == X and a * y_a + b * y_b == Y:
            tokens += 3 * a + b
    return tokens


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
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
                x = int(line.strip().split(",")[0].split("=")[1]) + 10000000000000
                y = int(line.strip().split(",")[1].split("=")[1]) + 10000000000000
                problems.append(
                    {"x_a": x_a, "x_b": x_b, "y_a": y_a, "y_b": y_b, "X": x, "Y": y}
                )
            elif line_ctr % 4 == 3:
                assert line.strip() == ""
            line_ctr += 1
    print(main(problems))
