use aoc2017::read_inputs;

fn solve_part1(offsets: Vec<String>) -> i32 {
    let mut instructions: Vec<i32> = offsets
        .into_iter()
        .map(|s| s.parse::<i32>().unwrap())
        .collect();
    let mut steps: i32 = 0;
    let len: i32 = instructions.len().try_into().unwrap();
    let mut ptr: i32 = 0;  // points to current instruction
    loop {
        if ptr < 0 || ptr >= len {
            return steps;
        }
        let offset: i32 = instructions[usize::try_from(ptr).unwrap()];
        instructions[usize::try_from(ptr).unwrap()] += 1;
        ptr += offset;
        steps += 1
    }
}

fn solve_part2(offsets: Vec<String>) -> i32 {
    let mut instructions: Vec<i32> = offsets
        .into_iter()
        .map(|s| s.parse::<i32>().unwrap())
        .collect();
    let mut steps: i32 = 0;
    let len: i32 = instructions.len().try_into().unwrap();
    let mut ptr: i32 = 0;  // points to current instruction
    loop {
        if ptr < 0 || ptr >= len {
            return steps;
        }
        let offset: i32 = instructions[usize::try_from(ptr).unwrap()];
        if instructions[usize::try_from(ptr).unwrap()] > 2 {
            instructions[usize::try_from(ptr).unwrap()] -= 1;
        } else {
            instructions[usize::try_from(ptr).unwrap()] += 1;
        }
        ptr += offset;
        steps += 1
    }
}

fn main() {
    let offsets: Vec<String> = read_inputs(5);
    println!("Part 1: {}", solve_part1(offsets.clone()));
    println!("Part 2: {}", solve_part2(offsets));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples;

use super::*;

    #[test]
    fn test_part1() {
        let offsets: Vec<String> = read_examples(5);
        assert_eq!(solve_part1(offsets), 5);
    }

    #[test]
    fn test_part2() {
        let offsets: Vec<String> = read_examples(5);
        assert_eq!(solve_part2(offsets), 10);
    }
}
