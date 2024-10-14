const std = @import("std");

pub const TreeError = error{
    ExistingNode,
    EmptyTree,
    DataNotFound,
};

pub fn Tree(comptime T: type) type {
    return struct {
        const This = @This();
        const TreeNode = struct {
            data: T,
            left: ?*TreeNode,
            right: ?*TreeNode,
        };

        gpa: std.mem.Allocator,
        root: ?*TreeNode = null,
        size: u32 = 0,

        pub fn init(gpa: std.mem.Allocator) This {
            return This{
                .gpa = gpa,
                .root = null,
                .size = 0,
            };
        }

        pub fn insert_node(this: *This, data: T) !void {
            const new_node = try this.gpa.create(TreeNode);
            new_node.* = TreeNode{
                .data = data,
                .left = null,
                .right = null,
            };

            if (this.root == null) {
                this.root = new_node;
                return;
            }

            var current = this.root;
            var parent: ?*TreeNode = null;

            while (current) |temp| {
                parent = temp;
                if (data < temp.data) {
                    current = temp.left;
                } else if (data > temp.data) {
                    current = temp.right;
                } else {
                    return TreeError.ExistingNode;
                }
            }

            if (parent) |par| {
                if (data < par.data) {
                    par.left = new_node;
                } else {
                    par.right = new_node;
                }
            }
            this.size += 1;
        }

        pub fn delete_node(this: *This, data: T) !void {
            if (this.root == null) {
                return TreeError.EmptyTree;
            }

            var parent: ?*TreeNode = null;
            var current = this.root;

            while (current) |curr| {
                if (data != curr.data) {
                    parent = curr;
                    if (data < curr.data) {
                        current = curr.left;
                    } else {
                        current = curr.right;
                    }
                } else {
                    break;
                }
            }

            if (current == null) {
                return TreeError.DataNotFound;
            }

            if (current) |curr| {
                if (parent) |par| {
                    if (curr.left == null and curr.right == null) {
                        if (curr == this.root) {
                            this.root = null;
                        } else if (par.left == curr) {
                            par.left = null;
                        } else {
                            par.right = null;
                        }
                        this.size -= 1;
                        this.gpa.destroy(curr);
                    } else if (curr.left == null or curr.right == null) {
                        const child: ?*TreeNode = if (curr.left != null) curr.left else curr.right;

                        if (curr == this.root) {
                            this.root = child;
                        } else if (par.left == curr) {
                            par.left = child;
                        } else {
                            par.right = child;
                        }
                        this.size -= 1;
                        this.gpa.destroy(curr);
                    } else {
                        var temp_parent = curr;
                        var temp = curr.right;
                        // TODO!
                        while (temp.?.left != null) {
                            temp_parent = temp.?;
                            temp = temp.?.left;
                        }

                        if (temp) |copy| {
                            curr.data = copy.data;
                            if (temp_parent.left == copy) {
                                temp_parent.left = copy.right;
                            } else {
                                temp_parent.right = copy.right;
                            }

                            this.size -= 1;
                            this.gpa.destroy(copy);
                        }
                    }
                }
            }
        }
    };
}
