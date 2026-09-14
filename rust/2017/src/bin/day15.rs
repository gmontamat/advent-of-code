use aoc2017::read_input;

fn parse_input(input: String) -> (i64, i64) {
    let lines: Vec<&str> = input.lines().collect();
    let a: i64 = lines[0].split_whitespace().last().unwrap().parse().unwrap();
    let b: i64 = lines[1].split_whitespace().last().unwrap().parse().unwrap();
    (a, b)
}

fn solve_part1(seed_a: i64, seed_b: i64) -> i32 {
    let mut total: i32 = 0;
    let mut a = seed_a;
    let mut b = seed_b;
    for _ in 0..40_000_000 {
        a = (a * 16807) % 2147483647;
        b = (b * 48271) % 2147483647;
        if a % 65536 == b % 65536 {
            total += 1;
        }
    }
    total
}

fn solve_part2(seed_a: i64, seed_b: i64) -> i32 {
    let mut total: i32 = 0;
    let mut a = seed_a;
    let mut b = seed_b;
    for _ in 0..5_000_000 {
        loop {
            a = (a * 16807) % 2147483647;
            if a % 4 == 0 {
                break;
            }
        }
        loop {
            b = (b * 48271) % 2147483647;
            if b % 8 == 0 {
                break;
            }
        }
        if a % 65536 == b % 65536 {
            total += 1;
        }
    }
    total
}

fn main() {
    let input = read_input(15);
    let (seed_a, seed_b) = parse_input(input);
    println!("Part 1: {}", solve_part1(seed_a, seed_b));
    println!("Part 2: {}", solve_part2(seed_a, seed_b));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        assert_eq!(solve_part1(65, 8921), 588);
    }

    #[test]
    fn test_part2() {
        assert_eq!(solve_part2(65, 8921), 309);
    }
}
