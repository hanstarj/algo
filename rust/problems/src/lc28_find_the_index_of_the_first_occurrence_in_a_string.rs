//! [LeetCode 28: Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string)
//!
//! Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle`
//! in `haystack`, or `-1` if `needle` is not part of `haystack`.
//!
//! # Example 1
//!
//! ```text
//! Input: haystack = "sadbutsad", needle = "sad"
//! Output: 0
//! Explanation: "sad" occurs at index 0 and 6.
//! The first occurrence is at index 0, so we return 0.
//! ```
//!
//! # Example 2
//!
//! ```text
//! Input: haystack = "leetcode", needle = "leeto"
//! Output: -1
//! Explanation: "leeto" did not occur in "leetcode", so we return -1.
//! ```
//!
//! # Constraints
//!
//! - `1 <= haystack.length, needle.length <= 10^4`
//! - `haystack` and `needle` consist of only lowercase English characters.

pub fn str_str(haystack: String, needle: String) -> i32 {
    // using built-ins:
    // haystack.find(&needle).map_or(-1, |i| i as i32)
    //
    // manual:
    if haystack.len() >= needle.len() {
        for i in 0..(haystack.len() - needle.len() + 1) {
            if haystack[i..i + needle.len()] == needle {
                return i as i32;
            }
        }
    }

    -1
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        assert_eq!(str_str("apple".into(), "apple".into()), 0);
        assert_eq!(str_str("applebook".into(), "apple".into()), 0);
        assert_eq!(str_str("applebook".into(), "book".into()), 5);
        assert_eq!(str_str("applebookapple".into(), "apple".into()), 0);
        assert_eq!(str_str("applebookbook".into(), "book".into()), 5);
        assert_eq!(str_str("applebookbook".into(), "book".into()), 5);
        assert_eq!(str_str("applebababook".into(), "babo".into()), 7);
        assert_eq!(str_str("applebook".into(), "cat".into()), -1);
        assert_eq!(str_str("applebookcar".into(), "cat".into()), -1);
        assert_eq!(str_str("app".into(), "apple".into()), -1);
    }
}
