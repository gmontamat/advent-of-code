use aoc2017::read_input;

fn solve_part1(digits: &str) -> u32 {
    let mut count: u32 = 0;
    let len = digits.len();
    for i in 0..len {
        let next = (i + 1) % len;
        if digits.chars().nth(i) == digits.chars().nth(next) {
            count += digits.chars()
                        .nth(i)
                        .expect("nth(i) error")
                        .to_digit(10)
                        .expect("to_digit error");
        }
    }
    count
}

fn solve_part2(digits: &str) -> u32 {
    let mut count: u32 = 0;
    let len = digits.len();
    let offset = len / 2;
    for i in 0..len {
        let next = (i + offset) % len;
        if digits.chars().nth(i) == digits.chars().nth(next) {
            count += digits.chars()
                        .nth(i)
                        .expect("nth(i) error")
                        .to_digit(10)
                        .expect("to_digit error");
        }
    }
    count
}

fn main() {
    let input = read_input(1);
    println!("Part 1: {}", solve_part1(&input));
    println!("Part 2: {}", solve_part2(&input));
}

#[cfg(test)]
mod tests {
    use super::*;
    use aoc2017::read_examples;

    #[test]
    fn test_part1() {
        let examples = read_examples(1);
        assert_eq!(solve_part1(&examples[0]), 3);
        assert_eq!(solve_part1(&examples[1]), 4);
        assert_eq!(solve_part1(&examples[2]), 0);
        assert_eq!(solve_part1(&examples[3]), 9);
    }

    #[test]
    fn test_part2() {
        let examples = read_examples(1);
        assert_eq!(solve_part2(&examples[4]), 6);
        assert_eq!(solve_part2(&examples[5]), 0);
        assert_eq!(solve_part2(&examples[6]), 4);
        assert_eq!(solve_part2(&examples[7]), 12);
        assert_eq!(solve_part2(&examples[8]), 4);

    }
}
