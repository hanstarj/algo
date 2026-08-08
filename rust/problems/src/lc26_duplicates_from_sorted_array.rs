//! [LeetCode 26: Duplicates from Sorted Array](https://leetcode.com/problems/duplicates-from-sorted-array/)

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
