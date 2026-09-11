use std::collections::HashMap;

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
    let mut hex_table: HashMap<char, i32> = HashMap::new();
    hex_table.insert('0', 0);  // 0000
    hex_table.insert('1', 1);  // 0001
    hex_table.insert('2', 1);  // 0010
    hex_table.insert('3', 2);  // 0011
    hex_table.insert('4', 1);  // 0100
    hex_table.insert('5', 2);  // 0101
    hex_table.insert('6', 2);  // 0110
    hex_table.insert('7', 3);  // 0111
    hex_table.insert('8', 1);  // 1000
    hex_table.insert('9', 2);  // 1001
    hex_table.insert('a', 2);  // 1010
    hex_table.insert('b', 3);  // 1011
    hex_table.insert('c', 2);  // 1100
    hex_table.insert('d', 3);  // 1101
    hex_table.insert('e', 3);  // 1110
    hex_table.insert('f', 4);  // 1111
    let mut total = 0;
    for row in 0..128 {
        // Compute hash
        let hash_input = format!("{input}-{row}");
        let hash = knot_hash(hash_input);
        // Convert hash to binary
        for c in hash.chars() {
            total += *hex_table.get(&c).unwrap();
        }
        // println!("{hash}");
    }
    total
}

fn floodfill(grid: &mut [[char; 128]; 128], row: usize, col: usize) {
    if grid[row][col] == '0' {
        return;
    }
    grid[row][col] = '0';
    if row > 0 {
        floodfill(grid, row - 1, col);
    }
    if col < 127 {
        floodfill(grid, row, col + 1);
    }
    if col > 0 {
        floodfill(grid, row, col - 1);
    }
    if row < 127 {
        floodfill(grid, row + 1, col);
    }
}

fn solve_part2(input: String) -> i32 {
    // Advent of flood fill
    let mut grid = [['0'; 128]; 128];
    let mut hex_table: HashMap<char, String> = HashMap::new();
    hex_table.insert('0', "0000".to_string());
    hex_table.insert('1', "0001".to_string());
    hex_table.insert('2', "0010".to_string());
    hex_table.insert('3', "0011".to_string());
    hex_table.insert('4', "0100".to_string());
    hex_table.insert('5', "0101".to_string());
    hex_table.insert('6', "0110".to_string());
    hex_table.insert('7', "0111".to_string());
    hex_table.insert('8', "1000".to_string());
    hex_table.insert('9', "1001".to_string());
    hex_table.insert('a', "1010".to_string());
    hex_table.insert('b', "1011".to_string());
    hex_table.insert('c', "1100".to_string());
    hex_table.insert('d', "1101".to_string());
    hex_table.insert('e', "1110".to_string());
    hex_table.insert('f', "1111".to_string());
    for row in 0..128 {
        // Compute hash
        let hash_input = format!("{input}-{row}");
        let hash = knot_hash(hash_input);
        let mut col: usize = 0;
        // Convert hash to binary
        for c in hash.chars() {
            let binary = hex_table.get(&c).unwrap();
            for v in binary.chars() {
                grid[row][col] = v;
                col += 1;
            }
        }
    }
    // Find groups
    let mut total = 0;
    for row in 0..128 {
        for col in 0..128 {
            if grid[row][col] == '1' {
                total += 1;
                floodfill(&mut grid, row, col);
            }
        }
    }
    total
}

fn main() {
    let input = read_input(14);
    println!("Part 1: {}", solve_part1(input.clone()));
    println!("Part 2: {}", solve_part2(input));
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

    #[test]
    fn test_part2() {
        assert_eq!(solve_part2("flqrgnkx".to_string()), 1242);
    }
}
