//! [LeetCode 27: Remove Element](https://leetcode.com/problems/remove-element)

pub fn remove_element(nums: &mut Vec<i32>, val: i32) -> i32 {
    if nums.is_empty() {
        return 0;
    }

    let mut left = 0usize;
    let mut right = nums.len() - 1;
    loop {
        while left <= right && nums[left] != val {
            left += 1;
        }

        while left < right && nums[right] == val {
            right -= 1;
        }

        if left < right {
            nums[left] = nums[right];
            nums[right] = val;
        } else {
            break;
        }
    }
    left as i32
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        check(&[], 42, &[]);
        check(&[1], 42, &[1]);
        check(&[42], 42, &[]);
        check(&[42, 42, 42], 42, &[]);
        check(&[1, 2, 3], 42, &[1, 2, 3]);
        check(&[1, 1, 1], 42, &[1, 1, 1]);
        check(&[42, 1, 2], 42, &[1, 2]);
        check(&[1, 42, 2], 42, &[1, 2]);
        check(&[1, 42, 42], 42, &[1]);
    }

    fn check(nums: &[i32], val: i32, expected: &[i32]) {
        let mut nums = nums.to_vec();
        let len = remove_element(&mut nums, val) as usize;
        let mut sorted: Vec<_> = nums[..len].to_vec();
        sorted.sort();
        let mut expected_sorted = expected.to_vec();
        expected_sorted.sort();

        assert_eq!(sorted, expected_sorted, "nums: {:?}, val: {}", nums, val);
    }
}
