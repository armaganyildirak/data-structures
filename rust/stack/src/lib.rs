struct StackNode<T> {
    data: T,
    next: Option<Box<StackNode<T>>>,
}

pub struct Stack<T> {
    top: Option<Box<StackNode<T>>>,
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
        let new_node = Box::new(StackNode {
            data,
            next: self.top.take(),
        });
        self.top = Some(new_node);
    }

    pub fn pop(&mut self) -> Option<T> {
        self.top.take().map(|top_node| {
            self.top = top_node.next;
            top_node.data
        })
    }

    pub fn peek(&self) -> Option<&T> {
        self.top.as_ref().map(|top_node| &top_node.data)
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
        assert_eq!(stack.peek(), Some(&100));

        stack.push(200);
        assert_eq!(stack.peek(), Some(&200));

        stack.pop();
        assert_eq!(stack.peek(), Some(&100));
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
