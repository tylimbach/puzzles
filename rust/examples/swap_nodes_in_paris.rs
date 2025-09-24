#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode {
      next: None,
      val
    }
  }
}

pub fn swap_pairs(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    match head {
        None => None,
        Some(mut first) => {
            match first.next.take() {
                None => Some(first),
                Some(mut second) => {
                    let rest = second.next.take();
                    first.next = swap_pairs(rest);
                    second.next = Some(first);
                    Some(second)
                }
            }
        }
    }
}

 
fn main(){
       
}

/*
24. Swap Nodes in Pairs
Solved
Medium
Topics
Companies

Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

 

Example 1:

Input: head = [1,2,3,4]

Output: [2,1,4,3]

Explanation:

Example 2:

Input: head = []

Output: []

Example 3:

Input: head = [1]

Output: [1]

Example 4:

Input: head = [1,2,3]

Output: [2,1,3]

 

Constraints:

    The number of nodes in the list is in the range [0, 100].
    0 <= Node.val <= 100

*/
