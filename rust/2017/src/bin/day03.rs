use std::collections::HashMap;

use aoc2017::read_input;

fn solve_part1(target: i32) -> i32 {
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut num = 1;
    let mut movement: i8 = 0;  // 0: right, 1: up, 2: left, 3: down
    let mut max = 1;
    loop {
        // replicates building of infinite grid
        if num == target {
            return x.abs() + y.abs();
        }
        num += 1;
        if movement == 0 {
            x += 1;
            if x.abs() == max {
                movement += 1;
            }
        } else if movement == 1 {
            y += 1;
            if y.abs() == max {
                movement += 1;
            }
        } else if movement == 2 {
            x -= 1;
            if x.abs() == max {
                movement += 1
            }
        } else {
            y -= 1;
            if y.abs() == max {
                movement = 0;
                max += 1;
            }
        }
    }
}

fn sum_neighbors(grid: HashMap<(i32, i32), i32>, x: i32, y: i32) -> i32 {
    let mut sum: i32 = 0;
    sum += grid.get(&(x-1, y+1)).copied().unwrap_or(0);
    sum += grid.get(&(x, y+1)).copied().unwrap_or(0);
    sum += grid.get(&(x+1, y+1)).copied().unwrap_or(0);
    sum += grid.get(&(x-1, y)).copied().unwrap_or(0);
    sum += grid.get(&(x+1, y)).copied().unwrap_or(0);
    sum += grid.get(&(x-1, y-1)).copied().unwrap_or(0);
    sum += grid.get(&(x, y-1)).copied().unwrap_or(0);
    sum += grid.get(&(x+1, y-1)).copied().unwrap_or(0);
    sum
}

fn solve_part2(target: i32) -> i32 {
    let mut grid: HashMap<(i32, i32), i32> = HashMap::new();
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut num: i32 = 1;
    let mut movement: i8 = 0;  // 0: right, 1: up, 2: left, 3: down 
    let mut max = 1;
    loop {
        if num > target {
            return num;
        }
        grid.insert((x, y), num);
        // replicates building of infinite grid
        if movement == 0 {
            x += 1;
            if x.abs() == max {
                movement += 1;
            }
        } else if movement == 1 {
            y += 1;
            if y.abs() == max {
                movement += 1;
            }
        } else if movement == 2 {
            x -= 1;
            if x.abs() == max {
                movement += 1
            }
        } else {
            y -= 1;
            if y.abs() == max {
                movement = 0;
                max += 1;
            }
        }
        num = sum_neighbors(grid.clone(), x, y);
    }
}

fn main() {
    let target: i32 = read_input(3).parse().unwrap();
    println!("Part 1: {}", solve_part1(target));
    println!("Part 2: {}", solve_part2(target));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        assert_eq!(solve_part1(1), 0);
        assert_eq!(solve_part1(12), 3);
        assert_eq!(solve_part1(23), 2);
        assert_eq!(solve_part1(1024), 31);
    }

    #[test]
    fn test_part2() {
        assert_eq!(solve_part2(800), 806);
    }
}
