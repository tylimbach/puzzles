#[derive(Debug)]
pub struct Node {
    pub val: i32,
    pub left: *mut Node,
    pub right: *mut Node,
    pub next: *mut Node,
}

impl Node {
    pub fn new(val: i32) -> Box<Node> {
        Box::new(Node {
            val,
            left: std::ptr::null_mut(),
            right: std::ptr::null_mut(),
            next: std::ptr::null_mut(),
        })
    }

    pub fn with_children(val: i32, left: Box<Node>, right: Box<Node>) -> Box<Node> {
        Box::new(Node {
            val,
            left: Box::into_raw(left),
            right: Box::into_raw(right),
            next: std::ptr::null_mut(),
        })
    }
}

fn post_order_traverse(right_at_depth: &mut Vec<*mut Node>, node: *mut Node, depth: usize) {
    unsafe {
        if !node.is_null() {
            // Ensure the vector has enough space for the current depth
            if right_at_depth.len() <= depth {
                right_at_depth.push(std::ptr::null_mut());
            }

            // Traverse the right and left children
            post_order_traverse(right_at_depth, (*node).right, depth + 1);
            post_order_traverse(right_at_depth, (*node).left, depth + 1);

            // Set the `next` pointer
            (*node).next = right_at_depth[depth];
            right_at_depth[depth] = node;
        }
    }
}

pub fn connect(mut root: Box<Node>) -> Box<Node> {
    let mut right_at_depth = Vec::new();
    let root_ptr = &mut *root as *mut Node; // Get a raw pointer to the root node

    post_order_traverse(&mut right_at_depth, root_ptr, 0);
    root
}

fn main() {
    let root = Node::with_children(
        1,
        Node::with_children(2, Node::new(4), Node::new(5)),
        Node::with_children(3, Node::new(6), Node::new(7)),
    );

    let connected_root = connect(root);
}
