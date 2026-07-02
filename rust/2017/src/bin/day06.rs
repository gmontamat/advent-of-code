use std::collections::{HashMap, HashSet};

use aoc2017::read_input;

fn solve_part1(memory: Vec<String>) -> i32 {
    let mut banks: Vec<i32> = memory
        .into_iter()
        .map(|s| s.parse::<i32>().unwrap())
        .collect();
    let len = banks.len();
    let mut dict: HashSet<Vec<i32>>= HashSet::new();  // keep track of known arrangements
    let mut cycles: i32 = 0;
    loop {
        if dict.contains(&banks.clone()) {
            return cycles;
        }
        dict.insert(banks.clone());  // add arrangement to known set
        let max_index = banks
            .iter()
            .enumerate()
            .max_by_key(|(index, value)| (*value, std::cmp::Reverse(*index)))
            .map(|(index, _)| index)
            .unwrap();
        let mut blocks = banks[max_index];
        banks[max_index] = 0;  // empty max bank and then spread memory
        let mut index = (max_index + 1) % len;
        while blocks > 0 {
            banks[index] += 1;
            blocks -= 1;
            index = (index + 1) % len;
        }
        cycles += 1;
    }
}

fn solve_part2(memory: Vec<String>) -> i32 {
    let mut banks: Vec<i32> = memory
        .into_iter()
        .map(|s| s.parse::<i32>().unwrap())
        .collect();
    let len = banks.len();
    let mut dict: HashMap<Vec<i32>, i32>= HashMap::new();  // keep track of known arrangements
    let mut cycles: i32 = 0;
    loop {
        if dict.contains_key(&banks.clone()) {
            return cycles - dict.get(&banks).unwrap();
        }
        dict.insert(banks.clone(), cycles);  // add arrangement to known set
        let max_index = banks
            .iter()
            .enumerate()
            .max_by_key(|(index, value)| (*value, std::cmp::Reverse(*index)))
            .map(|(index, _)| index)
            .unwrap();
        let mut blocks = banks[max_index];
        banks[max_index] = 0;  // empty max bank and then spread memory
        let mut index = (max_index + 1) % len;
        while blocks > 0 {
            banks[index] += 1;
            blocks -= 1;
            index = (index + 1) % len;
        }
        cycles += 1;
    }
}

fn main() {
    let memory: Vec<String> = read_input(6)
        .split_whitespace()
        .map(|s| s.to_string())
        .collect();
    println!("Part 1: {}", solve_part1(memory.clone()));
    println!("Part 2: {}", solve_part2(memory));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        let text: String = String::from("0 2 7 0");
        let memory: Vec<String> = text.split_whitespace()
            .map(|s| s.to_string())
            .collect();
        assert_eq!(solve_part1(memory), 5);
    }

    #[test]
    fn test_part2() {
        let text: String = String::from("0 2 7 0");
        let memory: Vec<String> = text.split_whitespace()
            .map(|s| s.to_string())
            .collect();
        assert_eq!(solve_part2(memory), 4);
    }
}
