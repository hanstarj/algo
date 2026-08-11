//! [LeetCode 20: Valid Parentheses](https://leetcode.com/problems/valid-parentheses)
//!
//! Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`,
//! determine if the input string is valid.
//!
//! An input string is valid if:
//!
//! - Open brackets must be closed by the same type of brackets.
//! - Open brackets must be closed in the correct order.
//! - Every close bracket has a corresponding open bracket of the same type.
//!
//! # Example 1
//!
//! ```text
//! Input: s = "()"
//! Output: true
//! ```
//!
//! # Example 2
//!
//! ```text
//! Input: s = "()[]{}"
//! Output: true
//! ```
//!
//! # Example 3
//!
//! ```text
//! Input: s = "(]"
//! Output: false
//! ```
//!
//! # Example 4
//!
//! ```text
//! Input: s = "([])"
//! Output: true
//! ```
//!
//! # Example 5
//!
//! ```text
//! Input: s = "([)]"
//! Output: false
//! ```
//!
//! # Constraints
//!
//! - `1 <= s.length <= 10^4`
//! - `s` consists of parentheses only `'()[]{}'`.

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
