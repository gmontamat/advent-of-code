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

fn knot_hash(input: String) -> String {
    let mut current_position: usize = 0;
    let mut skip_size: usize = 0;
    let mut circle = (0..256).collect();
    let mut input_lengths: Vec<usize> = input.chars()
        .map(|c| c as usize)
        .collect();
    input_lengths.push(17);
    input_lengths.push(31);
    input_lengths.push(73);
    input_lengths.push(47);
    input_lengths.push(23);
    for _ in 0..64 {
        for length in &input_lengths {
            circle = reverse(circle, current_position, *length as usize);
            // println!("{:?}", circle);
            current_position += *length as usize + skip_size;
            current_position %= 256 as usize;
            skip_size += 1;
        }
    }
    // Dense hash
    let mut hash = "".to_string();
    for i in 0..16 {
        let mut xored: u8 = circle.get(i * 16).unwrap().clone() as u8;
        for j in 1..16 {
            xored ^= circle.get(i * 16 + j).unwrap().clone() as u8;
        }
        let hex_padded = format!("{:02x}", xored); 
        hash.push_str(&hex_padded);
    }
    hash
}

fn solve_part1(input: String) -> i32 {
    for row in 0..128 {
        // Compute hash
        let hash_input = format!("{input}-{row}");
        let hash = knot_hash(hash_input);
        // Convert hash to binary
        println!("{hash}");
    }
    0
}

fn main() {
    let input = read_input(14);
    println!("Part 1: {}", solve_part1(input));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_knot_hash() {
        assert_eq!(knot_hash("".to_string()), "a2582a3a0e66e6e86e3812dcb672a272");
        assert_eq!(knot_hash("AoC 2017".to_string()), "33efeb34ea91902bb2f59c9920caa6cd");
        assert_eq!(knot_hash("1,2,3".to_string()), "3efbe78a8d82f29979031a4aa0b16a9d");
        assert_eq!(knot_hash("1,2,4".to_string()), "63960835bcdc130f0b66d7ff4f6a5a8e");
    }

    #[test]
    fn test_part1() {
        assert_eq!(solve_part1("flqrgnkx".to_string()), 8108);
    }
}
