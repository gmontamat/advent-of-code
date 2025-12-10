# --- Part Two ---

# All of the machines are starting to come online! Now, it's time to worry about the joltage requirements.

# Each machine needs to be configured to exactly the specified joltage levels to function properly. Below the buttons on
# each machine is a big lever that you can use to switch the buttons from configuring the indicator lights to increasing
# the joltage levels. (Ignore the indicator light diagrams.)

# The machines each have a set of numeric counters tracking its joltage levels, one counter per joltage requirement. The
# counters are all initially set to zero.

# So, joltage requirements like {3,5,4,7} mean that the machine has four counters which are initially 0 and that the
# goal is to simultaneously configure the first counter to be 3, the second counter to be 5, the third to be 4, and the
# fourth to be 7.

# The button wiring schematics are still relevant: in this new joltage configuration mode, each button now indicates
# which counters it affects, where 0 means the first counter, 1 means the second counter, and so on. When you push a
# button, each listed counter is increased by 1.

# So, a button wiring schematic like (1,3) means that each time you push that button, the second and fourth counters
# would each increase by 1. If the current joltage levels were {0,1,2,3}, pushing the button would change them to be
# {0,2,2,4}.

# You can push each button as many times as you like. However, your finger is getting sore from all the button pushing,
# and so you will need to determine the fewest total presses required to correctly configure each machine's joltage
# level counters to match the specified joltage requirements.

# Consider again the example from before:

# [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
# [...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
# [.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}

# Configuring the first machine's counters requires a minimum of 10 button presses. One way to do this is by pressing
# (3) once, (1,3) three times, (2,3) three times, (0,2) once, and (0,1) twice.

# Configuring the second machine's counters requires a minimum of 12 button presses. One way to do this is by pressing
# (0,2,3,4) twice, (2,3) five times, and (0,1,2) five times.

# Configuring the third machine's counters requires a minimum of 11 button presses. One way to do this is by pressing
# (0,1,2,3,4) five times, (0,1,2,4,5) five times, and (1,2) once.

# So, the fewest button presses required to correctly configure the joltage level counters on all of the machines is
# 10 + 12 + 11 = 33.

# Analyze each machine's joltage requirements and button wiring schematics. What is the fewest button presses required
# to correctly configure the joltage level counters on all of the machines?


import re
import sys

from scipy.optimize import milp, LinearConstraint, Bounds
import numpy as np


if __name__ == "__main__":
    # coordinates piped to sys.stdin
    machines = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            machines.append(line.strip())
    # Get elements
    all_buttons = []
    all_joltages = []
    for machine in machines:
        all_buttons.append(
            [[int(x) for x in t.split(",")] for t in re.findall(r"\((.*?)\)", machine)]
        )
        all_joltages.append(
            [[int(x) for x in t.split(",")] for t in re.findall(r"\{(.*?)\}", machine)][0]
        )
    # main loop - advent of discrete optimization
    # Used Mixed-integer linear programming
    all_solutions = []
    for buttons, joltages in zip(all_buttons, all_joltages):
        # Number of variables (# buttons)
        n_vars = len(buttons)
        # Objective: minimize sum of all variables (button presses)
        c = np.ones(n_vars)
        # Build constraint matrix A
        # Each row represents one constraint equation
        # Each column represents one button
        n_constraints = len(joltages)
        A = np.zeros((n_constraints, n_vars))
        for button_idx, constraint_indices in enumerate(buttons):
            for constraint_idx in constraint_indices:
                A[constraint_idx, button_idx] = 1
        # Create equality constraints (lb = ub = joltages)
        constraints = LinearConstraint(A, lb=joltages, ub=joltages)
        # Variable bounds (non-negative integers)
        bounds = Bounds(lb=0, ub=np.inf)
        # Solve the integer linear programming problem
        # integrality=1 means all variables must be integers
        result = milp(c=c, constraints=constraints, bounds=bounds, 
                      integrality=np.ones(n_vars))
        assert(result.success)
        all_solutions.append(result.fun)
    print(int(sum(all_solutions)))
