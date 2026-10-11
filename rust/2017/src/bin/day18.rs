use std::collections::HashMap;

use aoc2017::read_inputs;

fn is_numeric(s: &str) -> bool {
    s.parse::<f64>().is_ok()
}

fn solve_part1(instructions: Vec<String>) -> i64 {
    let mut last_freq: i64 = 0;
    let mut registers: HashMap<char, i64> = HashMap::new();
    let mut current: i64 = 0;
    loop {
        if current >= instructions.len().try_into().unwrap() || current < 0 {
            break -1;  // error code
        }
        let instruction = &instructions[current as usize]; 
        let parts: Vec<&str>= instruction.split_whitespace().collect();
        // Parse registers and values
        let mut reg: char = '*';  // null register (not to be used)
        let arg1: i64;
        let mut arg2: i64 = 0;
        if is_numeric(parts[1]) {
            arg1 = parts[1].parse().unwrap();
        } else {
            reg = parts[1].chars().next().unwrap();
            arg1 = *registers.get(&reg).unwrap_or(&0);
        }
        if !(parts[0] == "snd" || parts[0] == "rcv") {
            if is_numeric(parts[2]) {
                arg2 = parts[2].parse().unwrap();
            } else {
                let register: char = parts[2].chars().next().unwrap();
                arg2 = *registers.get(&register).unwrap_or(&0);
            }
        }
        // Execute instruction
        if parts[0] == "snd" {
            last_freq = arg1;
        } else if parts[0] == "set" {
            registers.insert(reg, arg2);
        } else if parts[0] == "add" {
            registers.insert(reg, arg1 + arg2);
        } else if parts[0] == "mul" {
            registers.insert(reg, arg1 * arg2);
        } else if parts[0] == "mod" {
            registers.insert(reg, arg1 % arg2);
        } else if parts[0] == "rcv" {
            if arg1 > 0 {
                return last_freq;
            }
        } else if parts[0] == "jgz" {
            if arg1 > 0 {
                current += arg2;
                continue;  // do not step
            }
        }
        current += 1;
    }
}

fn solve_part2(instructions: Vec<String>) -> i32 {
    let mut values_sent: i32 = 0;
    let mut msg_queues: [Vec<i64>; 2] = [Vec::new(), Vec::new()];
    let mut registers: [HashMap<char, i64>; 2] = [HashMap::new(), HashMap::new()];
    registers[0].insert('p', 0);
    registers[1].insert('p', 1);
    let mut counters: [i64; 2] = [0, 0];
    let mut program: usize = 0;  // which program's instruction should I run
    let mut flip: bool = false;  // change program to be executed in this cycle
    let mut waiting: bool = false;  // deadlock detection
    // Begin execution
    loop {
        // Flip
        if flip {
            if program == 1 {
                program = 0;
            } else {
                program = 1;
            }
            flip = false;
        }
        if counters[program] >= instructions.len().try_into().unwrap() || counters[program] < 0 {
            println!("overflow(id{program})");
            break;
        }
        // Parse registers and values
        let instruction = &instructions[counters[program] as usize]; 
        let parts: Vec<&str>= instruction.split_whitespace().collect();
        let mut reg: char = '*';  // null register (not to be used)
        let arg1: i64;
        let mut arg2: i64 = 0;
        if is_numeric(parts[1]) {
            arg1 = parts[1].parse().unwrap();
        } else {
            reg = parts[1].chars().next().unwrap();
            arg1 = *registers[program].get(&reg).unwrap_or(&0);
        }
        if !(parts[0] == "snd" || parts[0] == "rcv") {
            if is_numeric(parts[2]) {
                arg2 = parts[2].parse().unwrap();
            } else {
                let register: char = parts[2].chars().next().unwrap();
                arg2 = *registers[program].get(&register).unwrap_or(&0);
            }
        }
        // Reset deadlock detection
        if parts[0] != "rcv" {
            waiting = false;
        }
        // Execute instruction
        if parts[0] == "snd" {
            if program == 1 {
                msg_queues[0].push(arg1);
                values_sent += 1;
            } else if program == 0 {
                msg_queues[1].push(arg1);
            }
            // println!("id{program} sent {arg1}");
        } else if parts[0] == "set" {
            registers[program].insert(reg, arg2);
        } else if parts[0] == "add" {
            registers[program].insert(reg, arg1 + arg2);
        } else if parts[0] == "mul" {
            registers[program].insert(reg, arg1 * arg2);
        } else if parts[0] == "mod" {
            registers[program].insert(reg, arg1 % arg2);
        } else if parts[0] == "rcv" {
            if program == 0 {
                if msg_queues[0].len() > 0 {
                    registers[program].insert(reg, msg_queues[0].remove(0));
                } else {
                    if waiting {
                        // println!("deadlock(0)!");
                        break;
                    }
                    waiting = true;
                    flip = true;
                    continue;  // skip step for now
                }
            } else if program == 1 {
                if msg_queues[1].len() > 0 {
                    registers[program].insert(reg, msg_queues[1].remove(0));
                } else {
                    if waiting {
                        // println!("deadlock(1)!");
                        break;
                    }
                    waiting = true;
                    flip = true;
                    continue;  // skip step for now
                }
            }
        } else if parts[0] == "jgz" {
            if arg1 > 0 {
                counters[program] += arg2;
                continue;  // do not step
            }
        }
        counters[program] += 1;
    }
    values_sent
}

fn main() {
    let instructions = read_inputs(18);
    println!("Part 1: {}", solve_part1(instructions.clone()));
    println!("Part 2: {}", solve_part2(instructions));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples_file;

    use super::*;

    #[test]
    fn test_part1() {
        let instructions = read_examples_file("day18p1");
        assert_eq!(solve_part1(instructions), 4);
    }

    #[test]
    fn test_part2() {
        let instructions = read_examples_file("day18p2");
        assert_eq!(solve_part2(instructions), 3);
    }
}
