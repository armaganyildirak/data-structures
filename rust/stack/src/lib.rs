use std::cell::RefCell;
use std::option::Option;
use std::rc::Rc;

struct StackNode<T> {
    data: T,
    next: Option<Rc<RefCell<StackNode<T>>>>,
}

pub struct Stack<T> {
    top: Option<Rc<RefCell<StackNode<T>>>>,
}

impl<T> Default for Stack<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T> Stack<T> {
    pub fn new() -> Self {
        Stack { top: None }
    }

    pub fn push(&mut self, data: T) {
        let new_node = Rc::new(RefCell::new(StackNode {
            data,
            next: self.top.clone(),
        }));
        self.top = Some(new_node);
    }

    pub fn pop(&mut self) -> Option<T> {
        if !self.is_empty() {
            if let Some(top_node) = self.top.take() {
                if let Ok(top_node_taken) = Rc::try_unwrap(top_node) {
                    let top_node_taken_unwrapped = top_node_taken.into_inner();
                    self.top = top_node_taken_unwrapped.next;
                    Some(top_node_taken_unwrapped.data)
                } else {
                    None
                }
            } else {
                None
            }
        } else {
            None
        }
    }

    pub fn peek(&self) -> Option<T>
    where
        T: Clone,
    {
        if !self.is_empty() {
            if let Some(ref top_node) = self.top {
                let top_node_borrowed = top_node.borrow();
                Some(top_node_borrowed.data.clone())
            } else {
                None
            }
        } else {
            None
        }
    }

    pub fn is_empty(&self) -> bool {
        self.top.is_none()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_stack_push_pop() {
        let mut stack = Stack::default();

        stack.push(10);
        stack.push(20);
        stack.push(30);

        assert_eq!(stack.pop(), Some(30));
        assert_eq!(stack.pop(), Some(20));
        assert_eq!(stack.pop(), Some(10));
        assert_eq!(stack.pop(), None);
    }
    #[test]
    fn test_stack_peek() {
        let mut stack = Stack::default();
        assert_eq!(stack.peek(), None);

        stack.push(100);
        assert_eq!(stack.peek(), Some(100));

        stack.push(200);
        assert_eq!(stack.peek(), Some(200));

        stack.pop();
        assert_eq!(stack.peek(), Some(100));
    }

    #[test]
    fn test_stack_is_empty() {
        let mut stack = Stack::default();

        assert!(stack.is_empty());

        stack.push(42);
        assert!(!stack.is_empty());

        stack.pop();
        assert!(stack.is_empty());
    }
}
