use aoc2017::read_input;

fn solve_part1(movements: String) -> i32 {
    let apothem: f64 = 2.0;
    let dx: f64 = 3.0_f64.sqrt();  // 2 * cosine(30deg)
    let dy: f64 = 1.0;  // 2 * sine(30deg)
    // Represent hexagon in 2D space using each center point
    let mut x = 0.0;
    let mut y = 0.0;
    for movement in movements.split(',') {
        if movement == "n" {
            y += apothem;
        } else if  movement == "s" {
            y -= apothem;
        } else if movement == "ne" {
            x += dx;
            y += dy;
        } else if movement == "se" {
            x += dx;
            y -= dy;
        } else if movement == "sw" {
            x -= dx;
            y -= dy;
        } else {
            assert_eq!(movement, "nw");
            x -= dx;
            y += dy;
        }
    }
    // Calculate how many steps away are we
    let err: f64 = 0.000001;
    let mut steps = 0;
    while x.abs() > err || y.abs() > err {
        // First move horizontally while approaching vertically too
        if x > err {
            x -= dx;
            if y > err {
                y -= dy;
            } else {
                y += dy;
            }
        } else if x < -err {
            x += dx;
            if y > err {
                y -= dy;
            } else {
                y += dy;
            }
        } else if y > err {
            y -= apothem;
        } else if y < -err {
            y += apothem;
        }
        steps += 1;
    }
    steps
}

fn get_steps(mut x: f64, mut y: f64) -> i32 {
    let apothem: f64 = 2.0;
    let dx: f64 = 3.0_f64.sqrt();  // 2 * cosine(30deg)
    let dy: f64 = 1.0;  // 2 * sine(30deg)
    let err: f64 = 0.000001;
    let mut steps = 0;
    while x.abs() > err || y.abs() > err {
        // First move horizontally while approaching vertically too
        if x > err {
            x -= dx;
            if y > err {
                y -= dy;
            } else {
                y += dy;
            }
        } else if x < -err {
            x += dx;
            if y > err {
                y -= dy;
            } else {
                y += dy;
            }
        } else if y > err {
            y -= apothem;
        } else if y < -err {
            y += apothem;
        }
        steps += 1;
    }
    steps
}

fn solve_part2(movements: String) -> i32 {
    let apothem: f64 = 2.0;
    let dx: f64 = 3.0_f64.sqrt();  // 2 * cosine(30deg)
    let dy: f64 = 1.0;  // 2 * sine(30deg)
    let mut x = 0.0;
    let mut y = 0.0;
    let mut max_steps = 0;
    for movement in movements.split(',') {
        if movement == "n" {
            y += apothem;
        } else if  movement == "s" {
            y -= apothem;
        } else if movement == "ne" {
            x += dx;
            y += dy;
        } else if movement == "se" {
            x += dx;
            y -= dy;
        } else if movement == "sw" {
            x -= dx;
            y -= dy;
        } else {
            assert_eq!(movement, "nw");
            x -= dx;
            y += dy;
        }
        if get_steps(x, y) > max_steps {
            max_steps = get_steps(x, y);
        }
    }
    max_steps
}

fn main() {
    let input = read_input(11);
    println!("Part 1: {}", solve_part1(input.clone()));
    println!("Part 2: {}", solve_part2(input));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        assert_eq!(solve_part1("ne,ne,ne".to_string()), 3);
        assert_eq!(solve_part1("ne,ne,sw,sw".to_string()),0);
        assert_eq!(solve_part1("ne,ne,s,s".to_string()), 2);
        assert_eq!(solve_part1("se,sw,se,sw,sw".to_string()), 3);
    }
}
