use std::collections::HashMap;

use aoc2017::read_inputs;

fn solve_part1(instructions: Vec<String>) -> i32 {
    let mut registers: HashMap<String, i32> = HashMap::new();
    // Run program (we initialize registers to 0 when not found)
    // <reg1> <inc or dec> <n: i32> if <reg2> <operator> <m: i32>
    for instruction in instructions {
        let parts: Vec<&str> = instruction.split_whitespace().collect();
        // evaluate condition
        let reg2 = parts[4].to_string();
        let operator = parts[5];
        let m: i32 = parts[6].parse().unwrap();
        let mut condition: bool = false;
        if operator == ">" {
            if *registers.entry(reg2).or_insert(0) > m {
                condition = true;
            }
        } else if operator == "<" {
            if *registers.entry(reg2).or_insert(0) < m {
                condition = true;
            }
        } else if operator == ">=" {
            if *registers.entry(reg2).or_insert(0) >= m {
                condition = true;
            }
        } else if operator == "<=" {
            if *registers.entry(reg2).or_insert(0) <= m {
                condition = true;
            }
        } else if operator == "==" {
            if *registers.entry(reg2).or_insert(0) == m {
                condition = true;
            }
        } else if operator == "!=" {
            if *registers.entry(reg2).or_insert(0) != m {
                condition = true;
            }
        }
        // execute action
        if !condition {
            continue;
        }
        let reg1 = parts[0].to_string();
        let operation = parts[1];
        let n: i32 = parts[2].parse().unwrap();
        if operation == "inc" {
            *registers.entry(reg1).or_insert(0) += n;
        } else if  operation == "dec" {
            *registers.entry(reg1).or_insert(0) -= n;
        }
    }
    registers.values().max().unwrap().clone()
}

fn solve_part2(instructions: Vec<String>) -> i32 {
    let mut registers: HashMap<String, i32> = HashMap::new();
    let mut overall_max: i32 = i32::MIN;
    // Run program (we initialize registers to 0 when not found)
    // <reg1> <inc or dec> <n: i32> if <reg2> <operator> <m: i32>
    for instruction in instructions {
        let parts: Vec<&str> = instruction.split_whitespace().collect();
        // evaluate condition
        let reg2 = parts[4].to_string();
        let operator = parts[5];
        let m: i32 = parts[6].parse().unwrap();
        let mut condition: bool = false;
        if operator == ">" {
            if *registers.entry(reg2).or_insert(0) > m {
                condition = true;
            }
        } else if operator == "<" {
            if *registers.entry(reg2).or_insert(0) < m {
                condition = true;
            }
        } else if operator == ">=" {
            if *registers.entry(reg2).or_insert(0) >= m {
                condition = true;
            }
        } else if operator == "<=" {
            if *registers.entry(reg2).or_insert(0) <= m {
                condition = true;
            }
        } else if operator == "==" {
            if *registers.entry(reg2).or_insert(0) == m {
                condition = true;
            }
        } else if operator == "!=" {
            if *registers.entry(reg2).or_insert(0) != m {
                condition = true;
            }
        }
        // execute action
        if !condition {
            continue;
        }
        let reg1 = parts[0].to_string();
        let operation = parts[1];
        let n: i32 = parts[2].parse().unwrap();
        if operation == "inc" {
            *registers.entry(reg1).or_insert(0) += n;
        } else if  operation == "dec" {
            *registers.entry(reg1).or_insert(0) -= n;
        }
        if registers.values().max().unwrap().clone() > overall_max {
            overall_max = registers.values().max().unwrap().clone();
        }
    }
    overall_max
}

fn main() {
    let input: Vec<String> = read_inputs(8);
    println!("Part 1: {}", solve_part1(input.clone()));
    println!("Part 2: {}", solve_part2(input));
}

#[cfg(test)]
mod tests {
    use super::*;

    use aoc2017::read_examples;

    #[test]
    fn test_part1() {
        let input = read_examples(8);
        assert_eq!(solve_part1(input), 1);
    }

    #[test]
    fn test_part2() {
        let input = read_examples(8);
        assert_eq!(solve_part2(input), 10);
    }
}
