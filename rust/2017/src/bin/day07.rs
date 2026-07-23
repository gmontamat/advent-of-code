use std::collections::HashMap;
use regex::Regex;

use aoc2017::read_inputs;

fn solve_part1(input: Vec<String>) -> String {
    // parse input
    let mut parents: HashMap<String, String> = HashMap::new();  // maps node -> parent
    // Complete all nodes
    for line in &input {
        let parts: Vec<&str> = line.split_whitespace().collect();
        parents.insert(parts[0].to_string(), "None".to_string());
    }
    // Assign parents
    for line in input {
        if !line.contains("->") {
            continue;
        }
        let parts: Vec<&str> = line.split_whitespace().collect();
        let parent = parts[0].to_string();
        let parts: Vec<&str> = line.split(" -> ").collect();
        let children: Vec<&str> = parts[1].split(", ").collect();
        for child in children {
            parents.insert(child.to_string(), parent.clone());
        }
    }
    // Find orphan
    for (child, parent) in parents {
        if parent == "None" {
            return child;
        }
    }
    String::from("None")
}

fn solve_part2(input: Vec<String>) -> i32 {
    let mut nodes: HashMap<String, Vec<String>> = HashMap::new();  // maps node -> children
    let mut weights: HashMap<String, i32> = HashMap::new();  // maps node -> weight
    // Parse node weights 
    let re = Regex::new(r"\((\d+)\)").unwrap();
    for line in &input {
        let parts: Vec<&str> = line.split_whitespace().collect();
        nodes.insert(parts[0].to_string(), Vec::new());
        if let Some(caps) = re.captures(line) {
            if let Ok(number) = caps[1].parse::<i32>() {
                weights.insert(parts[0].to_string(), number);
            }
        }
    }
    // Add children to each node
    for line in input {
        if !line.contains("->") {
            continue;
        }
        let line_parts: Vec<&str> = line.split_whitespace().collect();
        let parent = line_parts[0].to_string();
        let parts: Vec<&str> = line.split(" -> ").collect();
        let children: Vec<&str> = parts[1].split(", ").collect();
        for child in children {
            nodes.get_mut(&parent).unwrap().push(child.to_string());
        }
    }
    let original_weights = weights.clone();
    // Find node whose children are leaves
    loop {
        let mut update_nodes = false;
        let mut node_to_update = String::new();
        for (node, children) in &nodes {
            // does it have children?
            if nodes[node].len() == 0 {
                continue;
            }
            // are all its children leaves (childless)?
            let mut children_are_leaves: bool = true;
            for child in children {
                if nodes[child].len() > 0 {
                    children_are_leaves = false;
                    break;
                }
            }
            if !children_are_leaves {
                continue;
            }
            // println!("{node}");
            // check balance of leaves
            let mut frequencies: HashMap<i32, i32> = HashMap::new();
            for child in children {
                let weight = weights.get(child).unwrap().to_owned();
                *frequencies.entry(weight).or_insert(0) += 1;
            }
            // println!("{:?}", frequencies);
            if frequencies.len() > 1 {
                // we found the unbalanced tree!
                let mut improper_weight = 0;
                let mut proper_weight = 0;
                for (w, f) in frequencies {
                    if f > 1 {
                        proper_weight = w;
                    } else {
                        improper_weight = w;
                    }
                }
                for child in children {
                    if weights[child] == improper_weight {
                        return original_weights[child] + proper_weight - improper_weight;
                    }
                }
            } else {
                // branches are balanced!
                // 1) Reassign weights to parent
                let total_children_weight: i32 = children.iter()
                    .map(|child| weights[child])
                    .sum();
                *weights.get_mut(node).unwrap() += total_children_weight;
                // 2) Clear children on the nodes map
                update_nodes = true;
                node_to_update = node.clone();
                // break the for loop, releasing the borrow so we can update nodes[node]
                // removing all children from its vector
                break;
            }
        }
        if update_nodes {
            nodes.get_mut(&node_to_update).unwrap().clear();
        }
    }
}

fn main() {
    let input: Vec<String> = read_inputs(7);
    println!("Part 1: {}", solve_part1(input.clone()));
    println!("Part 2: {}", solve_part2(input));
}

#[cfg(test)]
mod tests {
    use super::*;

    use aoc2017::read_examples;

    #[test]
    fn test_part1() {
        let input = read_examples(7);
        assert_eq!(solve_part1(input), "tknk");
    }

    #[test]
    fn test_part2() {
        let input = read_examples(7);
        assert_eq!(solve_part2(input), 60);
    }
}
