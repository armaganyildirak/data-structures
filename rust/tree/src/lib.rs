use std::cell::RefCell;
use std::rc::Rc;

#[derive(Debug, PartialEq)]
pub struct TreeNode<T> {
    pub data: T,
    pub left: Option<Rc<RefCell<TreeNode<T>>>>,
    pub right: Option<Rc<RefCell<TreeNode<T>>>>,
}

#[derive(Debug, PartialEq)]
pub struct Tree<T> {
    pub root: Option<Rc<RefCell<TreeNode<T>>>>,
}

impl<T: PartialOrd + Copy> Default for Tree<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T: PartialOrd + Copy> Tree<T> {
    pub fn new() -> Self {
        Tree { root: None }
    }
    pub fn insert_node(&mut self, data: T) {
        let new_node = Rc::new(RefCell::new(TreeNode {
            data,
            left: None,
            right: None,
        }));

        if self.root.is_none() {
            self.root = Some(new_node);
            return;
        }

        let mut temp = self.root.clone();
        let mut parent: Option<Rc<RefCell<TreeNode<T>>>> = None;

        while let Some(current) = temp {
            parent = Some(current.clone());
            let current_data = current.borrow().data;
            if data < current_data {
                temp = current.borrow().left.clone();
            } else if data > current_data {
                temp = current.borrow().right.clone();
            } else {
                println!("Error - cannot insert existing node");
                return;
            }
        }

        if let Some(parent_node) = parent {
            if data < parent_node.borrow().data {
                parent_node.borrow_mut().left = Some(new_node);
            } else {
                parent_node.borrow_mut().right = Some(new_node);
            }
        }
    }

    pub fn delete_node(&mut self, data: T) {
        if self.root.is_none() {
            println!("Error - tree is empty.");
            return;
        }

        let mut parent: Option<Rc<RefCell<TreeNode<T>>>> = None;
        let mut current = self.root.clone();

        while let Some(node) = current.clone() {
            if node.borrow().data == data {
                break;
            } else {
                parent = Some(node.clone());
                current = if data < node.borrow().data {
                    node.borrow().left.clone()
                } else {
                    node.borrow().right.clone()
                };
            }
        }

        if current.is_none() {
            println!("Error - data not found.");
            return;
        }

        let current_node = current.expect("Node should exist at this point!");
        let left_child = current_node.borrow().left.clone();
        let right_child = current_node.borrow().right.clone();

        if left_child.is_none() || right_child.is_none() {
            let child = left_child.or(right_child);
            if let Some(parent_node) = parent {
                if Rc::ptr_eq(
                    parent_node
                        .borrow()
                        .left
                        .as_ref()
                        .unwrap_or(&Rc::new(RefCell::new(TreeNode {
                            data: current_node.borrow().data, // Use the data of the current node
                            left: None,
                            right: None,
                        }))),
                    &current_node,
                ) {
                    parent_node.borrow_mut().left = child;
                } else {
                    parent_node.borrow_mut().right = child;
                }
            } else {
                self.root = child;
            }
        } else {
            let mut temp_parent = current_node.clone();
            let mut temp = right_child;

            while let Some(node) = temp.clone() {
                if node.borrow().left.is_none() {
                    break;
                }
                temp_parent = node.clone();
                temp = node.borrow().left.clone();
            }

            if let Some(temp_node) = temp {
                current_node.borrow_mut().data = temp_node.borrow().data;
                let temp_child = temp_node.borrow().right.clone();
                if Rc::ptr_eq(&temp_parent, &current_node) {
                    current_node.borrow_mut().right = temp_child;
                } else {
                    temp_parent.borrow_mut().left = temp_child;
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_insert_node() {
        let mut tree = Tree::new();
        tree.insert_node(10);
        tree.insert_node(5);
        tree.insert_node(15);

        assert_eq!(tree.root.as_ref().unwrap().borrow().data, 10);
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .left
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            5
        );
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .right
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            15
        );
    }

    #[test]
    fn test_delete_leaf_node() {
        let mut tree = Tree::new();
        tree.insert_node(10);
        tree.insert_node(5);
        tree.insert_node(15);

        tree.delete_node(5);

        assert!(tree.root.as_ref().unwrap().borrow().left.is_none());
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .right
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            15
        );
    }

    #[test]
    fn test_delete_node_with_one_child() {
        let mut tree = Tree::new();
        tree.insert_node(10);
        tree.insert_node(5);
        tree.insert_node(15);
        tree.insert_node(12);

        tree.delete_node(15);

        assert_eq!(tree.root.as_ref().unwrap().borrow().data, 10);
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .left
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            5
        );
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .right
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            12
        );
    }

    #[test]
    fn test_delete_node_with_two_children() {
        let mut tree = Tree::new();
        tree.insert_node(10);
        tree.insert_node(5);
        tree.insert_node(15);
        tree.insert_node(12);
        tree.insert_node(18);

        tree.delete_node(10);

        assert_eq!(tree.root.as_ref().unwrap().borrow().data, 12);
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .left
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            5
        );
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .right
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            15
        );
    }

    #[test]
    fn test_delete_non_existent_node() {
        let mut tree = Tree::new();
        tree.insert_node(10);
        tree.insert_node(5);
        tree.insert_node(15);

        tree.delete_node(20);

        assert_eq!(tree.root.as_ref().unwrap().borrow().data, 10);
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .left
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            5
        );
        assert_eq!(
            tree.root
                .as_ref()
                .unwrap()
                .borrow()
                .right
                .as_ref()
                .unwrap()
                .borrow()
                .data,
            15
        );
    }

    #[test]
    fn test_delete_from_empty_tree() {
        let mut tree = Tree::new();

        tree.delete_node(10);

        assert!(tree.root.is_none());
    }
}
