# Rust Solutions

## Setup

Make sure you have Rust installed: https://rustup.rs/

## Running Solutions

```bash
# Run a specific day's solution
cargo run  -p aoc2017 --bin day01

# Run with optimizations
cargo run --release  -p aoc2018 --bin day15

# Run tests for a specific day
cargo test -p aoc2017 --bin day01
```

## Structure

Each year is a separate Cargo package within a workspace. Solutions are organized as
binary targets in `src/bin/`, with shared utilities in `src/lib.rs`.

Place your puzzle input in `inputs/dayXX.txt` and example inputs in `examples/dayXX.txt`.
