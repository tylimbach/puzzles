use core::fmt;
use std::{alloc::{self, alloc, realloc, Layout}, marker::PhantomData, ops::{Index, IndexMut}, ptr::NonNull};

pub struct Vector<T> {
    data: NonNull<T>,
    size: usize,
    capacity: usize,
    marker: PhantomData<T>,
}

impl<T> Vector<T> {
    pub fn with_capacity(capacity: usize) -> Self {
        let layout = Layout::array::<T>(capacity).expect("Vector layout overflow");
        let ptr = unsafe {alloc(layout)} as *mut T;
        let data = NonNull::new(ptr).unwrap_or_else(|| alloc::handle_alloc_error(layout));

        Vector { data, capacity, size: 0, marker: PhantomData, }
    }

    pub fn push_back(&mut self, value: T) {
        if self.size == self.capacity {
            self.grow();
        }

        unsafe {
            *self.data.as_ptr().add(self.size) = value;
        }

        self.size += 1;
    }

    pub fn pop_back(&mut self) -> Option<T> {
        if self.size == 0 {
            return None;
        }

        let popped_value = unsafe {
            let ptr = self.data.as_ptr().add(self.size - 1);
            Some(std::ptr::read(ptr))
        };

        self.size -= 1;
        popped_value 
    }

    pub fn get(&self, index: usize) -> Option<&T> {
        if index >= self.size {
            return None;
        }

        unsafe {
            Some(&*self.data.as_ptr().add(self.size - 1))
        }
    }

    pub fn get_mut(&mut self, index: usize) -> Option<&mut T> {
        if index >= self.size {
            return None;
        }

        unsafe {
            Some(&mut *self.data.as_ptr().add(self.size - 1))
        }
    }

    pub fn clear(&mut self) {
        unsafe {
            let ptr = self.data.as_ptr(); 

            for i in (0..self.size).rev() {
                std::ptr::drop_in_place(ptr.add(i));
            }
        }

        self.size = 0;
    }

    fn grow(&mut self) {
        let new_capacity = self.capacity.saturating_mul(2);
        
        if new_capacity == self.capacity {
            panic!("Vector capacity overflow");
        }

        let old_layout = Layout::array::<T>(self.capacity).expect("Vector Layout Overflow");
        let old_ptr = self.data.as_ptr() as *mut u8;

        let new_layout = Layout::array::<T>(new_capacity).expect("Vector Layout Overflow");
        let new_ptr = unsafe {realloc(old_ptr, old_layout, new_layout.size())} as *mut T;
        let new_data = NonNull::new(new_ptr).unwrap_or_else(|| alloc::handle_alloc_error(new_layout));

        self.data = new_data;
        self.capacity = new_capacity;
    }
}

impl<T> Drop for Vector<T> {
    fn drop(&mut self) {
        todo!()
    }
}

impl<T> Index<usize> for Vector<T> {
    type Output = T;

    fn index(&self, index: usize) -> &Self::Output {
        todo!()
    }
}

impl<T> IndexMut<usize> for Vector<T> {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        todo!()
    }
}

impl<T: PartialEq> PartialEq for Vector<T> {
    fn eq(&self, other: &Self) -> bool {
        todo!();
    }
}

impl<T: fmt::Debug> fmt::Debug for Vector<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        todo!();
    }
}

impl<T: Clone> Clone for Vector<T> {
    fn clone(&self) -> Self {
        todo!();
    }
}

impl<T: Default> Default for Vector<T> {
    fn default() -> Self {
        todo!();
    }
}

pub struct VectorIter<'a, T> {
    vector: &'a Vector<T>,
    index: usize,
}

impl<T> Vector<T> {
    pub fn iter(&self) -> VectorIter<'_, T> {
        todo!();
    }
}

impl<'a, T> Iterator for VectorIter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        todo!()
    }
}
