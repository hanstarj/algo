//! [LeetCode 14: Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix)
//!
//! Write a function to find the longest common prefix string amongst an array of strings.
//!
//! If there is no common prefix, return an empty string `""`.
//!
//! # Example 1
//!
//! ```text
//! Input: strs = ["flower","flow","flight"]
//! Output: "fl"
//! ```
//!
//! # Example 2
//!
//! ```text
//! Input: strs = ["dog","racecar","car"]
//! Output: ""
//! Explanation: There is no common prefix among the input strings.
//! ```
//!
//! # Constraints
//!
//! - `1 <= strs.length <= 200`
//! - `0 <= strs[i].length <= 200`
//! - `strs[i]` consists of only lowercase English letters if it is non-empty.

pub fn longest_common_prefix(strs: Vec<String>) -> String {
    assert!(!strs.is_empty());
    let mut lcp = strs[0].clone();
    for s in strs[1..].iter() {
        let mut byte_len = 0;
        for (c, d) in lcp.chars().zip(s.chars()) {
            if c != d {
                break;
            }
            byte_len += c.len_utf8();
        }
        lcp.truncate(byte_len);
    }
    lcp
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        assert_eq!(lcp(&[""]), "".to_string());
        assert_eq!(lcp(&["", ""]), "".to_string());
        assert_eq!(lcp(&["apple"]), "apple".to_string());
        assert_eq!(lcp(&["apple", "banana"]), "".to_string());
        assert_eq!(lcp(&["apple", "apple"]), "apple".to_string());
        assert_eq!(lcp(&["apple", "application"]), "appl".to_string());
        assert_eq!(lcp(&["apple", "application", ""]), "".to_string());
    }

    fn lcp(strs: &[&str]) -> String {
        longest_common_prefix(strs.iter().map(ToString::to_string).collect::<Vec<_>>())
    }
}
