# --- Day 12: Christmas Tree Farm ---

# You're almost out of time, but there can't be much left to decorate. Although there are no stairs, elevators,
# escalators, tunnels, chutes, teleporters, firepoles, or conduits here that would take you deeper into the North Pole
# base, there is a ventilation duct. You jump in.

# After bumping around for a few minutes, you emerge into a large, well-lit cavern full of Christmas trees!

# There are a few Elves here frantically decorating before the deadline. They think they'll be able to finish most of
# the work, but the one thing they're worried about is the presents for all the young Elves that live here at the North
# Pole. It's an ancient tradition to put the presents under the trees, but the Elves are worried they won't fit.

# The presents come in a few standard but very weird shapes. The shapes and the regions into which they need to fit are
# all measured in standard units. To be aesthetically pleasing, the presents need to be placed into the regions in a way
# that follows a standardized two-dimensional unit grid; you also can't stack presents.

# As always, the Elves have a summary of the situation (your puzzle input) for you. First, it contains a list of the
# presents' shapes. Second, it contains the size of the region under each tree and a list of the number of presents of
# each shape that need to fit into that region. For example:

# 0:
# ###
# ##.
# ##.

# 1:
# ###
# ##.
# .##

# 2:
# .##
# ###
# ##.

# 3:
# ##.
# ###
# ##.

# 4:
# ###
# #..
# ###

# 5:
# ###
# .#.
# ###

# 4x4: 0 0 0 0 2 0
# 12x5: 1 0 1 0 2 2
# 12x5: 1 0 1 0 3 2

# The first section lists the standard present shapes. For convenience, each shape starts with its index and a colon;
# then, the shape is displayed visually, where # is part of the shape and . is not.

# The second section lists the regions under the trees. Each line starts with the width and length of the region; 12x5
# means the region is 12 units wide and 5 units long. The rest of the line describes the presents that need to fit into
# that region by listing the quantity of each shape of present; 1 0 1 0 3 2 means you need to fit one present with shape
# index 0, no presents with shape index 1, one present with shape index 2, no presents with shape index 3, three
# presents with shape index 4, and two presents with shape index 5.

# Presents can be rotated and flipped as necessary to make them fit in the available space, but they have to always be
# placed perfectly on the grid. Shapes can't overlap (that is, the # part from two different presents can't go in the
# same place on the grid), but they can fit together (that is, the . part in a present's shape's diagram does not block
# another present from occupying that space on the grid).

# The Elves need to know how many of the regions can fit the presents listed. In the above example, there are six unique
# present shapes and three regions that need checking.

# The first region is 4x4:

# ....
# ....
# ....
# ....

# In it, you need to determine whether you could fit two presents that have shape index 4:

# ###
# #..
# ###

# After some experimentation, it turns out that you can fit both presents in this region. Here is one way to do it,
# using A to represent one present and B to represent the other:

# AAA.
# ABAB
# ABAB
# .BBB

# The second region, 12x5: 1 0 1 0 2 2, is 12 units wide and 5 units long. In that region, you need to try to fit one
# present with shape index 0, one present with shape index 2, two presents with shape index 4, and two presents with
# shape index 5.

# It turns out that these presents can all fit in this region. Here is one way to do it, again using different capital
# letters to represent all the required presents:

# ....AAAFFE.E
# .BBBAAFFFEEE
# DDDBAAFFCECE
# DBBB....CCC.
# DDD.....C.C.

# The third region, 12x5: 1 0 1 0 3 2, is the same size as the previous region; the only difference is that this region
# needs to fit one additional present with shape index 4. Unfortunately, no matter how hard you try, there is no way to
# fit all of the presents into this region.

# So, in this example, 2 regions can fit all of their listed presents.

# Consider the regions beneath each tree and the presents the Elves would like to fit into each of them. How many of the
# regions can fit all of the presents listed?


import sys

import cpmpy as cp
import numpy as np


def shape_to_np(piece_strs):
    # Converts list of strings to boolean numpy array, True if "#" or else False
    return np.array([[c == "#" for c in row] for row in piece_strs])


def all_unique_rotations(shape):
    # Returns all unique rotations
    rotations = []
    for k in range(4):
        rot = np.rot90(shape, k)
        if not any(np.array_equal(rot, r) for r in rotations):
            rotations.append(rot)
    return rotations


