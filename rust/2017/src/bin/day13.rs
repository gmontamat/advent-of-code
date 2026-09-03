use std::collections::HashMap;

use aoc2017::read_inputs;

fn solve_part1(data: Vec<String>) -> i32 {
    let mut layers: HashMap<i32, i32> = HashMap::new();
    let mut firewall: HashMap<i32, i32> = HashMap::new();
    let mut direction: HashMap<i32, i32> = HashMap::new();
    for row in data {
        let row: Vec<String> = row.split(": ")
                                  .map(|s| s.to_string())
                                  .collect();
        let layer: i32 = row[0].parse().unwrap();
        let depth: i32 = row[1].parse().unwrap();
        layers.insert(layer, depth);
        firewall.insert(layer, 0);
        direction.insert(layer, 1);
    }
    let size: &i32 = layers.keys().max().unwrap();
    // Simulate crossing firewall
    let mut total: i32 = 0;
    for position in 0..size+1 {
        if firewall.contains_key(&position) {
            if *firewall.get(&position).unwrap() == 0 {
                total += position * layers.get(&position).unwrap_or(&0);
            }
        }
        // Update firewall location
        for i in firewall.clone().keys() {
            let firewall_position = *firewall.get(&i).unwrap();
            if firewall_position == *layers.get(i).unwrap() - 1 {
                direction.insert(*i, -1);  // reached layer depth
            } else if firewall_position == 0 {
                direction.insert(*i, 1);   // reached layer start
            }
            firewall.insert(*i, firewall_position + *direction.get(&i).unwrap());
        }
        // println!("{:#?}", firewall);
    }
    total
}

fn solve_part2(data: Vec<String>) -> i32 {
    let mut layers: HashMap<i32, i32> = HashMap::new();
    let mut firewall_start: HashMap<i32, i32> = HashMap::new();
    let mut direction_start: HashMap<i32, i32> = HashMap::new();
    for row in data {
        let row: Vec<String> = row.split(": ")
                                  .map(|s| s.to_string())
                                  .collect();
        let layer: i32 = row[0].parse().unwrap();
        let depth: i32 = row[1].parse().unwrap();
        layers.insert(layer, depth);
        firewall_start.insert(layer, 0);
        direction_start.insert(layer, 1);
    }
    let size: &i32 = layers.keys().max().unwrap();
    // Simulate crossing firewall
    let mut delay = 0;
    loop {
        let mut firewall = firewall_start.clone();
        let mut direction = direction_start.clone();
        for _ in 0..delay {
            // Update firewall location
            for i in firewall.clone().keys() {
                let firewall_position = *firewall.get(&i).unwrap();
                if firewall_position == *layers.get(i).unwrap() - 1 {
                    direction.insert(*i, -1);  // reached layer depth
                } else if firewall_position == 0 {
                    direction.insert(*i, 1);   // reached layer start
                }
                firewall.insert(*i, firewall_position + *direction.get(&i).unwrap());
            }
        }
        for position in 0..size+1 {
            if firewall.contains_key(&position) {
                if *firewall.get(&position).unwrap() == 0 {
                    break;
                }
            }
            // Update firewall location
            for i in firewall.clone().keys() {
                let firewall_position = *firewall.get(&i).unwrap();
                if firewall_position == *layers.get(i).unwrap() - 1 {
                    direction.insert(*i, -1);  // reached layer depth
                } else if firewall_position == 0 {
                    direction.insert(*i, 1);   // reached layer start
                }
                firewall.insert(*i, firewall_position + *direction.get(&i).unwrap());
            }
            if position == *size {
                return delay;
            }
        }
        delay += 1;
    }
}

fn main() {
    let data = read_inputs(13);
    println!("Part 1: {}", solve_part1(data.clone()));
    println!("Part 2: {}", solve_part2(data));
}

#[cfg(test)]
mod tests {
    use super::*;

    use aoc2017::read_examples;

    #[test]
    fn test_part1() {
        let data = read_examples(13);
        assert_eq!(solve_part1(data), 24);
    }

    #[test]
    fn test_part2() {
        let data = read_examples(13);
        assert_eq!(solve_part2(data), 10);
    }
}
