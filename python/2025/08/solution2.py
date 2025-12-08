# --- Part Two ---
#
# The Elves were right; they definitely don't have enough extension cables. You'll need to keep connecting junction
# boxes together until they're all in one large circuit.
#
# Continuing the above example, the first connection which causes all of the junction boxes to form a single circuit is
# between the junction boxes at 216,146,977 and 117,168,530. The Elves need to know how far those junction boxes are
# from the wall so they can pick the right extension cable; multiplying the X coordinates of those two junction boxes
# (216 and 117) produces 25272.
#
# Continue connecting the closest unconnected pairs of junction boxes together until they're all in the same circuit.
# What do you get if you multiply together the X coordinates of the last two junction boxes you need to connect?

import sys


def distance(coord1, coord2):
    return (
        (coord1[0] - coord2[0]) ** 2
        + (coord1[1] - coord2[1]) ** 2
        + (coord1[2] - coord2[2]) ** 2
    )


if __name__ == "__main__":
    # boxes piped to sys.stdin
    boxes = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            boxes.append(tuple(int(n) for n in line.strip().split(",")))
    # print(boxes)
    # main loop
    group_id = {box: i for i, box in enumerate(boxes)}  # track the group_id of each box
    groups = {
        i: [box] for i, box in enumerate(boxes)
    }  # each box in its own group first
    connections = set()
    # store all distances to save time - assumes distances are all unique
    distances = {}
    for i, box1 in enumerate(boxes):
        for j, box2 in enumerate(boxes):
            if i >= j:
                continue
            else:
                distances[distance(box1, box2)] = (i, j)
    sorted_distances = sorted(distances.keys())
    # connect one by one
    while True:
        pair = distances[sorted_distances[len(connections)]]
        connections.add(pair)
        # Connect the groups
        i, j = pair
        box1, box2 = boxes[i], boxes[j]
        new_group = min(group_id[box1], group_id[box2])
        old_group = max(group_id[box1], group_id[box2])
        # Merge old_group into new_group
        if new_group == old_group:
            continue  # same group, continue
        # print(box1, box2)
        # merge groups
        groups[new_group].extend(groups[old_group])
        del groups[old_group]
        if len(groups) == 1:
            print(box1[0] * box2[0])
            break
        for box in groups[new_group]:
            group_id[box] = new_group
