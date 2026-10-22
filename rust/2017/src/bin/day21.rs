use std::collections::HashMap;

use aoc2017::read_inputs;

fn patch_to_str(patch: Vec<Vec<char>>) -> String {
    patch.into_iter()
         .map(|row| row.into_iter().collect::<String>())
         .collect::<Vec<String>>()
         .join("/")
}

fn rotate_90_clockwise(matrix: &mut Vec<Vec<char>>) {
    let n = matrix.len();
    // Transpose
    for i in 0..n {
        for j in (i + 1)..n {
            let temp = matrix[i][j].clone();
            matrix[i][j] = matrix[j][i].clone();
            matrix[j][i] = temp;
        }
    }
    // Reverse each row
    for row in matrix.iter_mut() {
        row.reverse();
    }
}

fn flip_horizontal(matrix: &mut Vec<Vec<char>>) {
    for row in matrix.iter_mut() {
        row.reverse();
    }
}

fn match_rule(patch: &mut Vec<Vec<char>>, rulemap: &HashMap<String, Vec<Vec<char>>>) -> Vec<Vec<char>> {
    // println!("in: {}", &patch_to_str(patch.to_vec()));
    if rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        return rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec();
    }
    // rotate 90 in place
    rotate_90_clockwise( patch);
    if rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        return rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec();
    }
    // rotate 180 in place
    rotate_90_clockwise( patch);
    if rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        return rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec();
    }
    // rotate 270 in place
    rotate_90_clockwise( patch);
    if rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        return rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec();
    }
    // flipped
    rotate_90_clockwise( patch);
    flip_horizontal(patch);
    if rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        return rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec();
    }
    // flipped + 90
    rotate_90_clockwise(patch);
    if rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        return rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec();
    }
    // flipped + 180
    rotate_90_clockwise(patch);
    if rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        return rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec();
    }
    // flipped + 270
    rotate_90_clockwise(patch);
    if !rulemap.contains_key(&patch_to_str(patch.to_vec())) {
        println!("RULE NOT FOUND!");
        println!("{}", &patch_to_str(patch.to_vec()));
    }
    rulemap.get(&patch_to_str(patch.to_vec())).unwrap().to_vec()
}

fn parse_rules(rules: Vec<String>) -> HashMap<String, Vec<Vec<char>>> {
    let mut rulemap: HashMap<String, Vec<Vec<char>>> = HashMap::new();
    for rule in rules {
        let input = rule.split(" => ").nth(0).unwrap().to_string();
        let out: Vec<Vec<char>> = rule.split(" => ")
                                      .nth(1)
                                      .unwrap()
                                      .split("/")
                                      .map(|s| s.chars().collect())
                                      .collect();
        rulemap.insert(input, out);
    }
    rulemap
}

fn solve_part1(rules: Vec<String>, iterations: i32) -> i32 {
    // parse rules into hashmap
    let rulemap: HashMap<String, Vec<Vec<char>>> = parse_rules(rules);
    let mut image: Vec<Vec<char>> = Vec::new();
    image.push(['.', '#', '.'].to_vec());
    image.push(['.', '.', '#'].to_vec());
    image.push(['#', '#', '#'].to_vec());
    for _ in 0..iterations {
        let mut next_image: Vec<Vec<char>> = Vec::new();
        let size = image.len();
        if size % 2 == 0 {
            let next_size = size / 2 * 3;
            for _ in 0..next_size {
                next_image.push(Vec::new());
            }
            let mut row = 0;
            let mut row_next = 0;
            let mut col = 0;
            while row < size && col < size {
                // Grab patch
                let mut patch: Vec<Vec<char>> = Vec::new();
                for i in 0..2 {
                    patch.push(image[row + i][col..col+2].to_vec())
                }
                // find rule
                let matched = match_rule(&mut patch, &rulemap);
                // populate next_image
                for i in 0..3 {
                    next_image[row_next + i].extend(matched.iter().nth(i).unwrap());
                }
                // Advance to the next patch
                col += 2;
                if !(col < size) {
                    col = 0;
                    row += 2;
                    row_next += 3;
                }
            }
        } else if size % 3 == 0 {
            let next_size = size / 3 * 4;
            for _ in 0..next_size {
                next_image.push(Vec::new());
            }
            let mut row = 0;
            let mut row_next = 0;
            let mut col = 0;
            while row < size && col < size {
                // Grab patch
                let mut patch: Vec<Vec<char>> = Vec::new();
                for i in 0..3 {
                    patch.push(image[row + i][col..col+3].to_vec())
                }
                // find rule
                let matched = match_rule(&mut patch, &rulemap);
                // populate next_image
                for i in 0..4 {
                    next_image[row_next + i].extend(matched.iter().nth(i).unwrap());
                }
                // Advance to the next patch
                col += 3;
                if !(col < size) {
                    col = 0;
                    row += 3;
                    row_next += 4;
                }
            }
        }
        image = next_image.clone();
        // display
        // for i in 0..image.len() {
        //     println!("{:?}", image[i]);
        // }
        // println!("---")
    }
    let mut sum = 0;
    for i in 0..image.len() {
        for j in 0..image.len() {
            if image[i][j] == '#' {
                sum += 1;
            }
        }
    }
    sum
}

fn main() {
    let rules = read_inputs(21);
    println!("Part 1: {}", solve_part1(rules.clone(), 5));
    println!("Part 2: {}", solve_part1(rules, 18));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples;

    use super::*;

    #[test]
    fn test_part1() {
        let rules = read_examples(21);
        assert_eq!(solve_part1(rules, 2), 12);
    }
}
