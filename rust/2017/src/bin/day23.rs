use std::collections::HashMap;

use aoc2017::read_inputs;

fn is_numeric(s: &str) -> bool {
    s.parse::<f64>().is_ok()
}

fn solve_part1(instructions: Vec<String>) -> i64 {
    let mut mul_invoked: i64 = 0;
    let mut registers: HashMap<char, i64> = HashMap::new();
    let mut current: i64 = 0;
    loop {
        if current >= instructions.len().try_into().unwrap() || current < 0 {
            break;  // program terminated!
        }
        let instruction = &instructions[current as usize]; 
        let parts: Vec<&str>= instruction.split_whitespace().collect();
        // Parse registers and values
        let mut reg: char = '*';  // null register (not to be used)
        let arg1: i64;
        let arg2: i64;
        if is_numeric(parts[1]) {
            arg1 = parts[1].parse().unwrap();
        } else {
            reg = parts[1].chars().next().unwrap();
            arg1 = *registers.get(&reg).unwrap_or(&0);
        }
        // get arg2 (value)
        if is_numeric(parts[2]) {
            arg2 = parts[2].parse().unwrap();
        } else {
            let register: char = parts[2].chars().next().unwrap();
            arg2 = *registers.get(&register).unwrap_or(&0);
        }
        // Execute instruction
        if parts[0] == "set" {
            registers.insert(reg, arg2);
        } else if parts[0] == "sub" {
            registers.insert(reg, arg1 - arg2);
        } else if parts[0] == "mul" {
            registers.insert(reg, arg1 * arg2);
            mul_invoked += 1;
        } else if parts[0] == "jnz" {
            if !(arg1 == 0) {
                current += arg2;
                continue;  // do not step
            }
        }
        current += 1;
    }
    mul_invoked
}

fn is_prime(num: u64) -> bool {
    if num <= 1 {
        return false;
    }
    for i in 2..(num as f64).sqrt() as u64 {
        if num % i == 0 {
            return false;
        }
    }
    true
}

fn solve_part2() -> i32 {
    // Python translation of machine language
    // count composite numbers in range b - c step 17
    /*
        def part2(b, c):
            h = 0
            while True:
                f = 1  # is_prime flag
                d = 2
                while d != b:
                    e = 2
                    while e != b:
                        if d * e == b:
                            f = 0
                        e += 1
                    d += 1
                if f == 0:
                    h += 1
                if b == c:
                    return h
                b += 17
     */
    let mut ctr = 0;
    let mut b: u64 = 81 * 100 + 100000;
    let c: u64 = b + 17000;
    loop {
        if !is_prime(b) {
            ctr += 1;
        }
        b += 17;
        if b > c {
            break;
        }
    }
    ctr
}

fn main() {
    let instructions = read_inputs(23);
    println!("Part 1: {}", solve_part1(instructions));
    println!("Part 2: {}", solve_part2());
}

#[cfg(test)]
mod tests {
    // use aoc2017::read_examples_file;

    // use super::*;

    #[test]
    fn test_part1() {
        println!("No tests today!");
        assert_eq!(true, true);
    }
}
