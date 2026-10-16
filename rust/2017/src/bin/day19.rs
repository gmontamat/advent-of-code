use aoc2017::read_inputs_no_trim;

fn solve_part1(input_map: Vec<String>) -> String {
    let mut map: Vec<Vec<char>> = Vec::new();
    let mut orientation = 0;  // 0: down, 1: up, 2: right, 3: left
    let mut x = 0;
    let mut y = 0;
    let mut text: String = String::new();
    for row in input_map {
        map.push(row.chars().collect());
    }
    // retrieve starting position
    loop {
        if map[y][x] == '|' {
            break;
        }
        x += 1;
    }
    // follow path
    loop {
        if map[y][x].is_alphabetic() {
            text.push(map[y][x]);
        }
        if orientation == 0 {
            // going down
            if y + 1 < map.len() && map[y + 1][x] != ' ' {
                y += 1;
                continue;
            } else {
                if x + 1 < map[y].len() && map[y][x + 1] != ' ' {
                    x += 1;
                    orientation = 2;
                    continue;
                } else if x >= 1 && map[y][x - 1] != ' ' {
                    x -= 1;
                    orientation = 3;
                    continue;
                } else {
                    break;
                }
            }
        } else if orientation == 1 {
            // going up
            if y >= 1 && map[y - 1][x] != ' ' {
                y -= 1;
                continue;
            } else {
                if x + 1 < map[y].len() && map[y][x + 1] != ' ' {
                    x += 1;
                    orientation = 2;
                    continue;
                } else if x >= 1 && map[y][x - 1] != ' ' {
                    x -= 1;
                    orientation = 3;
                    continue;
                } else {
                    break;
                }
            }
        } else if orientation == 2 {
            // going right
            if x + 1 < map[y].len() && map[y][x + 1] != ' ' {
                x += 1;
                continue;
            } else {
                if y + 1 < map.len() && map[y + 1][x] != ' ' {
                    y += 1;
                    orientation = 0;
                    continue;
                } else if y >= 1 && map[y - 1][x] != ' ' {
                    y -= 1;
                    orientation = 1;
                    continue;
                } else {
                    break;
                }
            }
        } else if orientation == 3 {
            // going down
            if x >= 1 && map[y][x - 1] != ' ' {
                x -= 1;
                continue;
            } else {
                if y + 1 < map.len() && map[y + 1][x] != ' ' {
                    y += 1;
                    orientation = 0;
                    continue;
                } else if y >= 1 && map[y - 1][x] != ' ' {
                    y -= 1;
                    orientation = 1;
                    continue;
                } else {
                    break;
                }
            }
        }
    }
    text
}

fn solve_part2(input_map: Vec<String>) -> i32 {
    let mut map: Vec<Vec<char>> = Vec::new();
    let mut orientation = 0;  // 0: down, 1: up, 2: right, 3: left
    let mut x = 0;
    let mut y = 0;
    let mut steps: i32 = 0;
    for row in input_map {
        map.push(row.chars().collect());
    }
    // retrieve starting position
    loop {
        if map[y][x] == '|' {
            break;
        }
        x += 1;
    }
    // follow path
    loop {
        steps += 1;
        if orientation == 0 {
            // going down
            if y + 1 < map.len() && map[y + 1][x] != ' ' {
                y += 1;
                continue;
            } else {
                if x + 1 < map[y].len() && map[y][x + 1] != ' ' {
                    x += 1;
                    orientation = 2;
                    continue;
                } else if x >= 1 && map[y][x - 1] != ' ' {
                    x -= 1;
                    orientation = 3;
                    continue;
                } else {
                    break;
                }
            }
        } else if orientation == 1 {
            // going up
            if y >= 1 && map[y - 1][x] != ' ' {
                y -= 1;
                continue;
            } else {
                if x + 1 < map[y].len() && map[y][x + 1] != ' ' {
                    x += 1;
                    orientation = 2;
                    continue;
                } else if x >= 1 && map[y][x - 1] != ' ' {
                    x -= 1;
                    orientation = 3;
                    continue;
                } else {
                    break;
                }
            }
        } else if orientation == 2 {
            // going right
            if x + 1 < map[y].len() && map[y][x + 1] != ' ' {
                x += 1;
                continue;
            } else {
                if y + 1 < map.len() && map[y + 1][x] != ' ' {
                    y += 1;
                    orientation = 0;
                    continue;
                } else if y >= 1 && map[y - 1][x] != ' ' {
                    y -= 1;
                    orientation = 1;
                    continue;
                } else {
                    break;
                }
            }
        } else if orientation == 3 {
            // going down
            if x >= 1 && map[y][x - 1] != ' ' {
                x -= 1;
                continue;
            } else {
                if y + 1 < map.len() && map[y + 1][x] != ' ' {
                    y += 1;
                    orientation = 0;
                    continue;
                } else if y >= 1 && map[y - 1][x] != ' ' {
                    y -= 1;
                    orientation = 1;
                    continue;
                } else {
                    break;
                }
            }
        }
    }
    steps
}

fn main() {
    let input_map = read_inputs_no_trim(19);
    println!("Part 1: {}", solve_part1(input_map.clone()));
    println!("Part 2: {}", solve_part2(input_map));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples_no_trim;

    use super::*;

    #[test]
    fn test_part1() {
        let input_map = read_examples_no_trim(19);
        assert_eq!(solve_part1(input_map), "ABCDEF".to_string());
    }

    #[test]
    fn test_part2() {
        let input_map = read_examples_no_trim(19);
        assert_eq!(solve_part2(input_map), 38);
    }
}
