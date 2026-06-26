# Rust Solutions

## Setup

Make sure you have Rust installed: https://rustup.rs/

## Running Solutions

```bash
cd <year>  # eg. 2017

# Run a specific day's solution
cargo run --bin day01 -p aoc2017

# Run with optimizations
cargo run --release --bin day15 -p aoc2018

# Run tests for a specific day
cargo test --bin day01 -p aoc2017
```

## Structure

Each year is a separate Cargo package within a workspace. Solutions are organized as
binary targets in `src/bin/`, with shared utilities in `src/lib.rs`.

Place your puzzle input in `inputs/dayXX.txt` and example inputs in `examples/dayXX.txt`.
