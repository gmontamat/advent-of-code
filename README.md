# Advent of Code

This repository contains my solutions to Advent of Code puzzles. I use it to practice my coding skills and to explore
new programming languages.

## Repository Structure

- Each programming language has its own top-level directory.
- Inside each language directory, there is a subdirectory for each year (e.g., `2025/`, `2024/`).
- Within each year’s folder, each day's puzzle is organized into its own subfolder, named with a two-digit day number
  (`01/`, `02/`, etc.).
- Solution files for each day are placed inside their corresponding day subfolder.

### For example

```
<language>/
  └── <year>/
        ├── 01/
        │    ├── solution.<ext>
        │    └── example
        ├── 02/
        │    └── solution.<ext>
        └── ...
```

Replace `<language>` with the programming language (e.g., `python`, `rust`), `<year>` with the contest year
(e.g., 2023), and `<ext>` with the appropriate file extension. Input should be provided to the solution via standard
input, but example inputs are provided in each day's folder.

### Usage

Run a solution by piping the input into the solution file. For example:

```shell
cat input | python solution.py
```
