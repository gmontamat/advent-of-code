use std::collections::HashMap;
use scanf::sscanf;

use aoc2017::read_inputs;

fn solve_part1(input: Vec<String>) -> i32 {
    let mut tape: [i32; 100000] = [0; 100000];  // "infinite" tape
    let mut cursor = tape.len() / 2;     // center
    let mut state: char = '?';                  // current state
    let mut steps: i32 = 0;                     // steps to checksum
    let mut rules: HashMap<char, [(i32, i32, char); 2]> = HashMap::new();
    // Parse initial state
    let line: &str = &input[0];
    sscanf!(line, "Begin in state {state}.").unwrap();
    // Parse number of steps
    let line: &str = &input[1];
    sscanf!(line, "Perform a diagnostic checksum after {steps} steps.").unwrap();
    // Parse rules
    let mut ctr: usize = 3;
    loop {
        let mut s: char = '?';
        let line: &str = &input[ctr];
        sscanf!(line, "In state {s}:").unwrap();
        let mut value_0: i32 = 0;
        let line: &str = &input[ctr + 2];
        sscanf!(line, "- Write the value {value_0}.").unwrap();
        let cursor_0: i32;
        let line: &str = &input[ctr + 3];
        if line == "- Move one slot to the right." {
            cursor_0 = 1;
        } else {
            cursor_0 = -1;
        }
        let mut state_0: char = '?';
        let line: &str = &input[ctr + 4];
        sscanf!(line, "- Continue with state {state_0}.").unwrap();
        let mut value_1: i32 = 0;
        let line: &str = &input[ctr + 6];
        sscanf!(line, "- Write the value {value_1}.").unwrap();
        let cursor_1: i32;
        let line: &str = &input[ctr + 7];
        if line == "- Move one slot to the right." {
            cursor_1 = 1;
        } else {
            cursor_1 = -1;
        }
        let mut state_1: char = '?';
        let line: &str = &input[ctr + 8];
        sscanf!(line, "- Continue with state {state_1}.").unwrap();
        rules.insert(s, [(value_0, cursor_0, state_0), (value_1, cursor_1, state_1)]);
        ctr += 10;
        if ctr > input.len() {
            break;
        }
    }
    // Simulate turing machine for "steps"
    for _ in 0..steps {
        let value = tape[cursor];
        let (next_value, next_cursor, next_state) = rules.get(&state).unwrap()[value as usize];
        tape[cursor] = next_value;
        cursor = (cursor as i32 + next_cursor) as usize;
        state = next_state;
    }
    tape.iter().sum()
}

fn main() {
    let input = read_inputs(25);
    println!("Part 1: {}", solve_part1(input));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples;

    use super::*;

    #[test]
    fn test_part1() {
        let input = read_examples(25);
        assert_eq!(solve_part1(input), 3);
    }
}
