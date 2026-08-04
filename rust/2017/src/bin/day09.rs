use aoc2017::read_input;

fn solve_part1(stream: String) -> i32 {
    let mut ignore = false;
    let mut garbage = false;
    let mut group = 0;
    let mut total = 0;
    for character in stream.chars() {
        if ignore {
            ignore = false;
            continue;
        }
        if garbage == true {
            if character == '>' {
                garbage = false;
            } else if character == '!' {
                ignore = true;
            }
            continue;
        }
        if character == '!' {
            ignore = true;
        } else if character == '<' {
            garbage = true;
        } else if character == '{' {
            group += 1;
            total += group;
        } else if character == '}' {
            if group > 0 {
                group -= 1;
            }
        }
    }
    // println!("{stream} : {total}");
    total
}

fn solve_part2(stream: String) -> i32 {
    let mut ignore = false;
    let mut garbage = false;
    let mut total = 0;
    for character in stream.chars() {
        if ignore {
            ignore = false;
            continue;
        }
        if garbage == true {
            if character == '>' {
                garbage = false;
            } else if character == '!' {
                ignore = true;
            } else {
                total += 1;
            }
            continue;
        }
        if character == '!' {
            ignore = true;
        } else if character == '<' {
            garbage = true;
        }
    }
    // println!("{stream} : {total}");
    total
}

fn main() {
    let input: String = read_input(9);
    println!("Part 1: {}", solve_part1(input.clone()));
    println!("Part 2: {}", solve_part2(input));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        assert_eq!(solve_part1("{}".to_string()), 1);
        assert_eq!(solve_part1("{{{}}}".to_string()), 6);
        assert_eq!(solve_part1("{{},{}}".to_string()), 5);
        assert_eq!(solve_part1("{{{},{},{{}}}}".to_string()), 16);
        assert_eq!(solve_part1("{<a>,<a>,<a>,<a>}".to_string()), 1);
        assert_eq!(solve_part1("{{<ab>},{<ab>},{<ab>},{<ab>}}".to_string()), 9);
        assert_eq!(solve_part1("{{<!!>},{<!!>},{<!!>},{<!!>}}".to_string()), 9);
        assert_eq!(solve_part1("{{<a!>},{<a!>},{<a!>},{<ab>}}".to_string()), 3);
    }

    #[test]
    fn test_part2() {
        assert_eq!(solve_part2("<>".to_string()), 0);
        assert_eq!(solve_part2("<random characters>".to_string()), 17);
        assert_eq!(solve_part2("<<<<>".to_string()), 3);
        assert_eq!(solve_part2("<{!>}>".to_string()), 2);
        assert_eq!(solve_part2("<!!>".to_string()), 0);
        assert_eq!(solve_part2("<!!!>>".to_string()), 0);
        assert_eq!(solve_part2("<{o\"i!a,<{i<a>".to_string()), 10);
    }
}
