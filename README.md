# Advent of Code

This repository contains my solutions to [Advent of Code](https://adventofcode.com) puzzles. I solve them to:

1. Practice coding skills without using LLMs (this is not work, I even turn off AI-assisted autocompletion)
2. Sharpen problem-solving skills, keeping my brain at work
3. Explore or revisit a particular programming language

> The current generation of AI has quickly exposed that most people have no clue how learning works. Learning
> styles are a myth. You may have a preference in how you consume information, but you learn by doing.
> Learning happens in the struggle. You must wrestle with a concept. You must be confused at times. It is not
> optional. If you rely on an LLM to write most of your code, code that you do not have reps writing
> yourself, you will not learn. You will not gain a deeper understanding.
~ [brianmeeker.me - Have a Coherent AI Policy](https://brianmeeker.me/2026/05/14/have-a-coherent-ai-policy/)

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
        ├── README.md
        ├── 01/
        │    ├── solution1.<ext>
        │    ├── solution2.<ext>
        │    └── example
        ├── 02/
        │    ├── solution1.<ext>
        │    └── ...
        └── ...
```

Replace `<language>` with the programming language (e.g., `python`, `rust`), `<year>` with the contest year
(e.g., `2023`), and `<ext>` with the appropriate file extension. Input should be provided to the solution, but example
inputs are provided in each day's folder.

### Usage

Follow the README in each `<language>/<year>` directory for language-specific instructions.
