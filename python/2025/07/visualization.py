# --- Part Two ---
#
# With your analysis of the manifold complete, you begin fixing the teleporter. However, as you open the side of the
# teleporter to replace the broken manifold, you are surprised to discover that it isn't a classical tachyon manifold -
# it's a quantum tachyon manifold.
#
# With a quantum tachyon manifold, only a single tachyon particle is sent through the manifold. A tachyon particle takes
# both the left and right path of each splitter encountered.
#
# Since this is impossible, the manual recommends the many-worlds interpretation of quantum tachyon splitting: each time
# a particle reaches a splitter, it's actually time itself which splits. In one timeline, the particle went left, and in
# the other timeline, the particle went right.
#
# To fix the manifold, what you really need to know is the number of timelines active after a single particle completes
# all of its possible journeys through the manifold.
#
# In the above example, there are many timelines. For instance, there's the timeline where the particle always went
# left:
#
# .......S.......
# .......|.......
# ......|^.......
# ......|........
# .....|^.^......
# .....|.........
# ....|^.^.^.....
# ....|..........
# ...|^.^...^....
# ...|...........
# ..|^.^...^.^...
# ..|............
# .|^...^.....^..
# .|.............
# |^.^.^.^.^...^.
# |..............
#
# Or, there's the timeline where the particle alternated going left and right at each splitter:
#
# .......S.......
# .......|.......
# ......|^.......
# ......|........
# ......^|^......
# .......|.......
# .....^|^.^.....
# ......|........
# ....^.^|..^....
# .......|.......
# ...^.^.|.^.^...
# .......|.......
# ..^...^|....^..
# .......|.......
# .^.^.^|^.^...^.
# ......|........
#
# Or, there's the timeline where the particle ends up at the same point as the alternating timeline, but takes a totally
# different path to get there:
#
# .......S.......
# .......|.......
# ......|^.......
# ......|........
# .....|^.^......
# .....|.........
# ....|^.^.^.....
# ....|..........
# ....^|^...^....
# .....|.........
# ...^.^|..^.^...
# ......|........
# ..^..|^.....^..
# .....|.........
# .^.^.^|^.^...^.
# ......|........
#
# In this example, in total, the particle ends up on 40 different timelines.
#
# Apply the many-worlds interpretation of quantum tachyon splitting to your manifold diagram. In total, how many
# different timelines would a single tachyon particle end up on?

import sys
import numpy as np
from PIL import Image


def draw(all_ways, index):
    """
    Save all_ways matrix as {index}.png using a log10 scale and a blue-to-red color gradient.
    The image is resized to 800x800.
    Normalization is performed row by row after log scaling.
    """
    arr = np.array(all_ways, dtype=np.float64)
    # Apply log10 scale (add 1 to avoid log(0))
    log_arr = np.log10(arr + 1)
    norm = np.zeros_like(log_arr)
    for i, row in enumerate(log_arr):
        row_min = np.min(row)
        row_max = np.max(row)
        if row_max > row_min:
            norm[i] = (row - row_min) / (row_max - row_min)
        else:
            norm[i] = 0.0
    # Map normalized values to blue (low) -> red (high)
    # Blue: (0, 0, 255), Red: (255, 0, 0)
    rgb = np.zeros((arr.shape[0], arr.shape[1], 3), dtype=np.uint8)
    rgb[..., 0] = (norm * 255).astype(np.uint8)         # Red channel increases with value
    rgb[..., 1] = np.zeros_like(norm, dtype=np.uint8)   # Green channel stays 0
    rgb[..., 2] = ((1 - norm) * 255).astype(np.uint8)   # Blue channel decreases with value
    img = Image.fromarray(rgb, mode='RGB')
    img = img.resize((800, 800), resample=Image.NEAREST)
    img.save(f"{index:03d}.png")


if __name__ == "__main__":
    # manifold piped to sys.stdin
    manifold = []
    if not sys.stdin.isatty():
        for line in sys.stdin:
            manifold.append(list(line.strip()))
    # main loop (this is dynamic programming, very similar to Project Euler #67)\
    # 'ways' stores the number of paths you need to take to reach a certain position
    # in a row. We update it row by row. First, let's initialize with 0s except under S:
    ways = [0] * len(manifold[0])
    all_ways = [[0] * len(manifold[0])] * len(manifold)
    for i, value in enumerate(manifold[0]):
        if value == "S":
            ways[i] = 1
    all_ways[0] = ways[:]
    draw(all_ways, 0)
    # Loop starting on 2nd row
    for i_prev, row in enumerate(manifold[1:]):
        old_ways = ways[:]  # copy previous row's ways to transfer to new row
        for j, value in enumerate(row):
            if value == "^":
                ways[j] = 0  # can't reach a split
                if j > 0:
                    ways[j - 1] += old_ways[j]
                if j < len(manifold[0]) - 1:
                    ways[j + 1] += old_ways[j]
        all_ways[i_prev + 1] = ways[:]
        draw(all_ways, i_prev + 1)
        # print(ways, "".join(row))
    print(sum(ways))
