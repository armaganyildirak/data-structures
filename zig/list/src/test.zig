const std = @import("std");
const List = @import("list.zig").List;
const ListError = @import("list.zig").ListError;

test "Test Insertion" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var list = List(i32).init(arena.allocator());
    defer list.free();

    try list.insert_node(10, 0);
    try list.insert_node(20, 1);
    try list.insert_node(30, 2);

    try std.testing.expectEqual(list.size, 3);
}

test "Test Deletion" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var list = List(i32).init(arena.allocator());
    defer list.free();

    try list.insert_node(10, 0);
    try list.insert_node(20, 1);
    try list.insert_node(30, 2);

    try list.delete_node(1);
    try std.testing.expectEqual(list.size, 2);
}

test "Test Delete Out of Bounds" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var list = List(i32).init(arena.allocator());
    defer list.free();

    try list.insert_node(10, 0);
    try list.insert_node(20, 1);

    try std.testing.expect(list.delete_node(3) == ListError.OutofBounds);
}

test "Test Empty List Deletion" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var list = List(i32).init(arena.allocator());
    defer list.free();

    try std.testing.expect(list.delete_node(0) == ListError.EmptyList);
}
