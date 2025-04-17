use std::{collections::HashSet, io::{self, Write}};

// 1,1,1,2  3
// 1,2
// 1,1,1

pub fn combination_sum2(mut candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    candidates.sort_unstable();
    
    let mut results = Vec::new();

    fn backtrack(
        mut candidates: &[i32], 
        target: i32,
        mut sum: i32,
        path: &mut Vec<i32>,
        results: &mut Vec<Vec<i32>>,
    ) {
        if sum == target {
            results.push(path.clone());
            return;
        }

        if sum > target || candidates.is_empty() {
            return;
        }

        let value = candidates[0];

        sum += value;
        path.push(value);
        backtrack(&candidates[1..], target, sum, path, results);

        sum -= value;
        path.pop();

        // prevent dupes
        candidates = &candidates[1..];
        while !candidates.is_empty() && candidates[0] == value {
            candidates = &candidates[1..];
        }
        backtrack(candidates, target, sum, path, results);
    }

    backtrack(&candidates, target,0, &mut vec![], &mut results);
    results
}


fn main() -> io::Result<()> {
    println!("Enter args for combinaiton_sum2(candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>>");
    io::stdout().flush()?;

    let (candidates, target) = read_args()?;
    let res = combination_sum2(candidates, target);

    println!("Result: {:?}", res);
    io::stdout().flush()?;
    Ok(())
}

fn read_args() -> io::Result<(Vec<i32>, i32)> {
    let mut input = String::new();
    io::stdin().read_line(&mut input)?;

    let mut parts = input.split_whitespace();
    let candidates_str = parts
        .next()
        .ok_or_else(|| io::Error::new(io::ErrorKind::InvalidInput, "missing candidates"))?;
    let target_str = parts
        .next()
        .ok_or_else(|| io::Error::new(io::ErrorKind::InvalidInput, "missing target"))?;

    let candidates = candidates_str
        .split(",")
        .map(|s| {
            s.parse::<i32>().map_err(|e| io::Error::new(io::ErrorKind::InvalidInput, e))
        })
        .collect::<Result<Vec<_>, _>>()?;

    let target = target_str
        .parse::<i32>()
        .map_err(|e| io::Error::new(io::ErrorKind::InvalidInput, e))?;

    Ok((candidates, target))
}

/*
40. Combination Sum II
Medium
Topics
Companies

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

 

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]

 

Constraints:

    1 <= candidates.length <= 100
    1 <= candidates[i] <= 50
    1 <= target <= 30
*/
