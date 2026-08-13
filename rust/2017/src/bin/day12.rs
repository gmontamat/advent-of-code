use std::collections::{HashMap, HashSet};

use aoc2017::read_inputs;

fn dfs_visited(
    graph: &HashMap<i32, Vec<i32>>,
    visited: &mut HashSet<i32>,
    node: i32
) {
    visited.insert(node);

    for &neighbor in &graph[&node] {
        if !visited.contains(&neighbor) {
            dfs_visited(graph, visited, neighbor);
        }
    }
}

fn get_cc_size(graph: &HashMap<i32, Vec<i32>>, node: i32) -> i32 {
    let mut visited: HashSet<i32> = HashSet::new();
    dfs_visited(graph, &mut visited, node);
    visited.len() as i32
}

fn solve_part1(data: Vec<String>) -> i32 {
    // Build graph
    let mut graph: HashMap<i32, Vec<i32>> = HashMap::new();
    for row in data {
        let parts: Vec<String> = row.split(" <-> ")
                                    .map(|s| s.to_string())
                                    .collect();
        let node: i32 = parts[0].parse().unwrap();
        let neighbors: Vec<i32> = parts[1].split(", ")
                                          .map(|s: &str| s.parse::<i32>()
                                          .unwrap())
                                          .collect();
        graph.insert(node, neighbors);
    }
    // in graph theory: connected component
    get_cc_size(&graph, 0)
}

fn count_ccs(graph: &HashMap<i32, Vec<i32>>) -> i32 {
    let mut visited: HashSet<i32> = HashSet::new();
    let mut groups = 0;
    loop {
        let mut reduced_graph = graph.clone();
        for node in &visited {
            reduced_graph.remove(&node);
        }
        if reduced_graph.len() == 0 {
            // all connected components (groups) found
            break;
        }
        let node = *reduced_graph.keys().next().unwrap();
        dfs_visited(graph, &mut visited, node);
        groups += 1;
    }
    groups
}

fn solve_part2(data: Vec<String>) -> i32 {
    // Build graph
    let mut graph: HashMap<i32, Vec<i32>> = HashMap::new();
    for row in data {
        let parts: Vec<String> = row.split(" <-> ")
                                    .map(|s| s.to_string())
                                    .collect();
        let node: i32 = parts[0].parse().unwrap();
        let neighbors: Vec<i32> = parts[1].split(", ")
                                          .map(|s: &str| s.parse::<i32>()
                                          .unwrap())
                                          .collect();
        graph.insert(node, neighbors);
    }
    // in graph theory: count all connected components of a graph
    count_ccs(&graph)
}

fn main() {
    let data = read_inputs(12);
    println!("Part 1: {}", solve_part1(data.clone()));
    println!("Part 2: {}", solve_part2(data));
}

#[cfg(test)]
mod tests {
    use super::*;

    use aoc2017::read_examples;

    #[test]
    fn test_part1() {
        let data = read_examples(12);
        assert_eq!(solve_part1(data), 6);
    }

    #[test]
    fn test_part2() {
        let data = read_examples(12);
        assert_eq!(solve_part2(data), 2);
    }
}
