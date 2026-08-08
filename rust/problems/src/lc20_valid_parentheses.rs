//! [LeetCode 20: Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)

pub fn is_valid(s: String) -> bool {
    let mut openings: Vec<u8> = Vec::with_capacity(s.len());
    for c in s.chars() {
        match c {
            '(' | '{' | '[' => openings.push(c as u8),
            closing => {
                let expected_opening = match closing {
                    ')' => '(' as u8,
                    '}' => '{' as u8,
                    ']' => '[' as u8,
                    _ => unreachable!(),
                };
                if openings.pop() != Some(expected_opening) {
                    return false;
                }
            }
        }
    }
    openings.is_empty()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        assert!(is_valid("".to_string()));
        assert!(is_valid("()".to_string()));
        assert!(is_valid("{}".to_string()));
        assert!(is_valid("[]".to_string()));
        assert!(is_valid("()[]{}".to_string()));
        assert!(is_valid("(())".to_string()));
        assert!(is_valid("([{}])".to_string()));
        assert!(is_valid("([{}[]])".to_string()));

        assert!(!is_valid("(".to_string()));
        assert!(!is_valid(")".to_string()));
        assert!(!is_valid(")(".to_string()));
        assert!(!is_valid("(]".to_string()));
        assert!(!is_valid("()(".to_string()));
        assert!(!is_valid("())".to_string()));
        assert!(!is_valid("(()[))".to_string()));
        assert!(!is_valid("(()])".to_string()));
    }
}
