use std::collections::{HashMap, HashSet};

// iterate over pairs, lookup complement of sum, cache 2sums
// time complexity: n^2
// space complexity: n^2

fn four_sum(mut nums: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    if nums.len() < 4 {
        return vec![];
    }

    let mut results = HashSet::new();
    let mut sorted_nums: Vec<i64> = nums.into_iter().map(|x| x as i64).collect();
    let mut cached_2sums: HashMap<i64, Vec<(usize, usize)>> = HashMap::new();
    sorted_nums.sort_unstable();

    for i in 0..sorted_nums.len() {
        if i > 1 && sorted_nums[i] == sorted_nums[i - 2] {
            continue;
        }
        for j in i + 1..sorted_nums.len() {
            if j > 1 && sorted_nums[j] == sorted_nums[j - 2] {
                continue;
            }
            let sum = sorted_nums[i] + sorted_nums[j];
            let comp_target = target as i64 - sum;

            // append the result if we find the complement
            if let Some(pairs) = cached_2sums.get(&comp_target) {
                for &(k, l) in pairs.iter() {
                    if is_unique_unordered((k, l), (i, j)) {
                        let mut x = vec![
                            sorted_nums[i] as i32,
                            sorted_nums[j] as i32,
                            sorted_nums[k] as i32,
                            sorted_nums[l] as i32,
                        ];
                        x.sort();
                        _ = results.insert(x);
                    }
                }
            }

            // update 2sum cache
            cached_2sums
                .entry(sum)
                .or_insert_with(Vec::new)
                .push((i, j));
        }
    }

    results.into_iter().collect::<Vec<Vec<i32>>>()
}

fn is_unique_unordered<T: PartialEq>(pair1: (T, T), pair2: (T, T)) -> bool {
    pair1.0 != pair2.0 && pair1.0 != pair2.1 && pair1.1 != pair2.0 && pair1.1 != pair2.1
}

fn main() {
    let nums = vec![1000000000, 1000000000, 1000000000, 1000000000];
    print!("{:?}", four_sum(nums, -294967296));
}

