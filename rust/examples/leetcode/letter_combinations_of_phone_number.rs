use std::{collections::HashMap, io::{self, Write}};

pub fn letter_combinations(digits: String) -> Vec<String> {
    if digits.is_empty() {
        return vec![];
    }

    let keymap = HashMap::<char,Vec<char>>::from([
        ('2', vec!['a','b','c']),
        ('3', vec!['d','e','f']),
        ('4', vec!['g','h','i']),
        ('5', vec!['j','k','l']),
        ('6', vec!['m','n','o']),
        ('7', vec!['p','q','r','s']),
        ('8', vec!['t','u','v']),
        ('9', vec!['w','x','y','z']),
    ]);

    fn backtrack(path: &mut String, digits_left: &mut String, results: &mut Vec<String>, keymap: &HashMap::<char, Vec<char>>) {
        if digits_left.is_empty() {
            results.push(path.clone());
            return;
        } 

        let removed_char = digits_left.remove(0);
        if let Some(candidates) = keymap.get(&removed_char) {
            for candidate in candidates {
                path.push(*candidate);
                backtrack(path, digits_left, results, keymap);
                path.pop();
            }
        }
        digits_left.insert(0, removed_char);
    }

    let mut results = vec![];
    backtrack(&mut String::with_capacity(digits.len()), &mut digits.clone(), &mut results, &keymap);
    results
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(letter_combinations("".to_string()), Vec::<String>::new());
    }

    #[test]
    fn test_2() {
        assert_eq!(letter_combinations("23".to_string()), vec!["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]);
    }
}

fn main() -> io::Result<()> {
    println!("Enter args for letter_combinations(digits: String) -> Vec<String>");
    io::stdout().flush()?;

    let digits = read_args()?;
    println!("Inputs: {:?}", digits);
    let res = letter_combinations(digits);

    println!("Result: {:?}", res);
    io::stdout().flush()?;
    Ok(())
}

fn read_args() -> io::Result<String> {
    let mut inputs = String::new();
    io::stdin().read_line(&mut inputs)?; 
    Ok(inputs.trim().to_string())
}

/*
17. Letter Combinations of a Phone Number
Medium
Topics
Companies

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

 

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:

Input: digits = ""
Output: []

Example 3:

Input: digits = "2"
Output: ["a","b","c"]

 

Constraints:

    0 <= digits.length <= 4
    digits[i] is a digit in the range ['2', '9'].


*/
