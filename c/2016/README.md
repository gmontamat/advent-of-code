# Advent of Code 2016

**Not following advent calendar**. My verdict: This year's problems were slightly harder than 2015's. Day 11 was
noticeably difficult; an approach smarter than DFS is necessary to solve the problem efficiently. My favorite problem
was day 24 by far. The required methods were clear from the problem statement (pathfinding plus path optimization), and
it led me to implement A* and memoization in C and use them in combination with DFS. Another notable problem is day 19:
choosing the appropriate data structure (circular linked lists) makes the solution straightforward. However, C lacks
array slicing, which meant that more than one pointer to the linked list was needed. That said, programming in C feels
great in 2026.

![Calendar](aoc2016.gif)

## Usage

The [Makefile](./Makefile) can help compile and run:

```shell
# Run first day's solution1.c with "example" as input
make run DAY=01 PART=1 IN=example
```
