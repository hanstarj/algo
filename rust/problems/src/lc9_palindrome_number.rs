//! [LeetCode 9: Palindrome Number](https://leetcode.com/problems/palindrome-number)
//!
//! Given an integer `x`, return `true` if `x` is a **palindrome**, and `false` otherwise.
//!
//! # Example 1
//!
//! ```text
//! Input: x = 121
//! Output: true
//! Explanation: 121 reads as 121 from left to right and from right to left.
//! ```
//!
//! # Example 2
//!
//! ```text
//! Input: x = -121
//! Output: false
//! Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
//! ```
//!
//! # Example 3
//!
//! ```text
//! Input: x = 10
//! Output: false
//! Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
//! ```
//!
//! # Constraints
//!
//! - `-2^31 <= x <= 2^31 - 1`
//!
//! # Follow-up
//!
//! Could you solve it without converting the integer to a string?

pub fn is_palindrome(mut x: i32) -> bool {
    if x < 0 {
        return false;
    }
    if x % 10 == 0 {
        return x == 0;
    }

    let mut reverted = 0;
    while reverted < x {
        reverted = reverted * 10 + x % 10;
        x /= 10;
    }

    reverted == x || reverted / 10 == x
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_palindrome() {
        assert!(!is_palindrome(-1), "negative number");
        assert!(is_palindrome(0));
        assert!(is_palindrome(1));
        assert!(!is_palindrome(10), "end with zero");
        assert!(is_palindrome(101));
        assert!(is_palindrome(1001));
        assert!(is_palindrome(121), "increasing half, odd digits");
        assert!(is_palindrome(212), "decreasing half, odd digits");
        assert!(!is_palindrome(213));
        assert!(is_palindrome(1221), "increasing half, even digits");
        assert!(is_palindrome(2112), "decreasing half, even digits");
        assert!(!is_palindrome(2122));
        assert!(!is_palindrome(2111));
        assert!(!is_palindrome(i32::MAX), "overflow safety");
        assert!(!is_palindrome(i32::MIN), "underflow safety");
        assert!(is_palindrome(2147447412), "largest palindrome");
    }
}
