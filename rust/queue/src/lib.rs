use std::cell::RefCell;
use std::rc::Rc;

struct QueueNode<T> {
    value: T,
    next: Option<Rc<RefCell<QueueNode<T>>>>,
}

pub struct Queue<T> {
    head: Option<Rc<RefCell<QueueNode<T>>>>,
    tail: Option<Rc<RefCell<QueueNode<T>>>>,
}

impl<T: Clone> Default for Queue<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T: Clone> Queue<T> {
    pub fn new() -> Self {
        Queue {
            head: None,
            tail: None,
        }
    }

    pub fn enqueue(&mut self, value: T) {
        let new_node = Rc::new(RefCell::new(QueueNode { value, next: None }));

        if let Some(tail) = self.tail.take() {
            tail.borrow_mut().next = Some(new_node.clone());
        } else {
            self.head = Some(new_node.clone());
        }

        self.tail = Some(new_node);
    }

    pub fn dequeue(&mut self) -> Option<T> {
        self.head.take().map(|head| {
            let head_borrowed = head.borrow();
            self.head = head_borrowed.next.clone();
            if self.head.is_none() {
                self.tail = None;
            }
            head_borrowed.value.clone()
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_enqueue_dequeue() {
        let mut queue = Queue::default();
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);

        assert_eq!(queue.dequeue(), Some(10));
        assert_eq!(queue.dequeue(), Some(20));
        assert_eq!(queue.dequeue(), Some(30));
        assert_eq!(queue.dequeue(), None);
    }

    #[test]
    fn test_multiple_operations() {
        let mut queue = Queue::new();
        queue.enqueue(10);
        queue.enqueue(20);
        assert_eq!(queue.dequeue(), Some(10));
        queue.enqueue(30);
        assert_eq!(queue.dequeue(), Some(20));
        assert_eq!(queue.dequeue(), Some(30));
        assert_eq!(queue.dequeue(), None);
        queue.enqueue(40);
        assert_eq!(queue.dequeue(), Some(40));
    }
}
