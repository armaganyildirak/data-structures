const std = @import("std");

pub const TreeNode = struct {
    data: i32,
    left: ?*TreeNode,
    right: ?*TreeNode,
};

pub const TreeError = error{
    ExistingNode,
    EmptyTree,
    DataNotFound,
};

pub const Tree = struct {
    root: ?*TreeNode,

    pub fn init() Tree {
        return Tree{ .root = null };
    }

    pub fn insert_node(self: *Tree, data: i32) !void {
        const new_node = try std.heap.page_allocator.create(TreeNode);
        new_node.* = TreeNode{
            .data = data,
            .left = null,
            .right = null,
        };

        if (self.root == null) {
            self.root = new_node;
            return;
        }

        var temp = self.root;
        var parent: ?*TreeNode = null;

        while (temp != null) {
            parent = temp;
            if (data < temp.?.data) {
                temp = temp.?.left;
            } else if (data > temp.?.data) {
                temp = temp.?.right;
            } else {
                return TreeError.ExistingNode;
            }
        }

        if (data < parent.?.data) {
            parent.?.left = new_node;
        } else {
            parent.?.right = new_node;
        }
    }

    pub fn delete_node(self: *Tree, data: i32) !void {
        if (self.root == null) {
            return TreeError.EmptyTree;
        }

        var parent: ?*TreeNode = null;
        var current = self.root;

        while (current != null and data != current.?.data) {
            parent = current;
            if (data < current.?.data) {
                current = current.?.left;
            } else {
                current = current.?.right;
            }
        }

        if (current == null) {
            return TreeError.DataNotFound;
        }

        if (current.?.left == null and current.?.right == null) {
            if (current == self.root) {
                self.root = null;
            } else if (parent.?.left == current) {
                parent.?.left = null;
            } else {
                parent.?.right = null;
            }
            std.heap.page_allocator.destroy(current.?);
        } else if (current.?.left == null or current.?.right == null) {
            const child: ?*TreeNode = if (current.?.left != null) current.?.left else current.?.right;

            if (current == self.root) {
                self.root = child;
            } else if (parent.?.left == current) {
                parent.?.left = child;
            } else {
                parent.?.right = child;
            }
            std.heap.page_allocator.destroy(current.?);
        } else {
            var temp_parent = current;
            var temp = current.?.right;

            while (temp.?.left != null) {
                temp_parent = temp;
                temp = temp.?.left;
            }

            current.?.data = temp.?.data;

            if (temp_parent.?.left == temp) {
                temp_parent.?.left = temp.?.right;
            } else {
                temp_parent.?.right = temp.?.right;
            }

            std.heap.page_allocator.destroy(temp.?);
        }
    }
};
