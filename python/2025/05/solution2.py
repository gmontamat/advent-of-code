# --- Part Two ---
#
# The Elves start bringing their spoiled inventory to the trash chute at the back of the kitchen.
#
# So that they can stop bugging you when they get new inventory, the Elves would like to know all of the IDs that the
# fresh ingredient ID ranges consider to be fresh. An ingredient ID is still considered fresh if it is in any range.
#
# Now, the second section of the database (the available ingredient IDs) is irrelevant. Here are the fresh ingredient ID
# ranges from the above example:
#
# 3-5
# 10-14
# 16-20
# 12-18
#
# The ingredient IDs that these ranges consider to be fresh are 3, 4, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, and 20.
# So, in this example, the fresh ingredient ID ranges consider a total of 14 ingredient IDs to be fresh.
#
# Process the database file again. How many ingredient IDs are considered to be fresh according to the fresh ingredient
# ID ranges?

import sys

if __name__ == "__main__":
    # database piped to sys.stdin
    ranges = []
    ingredients = []
    input_ranges = True
    if not sys.stdin.isatty():
        for line in sys.stdin:
            if line.strip() == "":
                input_ranges = False
                continue
            if input_ranges:
                # parse ranges
                ranges.append(tuple(int(n) for n in line.strip().split("-")))
            else:
                # parse available ingredient IDs
                ingredients.append(int(line.strip()))
    # main loop - ranges overlap - adjust:
    ranges.sort(key=lambda x: x[0])  # sort by min_id of range
    # merge overlaps
    overlapped_ranges = [ranges[0]]
    for _range in ranges[1:]:
        if _range[0] <= overlapped_ranges[-1][1]:
            # merge overlapping ranges
            overlapped_ranges[-1] = (overlapped_ranges[-1][0], max(_range[1], overlapped_ranges[-1][1]))
        else:
            overlapped_ranges.append(_range)
    # Use overlapped ranges to quickly get totals
    all_ids = 0
    for min_id, max_id in overlapped_ranges:
        all_ids += max_id - min_id + 1
    print(all_ids)
