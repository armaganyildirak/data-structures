const std = @import("std");
const List = @import("list.zig").List;

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var list = List(i32).init(arena.allocator());
    defer list.free();

    try list.insert_node(10, 0);
    try list.insert_node(20, 1);
    try list.insert_node(30, 2);
    list.print_list();

    try list.delete_node(0);
    list.print_list();

    try list.delete_node(1);
    list.print_list();

    try list.delete_node(0);
    list.print_list();
}
