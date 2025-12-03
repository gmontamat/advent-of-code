# --- Part Two ---
#
# The escalator doesn't move. The Elf explains that it probably needs more joltage to overcome the static friction of
# the system and hits the big red "joltage limit safety override" button. You lose count of the number of times she
# needs to confirm "yes, I'm sure" and decorate the lobby a bit while you wait.
#
# Now, you need to make the largest joltage by turning on exactly twelve batteries within each bank.
#
# The joltage output for the bank is still the number formed by the digits of the batteries you've turned on; the only
# difference is that now there will be 12 digits in each bank's joltage output instead of two.
#
# Consider again the example from before:
#
# 987654321111111
# 811111111111119
# 234234234234278
# 818181911112111
#
# Now, the joltages are much larger:
#
#     In 987654321111111, the largest joltage can be found by turning on everything except some 1s at the end to produce 987654321111.
#     In the digit sequence 811111111111119, the largest joltage can be found by turning on everything except some 1s, producing 811111111119.
#     In 234234234234278, the largest joltage can be found by turning on everything except a 2 battery, a 3 battery, and another 2 battery near the start to produce 434234234278.
#     In 818181911112111, the joltage 888911112111 is produced by turning on everything except some 1s near the front.
#
# The total output joltage is now much larger: 987654321111 + 811111111119 + 434234234278 + 888911112111 = 3121910778619.
#
# What is the new total output joltage?

import sys

if __name__ == "__main__":
    # battery banks piped to sys.stdin
    batteries = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            batteries.append(line.strip())
    # main loop
    jolts = []
    for bank in batteries:
        positions = []
        start_idx = 0
        # Note: we have to be smarter than nested for-loops here!
        # For each digit of the 12-digit number, select largest digit closer to the front of the bank
        # ... I forgot how to prove correctness for this greedy approach, sorry Algorithms professor!
        for i in range(-11, 1):
            digit = max(bank[start_idx:len(bank) + i])
            idx = bank.index(digit, start_idx, len(bank) + i)
            positions.append(idx)
            start_idx = idx + 1
        max_joltage = int("".join(bank[i] for i in positions))
        # print(max_joltage)
        jolts.append(max_joltage)
    print(sum(jolts))
