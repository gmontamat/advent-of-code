use aoc2017::read_inputs;

fn solve_part1(input: Vec<String>, bursts: i32) -> i32 {
    let mut map: Vec<Vec<bool>> = Vec::new();
    // Create "infinite" map
    for _ in 0..1000 {
        let row = vec![false; 1000];
        map.push(row);
    }
    // Put input in the center
    let y_len = input.len();
    let x_len = input[0].len();
    let mut row: usize = 500;
    for line in input {
        let mut col: usize = 500;
        for ch in line.chars() {
            if ch == '#' {
                map[row][col] = true;
            }
            col += 1;
        }
        row += 1;
    }
    // Carrier properties
    let mut x = 500 + x_len / 2;
    let mut y = 500 + y_len / 2;
    let mut direction: u8 = 0;  // 0: up, 1: right, 2: down, 3: left
    let mut infections: i32 = 0;
    for _ in 0..bursts {
        // update direction
        if map[y][x] {
            direction = (direction + 1) % 4;
        } else {
            if direction == 0 {
                direction = 3;
            } else {
                direction -= 1;
            }
        }
        // update status
        if !map[y][x] {
            infections += 1;
        }
        map[y][x] = !map[y][x];
        // move carrier
        if direction == 0 {
            assert!(y > 0, "OOB! (y==0)");
            y -= 1;
        } else if direction == 1 {
            assert!(x < 1000, "OOB! (x==1000)");
            x += 1;
        } else if direction == 2 {
            assert!(y < 1000, "OOB! (y==1000)");
            y += 1;
        } else {
            assert!(x > 0, "OOB! (x==0)");
            x -= 1;
        }
    }
    infections
}

fn solve_part2(input: Vec<String>, bursts: i32) -> i32 {
    let mut map: Vec<Vec<u8>> = Vec::new();
    // Create "infinite" map
    for _ in 0..1000 {
        let row = vec![0; 1000];
        map.push(row);
    }
    // Put input in the center
    let y_len = input.len();
    let x_len = input[0].len();
    let mut row: usize = 500;
    for line in input {
        let mut col: usize = 500;
        for ch in line.chars() {
            if ch == '#' {
                map[row][col] = 2;  // 0: clean, 1: weakened, 2: infected, 3: flagged
            }
            col += 1;
        }
        row += 1;
    }
    // Carrier properties
    let mut x = 500 + x_len / 2;
    let mut y = 500 + y_len / 2;
    let mut direction: u8 = 0;  // 0: up, 1: right, 2: down, 3: left
    let mut infections: i32 = 0;
    for _ in 0..bursts {
        // update direction
        if map[y][x] == 2 {
            direction = (direction + 1) % 4;  // turn right
        } else if map[y][x] == 0  {
            direction = (direction + 3) % 4;  // turn left
        } else if map[y][x] == 3 {
            direction = (direction + 2) % 4;  // reverse direction
        }
        // update status
        if map[y][x] == 1 {
            infections += 1;  // weakened becomes infected
        }
        map[y][x] = (map[y][x] + 1) % 4;
        // move carrier
        if direction == 0 {
            assert!(y > 0, "OOB! (y==0)");
            y -= 1;
        } else if direction == 1 {
            assert!(x < 1000, "OOB! (x==1000)");
            x += 1;
        } else if direction == 2 {
            assert!(y < 1000, "OOB! (y==1000)");
            y += 1;
        } else {
            assert!(x > 0, "OOB! (x==0)");
            x -= 1;
        }
    }
    infections
}

fn main() {
    let input = read_inputs(22);
    println!("Part 1: {}", solve_part1(input.clone(), 10000));
    println!("Part 2: {}", solve_part2(input, 10000000));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples;

    use super::*;

    #[test]
    fn test_part1() {
        let input = read_examples(22);
        assert_eq!(solve_part1(input.clone(), 70), 41);
        assert_eq!(solve_part1(input.clone(), 10000), 5587);
    }

    #[test]
    fn test_part2() {
        let input = read_examples(22);
        assert_eq!(solve_part2(input.clone(), 100), 26);
        assert_eq!(solve_part2(input.clone(), 10000000), 2511944);
    }
}
