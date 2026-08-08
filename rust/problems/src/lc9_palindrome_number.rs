//! [LeetCode 9: Palindrome Number](https://leetcode.com/problems/palindrome-number/)

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
