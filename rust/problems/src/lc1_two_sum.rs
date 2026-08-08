//! [LeetCode 1: Two Sum](https://leetcode.com/problems/two-sum/)

use std::collections::HashMap;

pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    let mut map = HashMap::<i32, i16>::with_capacity(nums.len());
    for (j, &num) in nums.iter().enumerate() {
        if let Some(&i) = map.get(&(target - num)) {
            return vec![i as i32, j as i32];
        }
        map.insert(num, j as i16);
    }

    unreachable!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        assert_eq!(two_sum(vec![2, 7, 11, 15], 9), vec![0, 1]);
        assert_eq!(two_sum(vec![3, 2, 4], 6), vec![1, 2]);
        assert_eq!(two_sum(vec![3, 3], 6), vec![0, 1]);
    }
}
