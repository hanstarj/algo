//! [LeetCode 21: Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists)
//!
//! You are given the heads of two sorted linked lists `list1` and `list2`.
//!
//! Merge the two lists into one **sorted** list. The list should be made by splicing together the
//! nodes of the first two lists.
//!
//! Return *the head of the merged linked list*.
//!
//! # Example 1
//!
//! ```text
//! Input: list1 = [1,2,4], list2 = [1,3,4]
//! Output: [1,1,2,3,4,4]
//! ```
//!
//! # Example 2
//!
//! ```text
//! Input: list1 = [], list2 = []
//! Output: []
//! ```
//!
//! # Example 3
//!
//! ```text
//! Input: list1 = [], list2 = [0]
//! Output: [0]
//! ```
//!
//! # Constraints
//!
//! - The number of nodes in both lists is in the range `[0, 50]`.
//! - `-100 <= Node.val <= 100`
//! - Both `list1` and `list2` are sorted in **non-decreasing** order.

#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

pub fn merge_two_lists(
    mut list1: Option<Box<ListNode>>,
    mut list2: Option<Box<ListNode>>,
) -> Option<Box<ListNode>> {
    let mut dummy = ListNode::new(0);
    let mut tail = &mut dummy;

    while let (Some(l1), Some(l2)) = (list1.as_ref(), list2.as_ref()) {
        if l1.val < l2.val {
            tail.next = list1;
            tail = tail.next.as_mut().unwrap();
            list1 = tail.next.take();
        } else {
            tail.next = list2;
            tail = tail.next.as_mut().unwrap();
            list2 = tail.next.take();
        }
    }

    tail.next = list1.or(list2);
    dummy.next
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        assert_eq!(merge_two_lists(build(&[]), build(&[])), build(&[]));
        assert_eq!(merge_two_lists(build(&[1]), build(&[])), build(&[1]));
        assert_eq!(merge_two_lists(build(&[]), build(&[2])), build(&[2]));
        assert_eq!(merge_two_lists(build(&[1]), build(&[2])), build(&[1, 2]));
        assert_eq!(merge_two_lists(build(&[2]), build(&[1])), build(&[1, 2]));
        assert_eq!(
            merge_two_lists(build(&[1, 3]), build(&[2, 4])),
            build(&[1, 2, 3, 4])
        );
        assert_eq!(
            merge_two_lists(build(&[2, 4]), build(&[1, 3])),
            build(&[1, 2, 3, 4])
        );
        assert_eq!(
            merge_two_lists(build(&[1]), build(&[2, 3, 4])),
            build(&[1, 2, 3, 4])
        );
        assert_eq!(
            merge_two_lists(build(&[2, 3, 4]), build(&[1])),
            build(&[1, 2, 3, 4])
        );
        assert_eq!(
            merge_two_lists(build(&[1, 1, 2]), build(&[1, 1, 3])),
            build(&[1, 1, 1, 1, 2, 3])
        );
    }

    fn build(vals: &[i32]) -> Option<Box<ListNode>> {
        let Some(first) = vals.first() else {
            return None;
        };

        let mut head = Box::new(ListNode::new(*first));
        let mut tail = &mut head;
        for &val in &vals[1..] {
            tail.next = Some(Box::new(ListNode::new(val)));
            tail = tail.next.as_mut().unwrap();
        }
        Some(head)
    }
}
