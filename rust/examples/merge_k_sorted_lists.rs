use std::{cmp::Reverse, collections::BinaryHeap, io::{self, Write}};

#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode {
            next: None,
            val,
        }
    }
}

struct MinHeap<T: Ord> {
    inner: BinaryHeap<Reverse<T>>,
}

impl<T: Ord> MinHeap<T> {
    #[inline]
    fn new() -> Self {
         
    }
}



fn merge_k_lists(lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
    

    Some(Box::new(ListNode::new(1))) 
}

fn main() -> io::Result<()> {
    println!("Enter args for combinaiton_sum2(candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>>");
    io::stdout().flush()?;

    let lists= read_args()?;
    let res = merge_k_lists(lists);

    println!("Result: {:?}", res);
    io::stdout().flush()?;
    Ok(())
}

fn read_args() -> io::Result<Vec<Option<Box<ListNode>>>> {
    let mut input = String::new();
    io::stdin().read_line(&mut input)?;

    let mut lists: Vec<Option<Box<ListNode>>> = vec![];
    let parts = input.split_whitespace();
    for part in parts {
        let node_vals: Vec<i32> = part
            .split(",")
            .map(|s| {
                s.parse::<i32>()
                 .map_err(|e| io::Error::new(io::ErrorKind::InvalidInput, e))
            }).collect::<Result<Vec<_>, _>>()?;

        lists.push(vec_to_ll(node_vals));
    }

    Ok(lists)
}

fn vec_to_ll(vals: Vec<i32>) -> Option<Box<ListNode>> {
    vals.into_iter().rev().fold(None, |next, v| {
        let mut node = Box::new(ListNode::new(v));
        node.next = next;
        Some(node)
    })
}

/*
23. Merge k Sorted Lists
Hard
Topics
Companies

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Example 2:

Input: lists = []
Output: []

Example 3:

Input: lists = [[]]
Output: []

 

Constraints:

    k == lists.length
    0 <= k <= 104
    0 <= lists[i].length <= 500
    -104 <= lists[i][j] <= 104
    lists[i] is sorted in ascending order.
    The sum of lists[i].length will not exceed 104.

*/
