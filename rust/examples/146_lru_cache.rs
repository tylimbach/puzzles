use std::{collections::HashMap, hash::Hash}


struct DoubleLinkedListNode<T> {
    pub value: T,
    pub prev: *mut DoubleLinkedListNode<T>,
    pub next: *mut DoubleLinkedListNode<T>,
}
impl<T> DoubleLinkedListNode<T> {
    pub fn new(value: T) -> *mut Self {
        Box::into_raw(Box::new(DoubleLinkedListNode {
            value,
            prev: std::ptr::null_mut(),
            next: std::ptr::null_mut()
        }))
    }
}

pub struct LRUCache<K: Eq + Hash, V> {
    pub capacity: usize,
    pub size: usize,
    map: HashMap<K, *mut DoubleLinkedListNode<V>>,
    mru: *mut DoubleLinkedListNode<V>,
    lru: *mut DoubleLinkedListNode<V>
}
impl<K: Eq + Hash, V> LRUCache<K, V> {
    pub fn new(capacity: usize) -> Self {
        LRUCache {
            capacity,
            size: 0,
            map: HashMap::new(),
            mru: std::ptr::null_mut(),
            lru: std::ptr::null_mut(),
        }
    } 

    pub fn get(&mut self, key: &K) -> Option<&V> {
        if let Some(&node) = self.map.get(key) {
            unsafe {
                self.to_front(node);
                Some(&(*node).value)
            }
        } else {
            None
        }
    }

    pub fn put(&mut self, key: K, value: V) {
        if let Some(&node) = self.map.get(&key) {
            unsafe {
                (*node).value = value;
                self.to_front(node);
            }
            return;
        }

        if self.capacity == self.size {
            unsafe { self.evict_back(); }
        }
        let node = DoubleLinkedListNode::new(value);
        self.map.insert(key, node);
        unsafe { self.to_front(node); }
        self.size += 1;
    }

    unsafe fn remove_node(&mut self, node: *mut DoubleLinkedListNode<V>) {
        debug_assert!(!node.is_null());

        unsafe {
            let old_prev = (*node).prev;

            // this check should sufficiently confirm whether the node is in the list yet
            if !old_prev.is_null() {
                let old_next = (*node).next;

                (*old_prev).next = old_next;
                if !old_next.is_null() {
                    (*old_next).prev = old_prev;
                }
            }
        }
    }

    // TODO: handle nodes that are entirely new and not == mru
    unsafe fn to_front(&mut self, node: *mut DoubleLinkedListNode<V>) {
        debug_assert!(!node.is_null());

        unsafe {
            if node == self.mru { return; }

            self.remove_node(node);

            (*self.mru).prev = node;
            (*node).next = self.mru;
        }

        self.mru = node;
    }

    unsafe fn evict_back(&mut self) {
        debug_assert!(!self.lru.is_null());
        
        unsafe {
            if !(*self.lru).prev.is_null() {
                (*(*self.lru).prev).next = std::ptr::null_mut();
            }
            let _ = Box::from_raw(self.lru);
        }
    }
}

impl<K: Eq + Hash, V> Drop for LRUCache<K, V> {
    fn drop(&mut self) {
        unsafe {
            while !self.lru.is_null() {
                let node = self.lru;
                self.lru = (*node).prev;
                let _ = Box::from_raw(node);
            }
        }
    }
}


fn main() {
    let root = DoubleLinkedListNode::new(1);
}
