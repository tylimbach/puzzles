/*
lc 3272

brute force
1. Iterate over each integer 100 - 999
2. Find all k-palindromic values
3. Sum unique combination of digits (exclude zeros, ignore dupes)

maybe we can shortcut palindromic?

*/

use std::collections::HashSet;
use std::io::{self, Write};

pub fn count_good_integers(n: i32, k: i32) -> i64 {
    let mut good_ints = HashSet::<i32>::new();

    let palindromes = get_palindromes(n);
    println!("Palindromes: {:?}", palindromes);
    for v in palindromes {
        let num: i32 = v.parse().expect("Failed to parse integer");
        if !good_ints.contains(&num) && num % k == 0 {
            good_ints.extend(get_permutations(v));
        }
    }

    good_ints.len() as i64
}

pub fn get_palindromes(n: i32) -> Vec<String> {
    let mut results = Vec::new();
    let mut current = Vec::with_capacity(n as usize);

    fn backtrack(current: &mut Vec<i32>, results: &mut Vec<String>, n: usize) {
        if current.len() > ((n - 1) / 2) {
            let mut expanded = current.clone();

            let is_odd = n % 2 == 1;
            let skip = if is_odd { 1 } else { 0 };
            expanded.extend(current.iter().rev().skip(skip));

            let string_expanded = expanded.iter().map(|&x| x.to_string()).collect::<String>();
            results.push(string_expanded);
            return;
        }

        let start = if current.is_empty() {1} else {0};
        for x in start..=9 {
            current.push(x);
            backtrack(current, results, n);
            current.pop();
        }
    }

    backtrack(&mut current, &mut results, n as usize);
    results
}

pub fn is_palindrome(v: i32) -> bool {
    let digits: Vec<char> = v.to_string().chars().collect();
    
    for i in 0..(digits.len() / 2) {
        if digits[i] != digits[digits.len() - (i + 1)] {
            return false
        }
    }

    true
}

pub fn get_permutations(v: String) -> Vec<i32>  {
    let mut digits: Vec<char> = v.chars().collect();
    digits.sort_unstable();
    
    let mut results = Vec::new();
    let mut used = vec![false; digits.len()];
    let mut current = Vec::with_capacity(digits.len());

    fn backtrack(
        digits: &[char],
        used: &mut Vec<bool>,
        current: &mut Vec<char>,
        results: &mut Vec<i32>,
    ) {
        if current.len() == digits.len() {
            let num = current.iter().collect::<String>().parse::<i32>().unwrap();
            results.push(num);
            return;
        }

        for i in 0..digits.len() {
            if used[i] {
                continue;
            }
            if i > 0 && digits[i] == digits[i - 1] && !used[i - 1] {
                continue;
            }
            if current.is_empty() && digits[i] == '0' {
                continue;
            }

            used[i] = true;
            current.push(digits[i]);
            backtrack(digits, used, current, results);
            current.pop();
            used[i] = false;
        }
    }

    backtrack(&digits, &mut used, &mut current, &mut results);
    results
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(two_sum(vec![2, 7, 11, 15], 9), vec![2, 7]);
    }
}

fn main() {
    println!("Enter args for count_good_integers(n: u32, k: i32) -> i64");
    io::stdout().flush().unwrap();

    let (n, k) = read_two_ints();
    let c = count_good_integers(n, k);
    println!("Result: {}", c);
}

fn read_two_ints() -> (i32, i32) {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let mut parts = input.split_whitespace();

    let n = parts.next().expect("Missing value for n").parse::<i32>().expect("Invalid value for n");
    let k = parts.next().expect("Missing value for k").parse::<i32>().expect("Invalid value for k");

    (n, k)
}


/*
You are given two positive integers n and k.

An integer x is called k-palindromic if:

    x is a 

    .
    x is divisible by k.

An integer is called good if its digits can be rearranged to form a k-palindromic integer. For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a k-palindromic integer.

Return the count of good integers containing n digits.

Note that any integer must not have leading zeros, neither before nor after rearrangement. For example, 1010 cannot be rearranged to form 101.

 

Example 1:

Input: n = 3, k = 5

Output: 27

Explanation:

Some of the good integers are:

    551 because it can be rearranged to form 515.
    525 because it is already k-palindromic.

Example 2:

Input: n = 1, k = 4

Output: 2

Explanation:

The two good integers are 4 and 8.

Example 3:

Input: n = 5, k = 6

Output: 2468

 

Constraints:

    1 <= n <= 10
    1 <= k <= 9
*/