def build_piece_rotations(piece_dict):
    # For each piece type, get all unique rotations
    rots = []
    for i in range(len(piece_dict)):
        base = shape_to_np(piece_dict[i])
        unique_rots = all_unique_rotations(base)
        rots.append(unique_rots)
    return rots


def solve_packing(grid_w, grid_h, piece_counts, piece_dict):
    grid_shape = (grid_h, grid_w)
    piece_rotations = build_piece_rotations(piece_dict)

    # For each instance of a piece to be used, append its rotations
    all_pieces_shapes = []
    for pid, count in enumerate(piece_counts):
        for _ in range(count):
            all_pieces_shapes.append(piece_rotations[pid])

    # Generate a mask of all possible placements of each piece (and its rotations)
    placement_masks = []
    for piece_rotations in all_pieces_shapes:
        masks = []
        for shape in piece_rotations:
            sh, sw = shape.shape
            for i in range(grid_h - sh + 1):
                for j in range(grid_w - sw + 1):
                    mask = np.zeros(grid_shape, dtype=bool)
                    mask[i : i + sh, j : j + sw] = shape
                    masks.append(mask)
        placement_masks.append(masks)

    # For each mask, create a placement variable (True if mask is used, else False)
    placement_vars = []
    for masks in placement_masks:
        placement = cp.BoolVar(shape=len(masks))
        placement_vars.append(placement)

    # Define the constraint model
    model = cp.Model()

    # Constraint: each piece instance placed at exactly one of its locations
    for placement in placement_vars:
        if len(placement) == 0:
            # The shape doesn't fit the grid at all, so infeasible!
            # All pieces fit in a 3x3 grid, so this is unnecessary
            return False
        else:
            model += cp.sum(placement) == 1  # Use only 1 mask for each shape

    # Constraint: each grid cell covered at most once
    for i in range(grid_h):
        for j in range(grid_w):
            cell_coverage = []
            for piece_idx in range(len(all_pieces_shapes)):
                for placement_idx, mask in enumerate(placement_masks[piece_idx]):
                    if mask[i, j]:
                        cell_coverage.append(placement_vars[piece_idx][placement_idx])
            model += (
                cp.sum(cell_coverage) <= 1
            )  # if we wanted full grid coverage use == 1

    # Solve
    if model.solve():
        return True
    else:
        return False


if __name__ == "__main__":
    # nodes piped to sys.stdin
    piece_dict = {}
    grids = []
    load_shape = False
    if not sys.stdin.isatty():
        for line in sys.stdin:
            if line.strip() == "" and load_shape:
                piece_dict[shape_name] = shape
                load_shape = False
            if ":" in line.strip() and "x" not in line.strip():
                load_shape = True
                shape = []
                shape_name = int(line.split(":")[0])
            elif ":" in line.strip() and "x" in line.strip():
                grid_size = line.strip().split(":")[0]
                width = int(grid_size.split("x")[0])
                height = int(grid_size.split("x")[1])
                grid_shapes = [
                    int(c) for c in line.strip().split(":")[1].strip().split(" ")
                ]
                grids.append((width, height, grid_shapes))
            elif load_shape:
                shape.append(line.strip())
    # print(piece_dict)
    # print(grids)
    # advent of constraint programming - CPMpy with ortools to the rescue
    solvable = 0
    for grid in grids:
        width, height, count = grid
        # Before solving, check if the solution (or lack of) is trivial
        area = 0
        solid_area = 0
        for pid, n in enumerate(count):
            piece_area = 0
            solid_piece_area = 0
            for row in piece_dict[pid]:
                for c in row:
                    solid_piece_area += 1
                    if c == "#":
                        piece_area += 1
            area += piece_area * n
            solid_area += solid_piece_area * n
        if area > width * height:
            # Area of pieces > area of grid, we already know it can't be solved
            print(f"{grid} is trivially NOT solvable.")
        elif solid_area <= width * height:
            # Trivially solvable, there's plenty of space even if the pieces were 3x3 solids
            solvable += 1
            print(f"{grid} is trivially solvable.")
        else:
            if solve_packing(width, height, count, piece_dict):
                print(f"{grid} is solvable.")
                solvable += 1
            else:
                print(f"{grid} is NOT solvable.")
    print(solvable)
