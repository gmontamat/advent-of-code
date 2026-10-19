use std::{collections::HashMap, i32::MAX};
use scanf::sscanf;

use aoc2017::read_inputs;

fn solve_part1(particles: Vec<String>) -> i32 {
    // In the long run, lowest (absoulte) "manhattan" acceleration stays closer
    // issue: we need to break ties
    let mut min_acc: i32 = MAX;
    let mut min_dist: i32 = MAX;
    let mut closest = 0;
    let mut ctr = 0;
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut z: i32 = 0;
    let mut vx: i32 = 0;
    let mut vy: i32 = 0;
    let mut vz: i32 = 0;
    let mut ax: i32 = 0;
    let mut ay: i32 = 0;
    let mut az: i32 = 0;
    // find closest items
    for particle in particles.clone() {
        let input: &str = &particle;
        sscanf!(input, "p=<{x},{y},{z}>, v=<{vx},{vy},{vz}>, a=<{ax},{ay},{az}>").unwrap();
        if ax.abs() + ay.abs() + az.abs() < min_acc {
            min_acc = ax.abs() + ay.abs() + az.abs();
        }
    }
    // break ties
    for particle in particles {
        let input: &str = &particle;
        sscanf!(input, "p=<{x},{y},{z}>, v=<{vx},{vy},{vz}>, a=<{ax},{ay},{az}>").unwrap();
        if ax.abs() + ay.abs() + az.abs() == min_acc {
            // simulate this particle
            for _ in 1..10_000 {
                vx += ax;
                vy += ay;
                vz += az;
                x += vx;
                y += vy;
                z += vz;
            }
            if x.abs() + y.abs() + z.abs() < min_dist {
                min_dist = x.abs() + y.abs() + z.abs();
                closest = ctr;
            }
            // println!("{ctr} p=<{x},{y},{z}>, v=<{vx},{vy},{vz}>, a=<{ax},{ay},{az}>")
        }
        ctr += 1;
    }
    closest
}

fn solve_part2(particles: Vec<String>) -> i32 {
    // bruteforce approach: simulate all
    let mut spaces: HashMap<[i32; 3], i32> = HashMap::new();
    let mut position: HashMap<i32, [i32; 3]> = HashMap::new();
    let mut velocity: HashMap<i32, [i32; 3]> = HashMap::new();
    let mut accel: HashMap<i32, [i32; 3]> = HashMap::new();
    // Parse into HashMap
    let mut ctr = 0;
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut z: i32 = 0;
    let mut vx: i32 = 0;
    let mut vy: i32 = 0;
    let mut vz: i32 = 0;
    let mut ax: i32 = 0;
    let mut ay: i32 = 0;
    let mut az: i32 = 0;
    for particle in particles {
        let input: &str = &particle;
        sscanf!(input, "p=<{x},{y},{z}>, v=<{vx},{vy},{vz}>, a=<{ax},{ay},{az}>").unwrap();
        position.insert(ctr, [x, y, z]);
        velocity.insert(ctr, [vx, vy, vz]);
        accel.insert(ctr, [ax, ay, az]);
        ctr += 1;
    }
    // Simulate
    for _ in 1..1_000 {
        // Run collision detector
        spaces.clear();
        for (idx, p) in position.clone() {
            if spaces.contains_key(&p) {
                // collision found, delete items
                let idx_old = spaces.get(&p).unwrap();
                position.remove(idx_old);
                velocity.remove(idx_old);
                accel.remove(idx_old);
                position.remove(&idx);
                velocity.remove(&idx);
                accel.remove(&idx);
            }
            spaces.insert(p, idx);
        }
        // Simulate step
        for (idx, p) in position.clone() {
            [x, y, z] = p;
            [vx, vy, vz] = *velocity.get(&idx).unwrap();
            [ax, ay, az] = *accel.get(&idx).unwrap();
            vx += ax;
            vy += ay;
            vz += az;
            x += vx;
            y += vy;
            z += vz;
            position.insert(idx, [x, y, z]);
            velocity.insert(idx, [vx, vy, vz]);
        }
    }
    position.len().try_into().unwrap()
}

fn main() {
    let particles = read_inputs(20);
    println!("Part 1: {}", solve_part1(particles.clone()));
    println!("Part 2: {}", solve_part2(particles));
}

#[cfg(test)]
mod tests {
    use aoc2017::read_examples_file;

    use super::*;

    #[test]
    fn test_part1() {
        let particles = read_examples_file("day20p1");
        assert_eq!(solve_part1(particles), 0);
    }

    #[test]
    fn test_part2() {
        let particles = read_examples_file("day20p2");
        assert_eq!(solve_part2(particles), 1);
    }
}
