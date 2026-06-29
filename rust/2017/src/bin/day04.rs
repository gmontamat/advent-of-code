use std::collections::HashSet;

use aoc2017::read_inputs;

fn solve_part1(passphrases: Vec<String>) -> i32 {
    let mut count = 0;
    for passphrase in passphrases {
        if is_valid(&passphrase) {
            count += 1;
        }
    }
    count
}

fn is_valid(passphrase: &str) -> bool {
    let mut dict = HashSet::new();

    let words: Vec<&str> = passphrase.split_whitespace().collect();

    for word in words {
        if dict.contains(word) {
            return false;
        }
        dict.insert(word);
    }
    true
}

fn solve_part2(passphrases: Vec<String>) -> i32 {
    let mut count = 0;
    for passphrase in passphrases {
        if is_valid_anagram(&passphrase) {
            count += 1;
        }
    }
    count
}

fn is_valid_anagram(passphrase: &str) -> bool {
    let mut dict = HashSet::new();

    let words: Vec<&str> = passphrase.split_whitespace().collect();

    for word in words {
        // trick: sort characters in word alphabetically so the
        // implemementation is almost the same as is_valid()
        let mut chars: Vec<char> = word.chars().collect();
        chars.sort_unstable();
        if dict.contains(&chars) {
            return false;
        }
        dict.insert(chars);
    }
    true
}

fn main() {
    let phrases: Vec<String> = read_inputs(4);
    println!("Part 1: {}", solve_part1(phrases.clone()));
    println!("Part 2: {}", solve_part2(phrases));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part1() {
        assert_eq!(is_valid("aa bb cc dd ee"), true);
        assert_eq!(is_valid("aa bb cc dd aa"), false);
        assert_eq!(is_valid("aa bb cc dd aaa"), true);
    }

    #[test]
    fn test_part2() {
        assert_eq!(is_valid_anagram("abcde fghij"), true);
        assert_eq!(is_valid_anagram("abcde xyz ecdab"), false);
        assert_eq!(is_valid_anagram("a ab abc abd abf abj"), true);
        assert_eq!(is_valid_anagram("iiii oiii ooii oooi oooo"), true);
        assert_eq!(is_valid_anagram("oiii ioii iioi iiio"), false);
    }
}
