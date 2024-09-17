struct QueueNode<T> {
    value: T,
    next: Option<Box<QueueNode<T>>>,
}

pub struct Queue<T> {
    head: Option<Box<QueueNode<T>>>,
    tail: Option<*mut QueueNode<T>>,
}

impl<T> Default for Queue<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T> Queue<T> {
    pub fn new() -> Self {
        Queue {
            head: None,
            tail: None,
        }
    }

    pub fn enqueue(&mut self, value: T) {
        let mut new_node = Box::new(QueueNode { value, next: None });
        let raw_node = &mut *new_node as *mut QueueNode<T>;

        match self.tail {
            Some(tail) => unsafe {
                (*tail).next = Some(new_node);
            },
            None => self.head = Some(new_node),
        }
        self.tail = Some(raw_node);
    }

    pub fn dequeue(&mut self) -> Option<T> {
        self.head.take().map(|mut head| {
            self.head = head.next.take();
            if self.head.is_none() {
                self.tail = None;
            }
            head.value
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
