use std::collections::HashMap;

fn valid_anagram(s: String, t: String) -> bool {
    if s.len() != t.len() {
        return false;
    }

    let mut letters_set = HashMap::new();

    for ch in s.chars() {
        let value = letters_set.entry(ch).or_insert(0);
        *value = *value + 1;
    }

    for ch in t.chars() {
        if let Some(mut value) = letters_set.get_mut(&ch) {
            if *value == 0 {
                return false;
            }
            *value = *value - 1;
        } else {
            return false;
        }
    }

    letters_set.iter().all(|x| *x.1 == 0)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(
            valid_anagram("anagram".to_string(), "nagaram".to_string()),
            true
        );
    }

    #[test]
    fn test_2() {
        assert_eq!(valid_anagram("rat".to_string(), "car".to_string()), false);
    }
}

fn main() {}

