use std::cell::RefCell;
use std::rc::Rc;

type NodeRef = Option<Rc<RefCell<Node>>>;

#[derive(Debug)]
pub struct Node {
    pub val: i32,
    pub left: NodeRef,
    pub right: NodeRef,
    pub next: Option<Rc<RefCell<Node>>>,
}

impl Node {
    pub fn new(val: i32) -> NodeRef {
        Some(Rc::new(RefCell::new(Node {
            val,
            left: None,
            right: None,
            next: None,
        })))
    }

    pub fn with_children(val: i32, left: NodeRef, right: NodeRef) -> NodeRef {
        Some(Rc::new(RefCell::new(Node {
            val,
            left,
            right,
            next: None,
        })))
    }
}

pub fn post_order_traverse(right_at_depth: &mut Vec<Option<Rc<RefCell<Node>>>>, node: &NodeRef, depth: usize) {
    if let Some(node_rc) = node {
        let mut node_ref = node_rc.borrow_mut();

        // Ensure the vector has enough space for the current depth
        if right_at_depth.len() <= depth {
            right_at_depth.push(None);
        }

        // Traverse the right and left children
        post_order_traverse(right_at_depth, &node_ref.right, depth + 1);
        post_order_traverse(right_at_depth, &node_ref.left, depth + 1);

        // Set the `next` pointer
        node_ref.next = right_at_depth[depth].clone();
        right_at_depth[depth] = Some(node_rc.clone());
    }
}

pub fn connect(root: NodeRef) -> NodeRef {
    let mut right_at_depth = Vec::new();
    if root.is_some() {
        post_order_traverse(&mut right_at_depth, &root, 0);
    }
    root
}


fn main() {
    let root = Node::with_children(
        1,
        Node::with_children(2, Node::new(4), Node::new(5)),
        Node::with_children(3, Node::new(6), Node::new(7)),
    );

    let connected_root = connect(root);

    // Print the tree with next pointers
    fn print_tree_with_next(node: &NodeRef) {
        if let Some(node_rc) = node {
            let node_ref = node_rc.borrow();
            let next_val = node_ref.next.as_ref().map_or(-1, |n| n.borrow().val);
            println!("Node: {}, Next: {}", node_ref.val, next_val);
            print_tree_with_next(&node_ref.left);
            print_tree_with_next(&node_ref.right);
        }
    }

    print_tree_with_next(&connected_root);
}
