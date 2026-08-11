//! [LeetCode 26: Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array)
//!
//! Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates
//! **in-place** such that each unique element appears only **once**. The **relative order** of the
//! elements should be kept the **same**.
//!
//! Consider the number of *unique elements* in `nums` to be `k`. After removing duplicates, return
//! the number of unique elements `k`.
//!
//! The first `k` elements of `nums` should contain the unique numbers in **sorted order**. The
//! remaining elements beyond index `k - 1` can be ignored.
//!
//! # Custom Judge
//!
//! The judge will test your solution with the following code:
//!
//! ```text
//! int[] nums = [...]; // Input array
//! int[] expectedNums = [...]; // The expected answer with correct length
//!
//! int k = removeDuplicates(nums); // Calls your implementation
//!
//! assert k == expectedNums.length;
//! for (int i = 0; i < k; i++) {
//!     assert nums[i] == expectedNums[i];
//! }
//! ```
//!
//! If all assertions pass, then your solution will be **accepted**.
//!
//! # Example 1
//!
//! ```text
//! Input: nums = [1,1,2]
//! Output: 2, nums = [1,2,_]
//! Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
//! It does not matter what you leave beyond the returned k (hence they are underscores).
//! ```
//!
//! # Example 2
//!
//! ```text
//! Input: nums = [0,0,1,1,1,2,2,3,3,4]
//! Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
//! Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
//! It does not matter what you leave beyond the returned k (hence they are underscores).
//! ```
//!
//! # Constraints
//!
//! - `1 <= nums.length <= 3 * 10^4`
//! - `-100 <= nums[i] <= 100`
//! - `nums` is sorted in **non-decreasing** order.

pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
    if nums.len() <= 1 {
        return nums.len() as i32;
    }

    let mut new_len = 1;
    for i in 1..nums.len() {
        if nums[i] != nums[i - 1] {
            nums[new_len] = nums[i];
            new_len += 1;
        }
    }
    new_len as i32
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        check(&[], &[]);
        check(&[1], &[1]);
        check(&[1, 2], &[1, 2]);
        check(&[1, 1], &[1]);
        check(&[1, 1, 2], &[1, 2]);
        check(&[1, 2, 2], &[1, 2]);
        check(&[1, 2, 2, 3], &[1, 2, 3]);
        check(&[-100, -100, 0, 0, 100, 100], &[-100, 0, 100]);
    }

    fn check(nums: &[i32], expected: &[i32]) {
        let mut nums = nums.to_vec();
        let new_len = remove_duplicates(&mut nums) as usize;
        assert_eq!(&nums[..new_len], expected);
    }
}
