# --- Part Two ---
#
# The big cephalopods come back to check on how things are going. When they see that your grand total doesn't match the
# one expected by the worksheet, they realize they forgot to explain how to read cephalopod math.
#
# Cephalopod math is written right-to-left in columns. Each number is given in its own column, with the most significant
# digit at the top and the least significant digit at the bottom. (Problems are still separated with a column consisting
# only of spaces, and the symbol at the bottom of the problem is still the operator to use.)
#
# Here's the example worksheet again:
#
# 123 328  51 64
#  45 64  387 23
#   6 98  215 314
# *   +   *   +
#
# Reading the problems right-to-left one column at a time, the problems are now quite different:
#
#     The rightmost problem is 4 + 431 + 623 = 1058
#     The second problem from the right is 175 * 581 * 32 = 3253600
#     The third problem from the right is 8 + 248 + 369 = 625
#     Finally, the leftmost problem is 356 * 24 * 1 = 8544
#
# Now, the grand total is 1058 + 3253600 + 625 + 8544 = 3263827.
#
# Solve the problems on the math worksheet again. What is the grand total found by adding together all of the answers to
# the individual problems?

import sys

if __name__ == "__main__":
    # worksheet piped to sys.stdin
    worksheet = []
    operators = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            worksheet.append(line)
    operators = worksheet[-1]
    # Add padding to the operators string (for the last set of numbers)
    operators = operators.rstrip("\n")
    max_len = max(len(line) for line in worksheet)
    operators += " " * (max_len - len(operators))
    operators += "!"  # Not an operator but will trigger compute for the last set
    grand_total = 0
    # Track the operator to be used and its index
    operator = operators[0]
    idx = 0
    # Loop column by column of each string
    for i, cur_op in enumerate(operators[1:]):
        if cur_op != " ":  # Time to build the numbers and compute
            # print(i, cur_op, operator, idx)
            # Use idx to build numbers, column by column
            numbers = [""] * (i - idx)
            for col in range(i - 1, idx - 1, -1):
                for row in worksheet[:-1]:
                    numbers[col % (i - idx)] += row[col].strip()
            if operator == "+":
                # print(numbers)
                grand_total += sum(int(n) for n in numbers)
            elif operator == "*":
                # print(numbers)
                prod = 1
                for n in numbers:
                    prod *= int(n)
                grand_total += prod
            # Update operator and its index
            idx = i + 1
            operator = cur_op
    print(grand_total)
