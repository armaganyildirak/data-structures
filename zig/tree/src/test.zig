const std = @import("std");
const Tree = @import("tree.zig").Tree;
const TreeError = @import("tree.zig").TreeError;

test "initialize tree" {
    const tree = Tree(i32).init(std.testing.allocator);
    try std.testing.expect(tree.root == null);
}

test "insert single node" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);
    try std.testing.expect(tree.root.?.data == 10);
    try std.testing.expect(tree.root.?.left == null);
    try std.testing.expect(tree.root.?.right == null);
}

test "insert multiple nodes" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);
    try tree.insert_node(5);
    try tree.insert_node(15);

    try std.testing.expect(tree.root.?.data == 10);
    try std.testing.expect(tree.root.?.left.?.data == 5);
    try std.testing.expect(tree.root.?.right.?.data == 15);
}

test "insert duplicate node" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);

    const result = tree.insert_node(10);
    try std.testing.expect(result == TreeError.ExistingNode);

    try std.testing.expect(tree.root.?.data == 10);
    try std.testing.expect(tree.root.?.left == null);
    try std.testing.expect(tree.root.?.right == null);
}

test "deleting leaf nodes" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);
    try tree.insert_node(5);
    try tree.insert_node(15);
    try tree.insert_node(1);
    try tree.insert_node(7);

    try tree.delete_node(1);
    try std.testing.expect(tree.root.?.left.?.left == null);

    try tree.delete_node(7);
    try std.testing.expect(tree.root.?.left.?.right == null);
}

test "deleting node with one child" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);
    try tree.insert_node(5);
    try tree.insert_node(15);
    try tree.insert_node(12);

    try tree.delete_node(15);
    try std.testing.expect(tree.root.?.right.?.data == 12);
    try std.testing.expect(tree.root.?.right.?.left == null);
    try std.testing.expect(tree.root.?.right.?.right == null);
}

test "deleting node with two children" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);
    try tree.insert_node(5);
    try tree.insert_node(15);
    try tree.insert_node(12);
    try tree.insert_node(18);

    try tree.delete_node(15);

    try std.testing.expect(tree.root.?.right.?.data == 18);
    try std.testing.expect(tree.root.?.right.?.left.?.data == 12);
}

test "deleting node not found" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);
    try tree.insert_node(5);
    try tree.insert_node(15);

    const result = tree.delete_node(100);
    try std.testing.expectError(TreeError.DataNotFound, result);
}
