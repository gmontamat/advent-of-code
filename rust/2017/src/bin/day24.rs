use aoc2017::read_inputs;

fn dfs(available: Vec<[i32; 2]>, last_type: i32, current_strength: i32, mut max_strength: i32) -> i32 {
    for i in 0..available.len() {
        let component = available[i];
        if component[0] == last_type {
            let mut remaining = available.clone();
            remaining.remove(i);
            let strength = dfs(
                remaining, component[1],
                current_strength + component[1] + component[0],
                max_strength
            );
            if strength > max_strength {
                max_strength = strength;
            }
        } else if component[1] == last_type {
            let mut remaining = available.clone();
            remaining.remove(i);
            let strength = dfs(
                remaining, component[0],
                current_strength + component[1] + component[0],
                max_strength
            );
            if strength > max_strength {
                max_strength = strength;
            }
        }
    }
    if current_strength > max_strength {
        return current_strength;
    }
    max_strength
}

fn solve_part1(input: Vec<String>) -> i32 {
    let mut components: Vec<[i32; 2]> = Vec::new();
    // parse input
    for component in input {
        let parts: Vec<i32> = component.split('/').map(|s| s.parse().unwrap()).collect();
        components.push([parts[0], parts[1]]);
    }
    dfs(components, 0, 0, 0)
}

fn dfs_len(available: Vec<[i32; 2]>, last_type: i32, current_strength: i32, mut max_strength: i32) -> i32 {
    for i in 0..available.len() {
        let component = available[i];
        if component[0] == last_type {
            let mut remaining = available.clone();
            remaining.remove(i);
            let strength = dfs_len(remaining, component[1],
                current_strength + component[1] + component[0] + 100_000,
                max_strength
            );
            if strength > max_strength {
                max_strength = strength;
            }
        } else if component[1] == last_type {
            let mut remaining = available.clone();
            remaining.remove(i);
            let strength = dfs_len(remaining, component[0],
                current_strength + component[1] + component[0] + 100_000,
                max_strength
            );
            if strength > max_strength {
                max_strength = strength;
            }
        }
    }
    if current_strength > max_strength {
        return current_strength;
    }
    max_strength
}

fn solve_part2(input: Vec<String>) -> i32 {
    // strategy: current path = 100_000 * length + strength
    let mut components: Vec<[i32; 2]> = Vec::new();
    // parse input
    for component in input {
        let parts: Vec<i32> = component.split('/').map(|s| s.parse().unwrap()).collect();
        components.push([parts[0], parts[1]]);
    }
    dfs_len(components, 0, 0, 0) % 100_000
}

fn main() {
    let input = read_inputs(24);
    println!("Part 1: {}", solve_part1(input.clone()));
    println!("Part 2: {}", solve_part2(input));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples;

    use super::*;

    #[test]
    fn test_part1() {
        let input = read_examples(24);
        assert_eq!(solve_part1(input), 31);
    }

    #[test]
    fn test_part2() {
        let input = read_examples(24);
        assert_eq!(solve_part2(input), 19);
    }
}
