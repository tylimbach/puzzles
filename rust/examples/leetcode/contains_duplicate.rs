use std::collections::HashSet;

fn contains_duplicate(nums: Vec<i32>) -> bool {
    let mut set = HashSet::new();
    for num in nums {
        if !set.insert(num) {
            return true;
        }
    }

    false
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(contains_duplicate(vec![1, 2, 3]), false);
    }

    #[test]
    fn test_2() {
        assert_eq!(contains_duplicate(vec![1, 2, 3, 3]), true);
    }
}

fn main() {}

