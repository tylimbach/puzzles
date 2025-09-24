fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    let mut sorted_nums = nums.clone();
    sorted_nums.sort_unstable();

    let mut l = 0;
    let mut r = sorted_nums.len() - 1;

    while l != r {
        let sum = sorted_nums[l] + sorted_nums[r];
        if target > sum {
            l += 1;
        } else if sum > target {
            r += 1;
        } else {
            return vec![sorted_nums[l], sorted_nums[r]];
        }
    }

    // the problem says exactly 1 solution exists
    unreachable!();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(two_sum(vec![2, 7, 11, 15], 9), vec![2, 7]);
    }
}

fn main() {}
