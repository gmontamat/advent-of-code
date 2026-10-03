use aoc2017::read_input;

fn solve_part1(programs: usize, moves: Vec<String>) -> String {
    let mut line: Vec<char> = Vec::new();
    for i in 0..programs {
        line.push(char::from_u32((i + 97).try_into().unwrap()).unwrap());
    }
    for current_move in moves {
        if current_move.chars().nth(0).unwrap() == 's' {
            // Parse spin value
            let value: String = current_move.chars().skip(1).collect();
            let spin: usize = value.parse().unwrap();
            // Spin
            line.rotate_right(spin % programs);
        } else if current_move.chars().nth(0).unwrap() == 'x' {
            // Parse exchange indexes
            let values: String = current_move.chars().skip(1).collect();
            let idx1: usize = values.split('/').nth(0).unwrap().parse().unwrap();
            let idx2: usize = values.split('/').nth(1).unwrap().parse().unwrap();
            // Exchange
            line.swap(idx1, idx2);
        } else if current_move.chars().nth(0).unwrap() == 'p' {
            // Parse partner programs
            let values: String = current_move.chars().skip(1).collect();
            assert_eq!(values.chars().nth(1).unwrap(), '/');
            let program1: char = values.chars().nth(0).unwrap();
            let program2: char = values.chars().nth(2).unwrap();
            for i in 0..programs {
                if line[i] == program1 {
                    line[i] = program2;
                } else if line[i] == program2 {
                    line[i] = program1;
                }
            }
        }
    }
    line.into_iter().collect()
}

fn solve_part2(programs: usize, moves: Vec<String>, times: u32) -> String {
    let mut line: Vec<char> = Vec::new();
    let mut original: Vec<char> = Vec::new();
    for i in 0..programs {
        line.push(char::from_u32((i + 97).try_into().unwrap()).unwrap());
        original.push(char::from_u32((i + 97).try_into().unwrap()).unwrap());
    }
    // Find number of times needed to get back to initial position ("steps")
    // Then only repeat 1_000_000_000 mod steps
    let mut steps: u32 = 0;
    let mut found: bool = false;
    for t in 1..times+1 {
        for current_move in &moves {
            if current_move.chars().nth(0).unwrap() == 's' {
                // Parse spin value
                let value: String = current_move.chars().skip(1).collect();
                let spin: usize = value.parse().unwrap();
                // Spin
                line.rotate_right(spin % programs);
            } else if current_move.chars().nth(0).unwrap() == 'x' {
                // Parse exchange indexes
                let values: String = current_move.chars().skip(1).collect();
                let idx1: usize = values.split('/').nth(0).unwrap().parse().unwrap();
                let idx2: usize = values.split('/').nth(1).unwrap().parse().unwrap();
                // Exchange
                line.swap(idx1, idx2);
            } else if current_move.chars().nth(0).unwrap() == 'p' {
                // Parse partner programs
                let values: String = current_move.chars().skip(1).collect();
                assert_eq!(values.chars().nth(1).unwrap(), '/');
                let program1: char = values.chars().nth(0).unwrap();
                let program2: char = values.chars().nth(2).unwrap();
                for i in 0..programs {
                    if line[i] == program1 {
                        line[i] = program2;
                    } else if line[i] == program2 {
                        line[i] = program1;
                    }
                }
            }
        }
        if line == original {
            steps = t;
            found = true;
            break;
        }
    }
    if !found {
        return line.into_iter().collect();
    }
    // println!("Pattern repeats after {steps} steps.");
    for _ in 0..times%steps {
        for current_move in &moves {
            if current_move.chars().nth(0).unwrap() == 's' {
                // Parse spin value
                let value: String = current_move.chars().skip(1).collect();
                let spin: usize = value.parse().unwrap();
                // Spin
                line.rotate_right(spin % programs);
            } else if current_move.chars().nth(0).unwrap() == 'x' {
                // Parse exchange indexes
                let values: String = current_move.chars().skip(1).collect();
                let idx1: usize = values.split('/').nth(0).unwrap().parse().unwrap();
                let idx2: usize = values.split('/').nth(1).unwrap().parse().unwrap();
                // Exchange
                line.swap(idx1, idx2);
            } else if current_move.chars().nth(0).unwrap() == 'p' {
                // Parse partner programs
                let values: String = current_move.chars().skip(1).collect();
                assert_eq!(values.chars().nth(1).unwrap(), '/');
                let program1: char = values.chars().nth(0).unwrap();
                let program2: char = values.chars().nth(2).unwrap();
                for i in 0..programs {
                    if line[i] == program1 {
                        line[i] = program2;
                    } else if line[i] == program2 {
                        line[i] = program1;
                    }
                }
            }
        }
    }
    line.into_iter().collect()
}

fn main() {
    let moves: Vec<String> = read_input(16).split(",")
                                           .map(|s| s.to_string())
                                           .collect();
    println!("Part 1: {}", solve_part1(16, moves.clone()));
    println!("Part 2: {}", solve_part2(16, moves, 1_000_000_000));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_example;

    use super::*;

    #[test]
    fn test_part1() {
        let moves = read_example(16).split(",")
                                    .map(|s| s.to_string())
                                    .collect();
        assert_eq!(solve_part1(5, moves), "baedc".to_string());
    }

    #[test]
    fn test_part2() {
        let moves = read_example(16).split(",")
                                    .map(|s| s.to_string())
                                    .collect();
        assert_eq!(solve_part2(5, moves, 2), "ceadb".to_string());
    }
}
