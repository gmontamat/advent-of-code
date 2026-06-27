use aoc2017::read_inputs;

fn solve_part1(spreadsheet: Vec<String>) -> i32 {
    let rows = spreadsheet.len();
    let mut checksum: i32 = 0;
    for i in 0..rows {
        let row: Vec<i32> = spreadsheet[i]
                .split_whitespace()
                .map(|n| n.parse().unwrap())
                .collect();
        checksum += *row.iter().max().unwrap();
        checksum -= *row.iter().min().unwrap();
    }
    checksum
}

fn solve_part2(spreadsheet: Vec<String>) -> i32 {
    let rows = spreadsheet.len();
    let mut checksum: i32 = 0;
    for i in 0..rows {
        let row: Vec<i32> = spreadsheet[i]
                .split_whitespace()
                .map(|n| n.parse().unwrap())
                .collect();
        let nums = row.len();
        'outer: for p in 0..nums {
            for q in 0..nums {
                if p == q {continue;}
                if row[p] >= row[q] {
                    if row[p] % row[q] == 0 {
                        checksum += row[p] / row[q];
                        break 'outer;
                    }
                } else {
                    if row[q] % row[p] == 0 {
                        checksum += row[q] / row[p];
                        break 'outer;
                    }
                }
            }
        }
    }
    checksum
}

fn main() {
    let spreadsheet = read_inputs(2);
    println!("Part 1: {}", solve_part1(spreadsheet.clone()));
    println!("Part 2: {}", solve_part2(spreadsheet));
}

#[cfg(test)]
mod tests {
    use super::*;
    use aoc2017::read_examples;
    use aoc2017::read_examples_file;

    #[test]
    fn test_part1() {
        let spreadsheet = read_examples(2);
        assert_eq!(solve_part1(spreadsheet), 18);
    }

    #[test]
    fn test_part2() {
        let spreadsheet = read_examples_file("day02p2");
        assert_eq!(solve_part2(spreadsheet), 9);
    }
}
