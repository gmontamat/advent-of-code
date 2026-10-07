use aoc2017::read_input;

fn solve_part1(step: usize) -> usize {
    let mut buffer: Vec<usize> = [0].to_vec();
    let mut current: usize = 0;
    let mut insert: usize = 1;
    for _ in 1..2017+1 {
        current = (current + step) % insert + 1;  // insert is the buffer size
        buffer.insert(current, insert);
        // println!("{buffer:?}");
        insert += 1;
    }
    buffer[current + 1]
}

fn solve_part2(step: usize) -> usize {
    // strategy: no need to build the buffer
    // just check when we insert at position 1
    // (0 will always remain the first element in the buffer)
    let mut current: usize = 0;
    let mut insert: usize = 1;
    let mut result: usize = 0;
    for _ in 1..50_000_000+1 {
        current = (current + step) % insert + 1;  // insert is the buffer size
        if current == 1 {
            result = insert;
        }
        insert += 1;
    }
    result
}

fn main() {
    let step: usize = read_input(17).parse().unwrap();
    println!("Part 1: {}", solve_part1(step));
    println!("Part 2: {}", solve_part2(step));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        assert_eq!(solve_part1(3), 638);
    }
}
