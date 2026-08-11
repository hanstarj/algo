//! [LeetCode 35: Search Insert Position](https://leetcode.com/problems/search-insert-position)
//!
//! Given a sorted array of distinct integers and a target value, return the index if the target is
//! found. If not, return the index where it would be if it were inserted in order.
//!
//! You must write an algorithm with `O(log n)` runtime complexity.
//!
//! # Example 1
//!
//! ```text
//! Input: nums = [1,3,5,6], target = 5
//! Output: 2
//! ```
//!
//! # Example 2
//!
//! ```text
//! Input: nums = [1,3,5,6], target = 2
//! Output: 1
//! ```
//!
//! # Example 3
//!
//! ```text
//! Input: nums = [1,3,5,6], target = 7
//! Output: 4
//! ```
//!
//! # Constraints
//!
//! - `1 <= nums.length <= 10^4`
//! - `-10^4 <= nums[i] <= 10^4`
//! - `nums` contains **distinct** values sorted in **ascending** order.
//! - `-10^4 <= target <= 10^4`

pub fn search_insert(nums: Vec<i32>, target: i32) -> i32 {
    // using built-ins:
    // match nums.binary_search(target) {
    //   Ok(i) | Err(i) => i as i32,
    // }
    //
    // manual:
    search_insert_inner(&nums, target) as i32
}

fn search_insert_inner(nums: &[i32], target: i32) -> usize {
    let mut begin = 0;
    let mut end = nums.len();

    while begin < end {
        let mid = (begin + end) / 2;
        if target < nums[mid] {
            end = mid;
        } else if target > nums[mid] {
            begin = mid + 1;
        } else {
            return mid;
        }
    }

    begin
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        assert_eq!(si(&[1], 0), 0);
        assert_eq!(si(&[1], 1), 0);
        assert_eq!(si(&[1], 2), 1);

        assert_eq!(si(&[1, 3, 5], 0), 0);
        assert_eq!(si(&[1, 3, 5], 1), 0);
        assert_eq!(si(&[1, 3, 5], 2), 1);
        assert_eq!(si(&[1, 3, 5], 3), 1);
        assert_eq!(si(&[1, 3, 5], 4), 2);
        assert_eq!(si(&[1, 3, 5], 5), 2);
        assert_eq!(si(&[1, 3, 5], 6), 3);

        assert_eq!(si(&[1, 3, 5, 7], 0), 0);
        assert_eq!(si(&[1, 3, 5, 7], 1), 0);
        assert_eq!(si(&[1, 3, 5, 7], 2), 1);
        assert_eq!(si(&[1, 3, 5, 7], 3), 1);
        assert_eq!(si(&[1, 3, 5, 7], 4), 2);
        assert_eq!(si(&[1, 3, 5, 7], 5), 2);
        assert_eq!(si(&[1, 3, 5, 7], 6), 3);
        assert_eq!(si(&[1, 3, 5, 7], 7), 3);
        assert_eq!(si(&[1, 3, 5, 7], 8), 4);
    }

    fn si(nums: &[i32], target: i32) -> i32 {
        search_insert(nums.into(), target)
    }
}
