use std::fs;

pub fn read_input(day: u8) -> String {
    let path = format!("{}/inputs/day{:02}.txt", env!("CARGO_MANIFEST_DIR"), day);
    fs::read_to_string(&path)
        .unwrap_or_else(|_| panic!("Failed to read input file: {}", path))
        .trim()
        .to_string()
}

pub fn read_example(day: u8) -> String {
    let path = format!("{}/examples/day{:02}.txt", env!("CARGO_MANIFEST_DIR"), day);
    fs::read_to_string(&path)
        .unwrap_or_else(|_| panic!("Failed to read example file: {}", path))
        .trim()
        .to_string()
}

pub fn read_inputs(day: u8) -> Vec<String> {
    let path = format!("{}/inputs/day{:02}.txt", env!("CARGO_MANIFEST_DIR"), day);
    fs::read_to_string(&path)
        .unwrap_or_else(|_| panic!("Failed to read input file: {}", path))
        .lines()
        .map(|l| l.trim().to_string())
        .collect()
}

pub fn read_examples(day: u8) -> Vec<String> {
    let path = format!("{}/examples/day{:02}.txt", env!("CARGO_MANIFEST_DIR"), day);
    fs::read_to_string(&path)
        .unwrap_or_else(|_| panic!("Failed to read example file: {}", path))
        .lines()
        .map(|l| l.trim().to_string())
        .collect()
}
