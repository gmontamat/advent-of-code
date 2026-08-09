use aoc2017::read_input;

fn reverse(mut circle: Vec<i32>, start: usize, length: usize) -> Vec<i32> {
    let len = circle.len();
    for i in 0..length/2 {
        let a = (start + i) % len;
        let b = (start + length - i - 1) % len;
        circle.swap(a, b);
    }
    circle
}

fn solve_part1(size: i32, input_lengths: Vec<i32>) -> i32 {
    let mut current_position: usize = 0;
    let mut skip_size: usize = 0;
    let mut circle = Vec::new();
    for i in 0..size {
        circle.push(i);
    }
    for length in input_lengths {
        circle = reverse(circle, current_position, length as usize);
        // println!("{:?}", circle);
        current_position += length as usize + skip_size;
        current_position %= size as usize;
        skip_size += 1;
    }
    circle.get(0).unwrap() * circle.get(1).unwrap()
}

fn solve_part2(_input: String) -> String {
    let mut current_position: usize = 0;
    let mut skip_size: usize = 0;
    // Create circle array
    let mut circle = Vec::new();
    for i in 0..256 {
        circle.push(i);
    }
    for i in 0..64 {
        for length in input_lengths {
            circle = reverse(circle, current_position, length as usize);
            // println!("{:?}", circle);
            current_position += length as usize + skip_size;
            current_position %= size as usize;
            skip_size += 1;
        }
    }
    "".to_string()
}

fn main() {
    let input_lengths: Vec<i32> = read_input(10)
        .split(',')
        .map(|s| s.trim().parse().expect("Not a valid number"))
        .collect();
    println!("Part 1: {}", solve_part1(256, input_lengths));
    let input = read_input(10);
    println!("Part 2: {}", solve_part2(input));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        let input_lengths = vec![3, 4, 1, 5];
        assert_eq!(solve_part1(5, input_lengths), 12);
    }

    #[test]
    fn test_part2() {
        assert_eq!(solve_part2("".to_string()), "a2582a3a0e66e6e86e3812dcb672a272");
        assert_eq!(solve_part2("AoC 2017".to_string()), "33efeb34ea91902bb2f59c9920caa6cd");
        assert_eq!(solve_part2("1,2,3".to_string()), "3efbe78a8d82f29979031a4aa0b16a9d");
        assert_eq!(solve_part2("1,2,4".to_string()), "63960835bcdc130f0b66d7ff4f6a5a8e");
    }
}
