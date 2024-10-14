const std = @import("std");
const Tree = @import("tree.zig").Tree;

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var tree = Tree(i32).init(arena.allocator());
    try tree.insert_node(10);
    try tree.insert_node(5);
    try tree.insert_node(15);
    try tree.insert_node(12);
    try tree.insert_node(20);

    std.debug.print("{}\n", .{tree.root.?.data});
    std.debug.print("{}\n", .{tree.root.?.left.?.data});
    std.debug.print("{}\n", .{tree.root.?.right.?.data});
    std.debug.print("{}\n", .{tree.root.?.right.?.right.?.data});
    std.debug.print("{}\n", .{tree.root.?.right.?.left.?.data});

    try tree.delete_node(15);

    std.debug.print("{}\n", .{tree.root.?.data});
    std.debug.print("{}\n", .{tree.root.?.left.?.data});
    std.debug.print("{}\n", .{tree.root.?.right.?.data});
    std.debug.print("{}\n", .{tree.root.?.right.?.left.?.data});
}
