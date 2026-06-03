# Advent of Code 2016

**Not following advent calendar**. My verdict: This year's problems were slightly harder than 2015.
Day 11 noticeably difficult. An approach smarter than DFS is needed. Favorite problem: day 24 by
far. I knew how to solve it as soon as I read it, but it got me to implement A* and memoization in
C and use them along with DFS. Another notable problem is day 19, with the correct data structure
(circular linked lists) the solution is straightforward. C lacks array/string slicing which would
have made the implementation simpler. Nevertheless, C feels great in 2026.

![Calendar](aoc2016.gif)

## Usage

The [Makefile](./Makefile) can help compile and run:

```shell
# Run first day's solution1.c with "example" as input
make run DAY=01 PART=1 IN=example
```
