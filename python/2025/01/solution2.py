# --- Part Two ---
#
# You're sure that's the right password, but the door won't open. You knock, but nobody answers. You build a snowman
# while you think.
#
# As you're rolling the snowballs for your snowman, you find another security document that must have fallen into the
# snow:
#
# "Due to newer security protocols, please use password method 0x434C49434B until further notice."
#
# You remember from the training seminar that "method 0x434C49434B" means you're actually supposed to count the number
# of times any click causes the dial to point at 0, regardless of whether it happens during a rotation or at the end of
# one.
#
# Following the same rotations as in the above example, the dial points at zero a few extra times during its rotations:
#
#     The dial starts by pointing at 50.
#     The dial is rotated L68 to point at 82; during this rotation, it points at 0 once.
#     The dial is rotated L30 to point at 52.
#     The dial is rotated R48 to point at 0.
#     The dial is rotated L5 to point at 95.
#     The dial is rotated R60 to point at 55; during this rotation, it points at 0 once.
#     The dial is rotated L55 to point at 0.
#     The dial is rotated L1 to point at 99.
#     The dial is rotated L99 to point at 0.
#     The dial is rotated R14 to point at 14.
#     The dial is rotated L82 to point at 32; during this rotation, it points at 0 once.
#
# In this example, the dial points at 0 three times at the end of a rotation, plus three more times during a rotation.
# So, in this example, the new password would be 6.
#
# Be careful: if the dial were pointing at 50, a single rotation like R1000 would cause the dial to point at 0 ten times
# before returning back to 50!
#
# Using password method 0x434C49434B, what is the password to open the door?

import sys


def update_dial(direction, amount, current):
    if direction == 'L':
        correction = -1 if current == 0 else 0
        # print(f"The dial is rotated {direction}{amount} to point at {(current - amount) % 100}", end="")
        # if abs((current - amount - 1) // 100) + correction > 0:
        #     print(f"; during this rotation, it points at 0 #{abs((current - amount - 1) // 100)} times.")
        # else:
        #     print(".")
        return (current - amount) % 100, abs((current - amount - 1) // 100) + correction
    else:
        # print(f"The dial is rotated {direction}{amount} to point at {(current + amount) % 100}", end="")
        # if abs((current + amount) // 100) > 0:
        #     print(f"; during this rotation, it points at 0 #{abs((current + amount) // 100)} times.")
        # else:
        #     print(".")
        return (current + amount) % 100, abs((current + amount) // 100)


if __name__ == "__main__":
    # rotations piped to sys.stdin or passed as arguments
    rotations = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            rotations.append(line.strip())
    dial = 50
    zeroes = 0
    for rotation in rotations:
        direction = rotation[0]
        amount = int(rotation[1:])
        dial, n_zeroes = update_dial(direction, amount, dial)
        zeroes += n_zeroes
    print(zeroes)
