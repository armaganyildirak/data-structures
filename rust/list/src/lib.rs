use std::cell::RefCell;
use std::rc::Rc;
use std::fmt::Debug;

struct ListNode<T> {
    data: T,
    next: Option<Rc<RefCell<ListNode<T>>>>,
    prev: Option<Rc<RefCell<ListNode<T>>>>,
}

pub struct List<T> {
    head: Option<Rc<RefCell<ListNode<T>>>>,
}

impl<T: Debug + PartialEq + Copy> Default for List<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T: Debug + PartialEq + Clone> List<T> {
    pub fn new() -> Self {
        List { head: None }
    }

    pub fn insert_node(&mut self, data: T) {
        let new_node = Rc::new(RefCell::new(ListNode {
            data,
            next: None,
            prev: None,
        }));

        if let Some(head) = self.head.take() {
            let mut current = head.clone();
            while let Some(next) = current.clone().borrow().next.clone() {
                current = next;
            }
            new_node.borrow_mut().prev = Some(current.clone());
            current.borrow_mut().next = Some(new_node.clone());
            self.head = Some(head);
        } else {
            self.head = Some(new_node);
        }
    }

    pub fn delete_node(&mut self, data: T) {
        let mut current = self.head.clone();

        while let Some(node_rc) = current {
            let node = node_rc.borrow_mut();
            if node.data == data {
                let next_node = node.next.clone();
                let prev_node = node.prev.clone();

                if let Some(next) = next_node.clone() {
                    next.borrow_mut().prev = prev_node.clone();
                }

                if let Some(prev) = prev_node.clone() {
                    prev.borrow_mut().next = next_node.clone();
                } else {
                    self.head = next_node.clone();
                }

                if self.head.is_none() {
                    return;
                }

                return;
            }
            current = node.next.clone();
        }
    }

    pub fn print_list(&self) {
        let mut current = self.head.clone();
        while let Some(node_rc) = current {
            let node = node_rc.borrow();
            print!("{:?} -> ", node.data);
            current = node.next.clone();
        }
        println!("NULL");
    }

    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_insert_node() {
        let mut list = List::new();

        list.insert_node(10);
        list.insert_node(20);
        list.insert_node(30);

        list.print_list();

        let mut current = list.head.clone();
        assert_eq!(current.as_ref().unwrap().borrow().data, 10);
        current = current.unwrap().borrow().next.clone();
        assert_eq!(current.as_ref().unwrap().borrow().data, 20);
        current = current.unwrap().borrow().next.clone();
        assert_eq!(current.as_ref().unwrap().borrow().data, 30);
    }

    #[test]
    fn test_delete_node() {
        let mut list = List::new();
        list.insert_node(10);
        list.insert_node(20);
        list.insert_node(30);

        list.print_list();

        list.delete_node(30);
        list.print_list();
        assert_eq!(list.head.as_ref().unwrap().borrow().data, 10);
        
        list.delete_node(10);
        list.print_list();
        assert_eq!(list.head.as_ref().unwrap().borrow().data, 20);
          
        list.delete_node(20);
        list.print_list();
        assert!(list.is_empty());
    }

    #[test]
    fn test_delete_nonexistent_node() {
        let mut list = List::new();
        list.insert_node(10);
        list.insert_node(20);
        list.insert_node(30);

        list.delete_node(40);
        let mut current = list.head.clone();
        assert_eq!(current.as_ref().unwrap().borrow().data, 10);
        current = current.unwrap().borrow().next.clone();
        assert_eq!(current.as_ref().unwrap().borrow().data, 20);
        current = current.unwrap().borrow().next.clone();
        assert_eq!(current.as_ref().unwrap().borrow().data, 30);
    }

    #[test]
    fn test_empty_list() {
        let mut list = List::new();
        assert!(list.is_empty());

        list.delete_node(10);
        assert!(list.is_empty());
    }

    #[test]
    fn test_insert_multiple_nodes() {
        let mut list = List::new();

        for i in 1..=100 {
            list.insert_node(i);
        }

        let mut current = list.head.clone();
        for i in 1..=100 {
            assert_eq!(current.as_ref().unwrap().borrow().data, i);
            current = current.unwrap().borrow().next.clone();
        }
        assert!(current.is_none());
    }
}