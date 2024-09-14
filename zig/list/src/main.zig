const std = @import("std");
const List = @import("list.zig").List;

pub fn main() !void {
    var list = List.init();
    try list.insert_node(10);
    try list.insert_node(20);
    try list.insert_node(30);
    list.print_list();

    try list.delete_node(10);
    list.print_list();

    try list.delete_node(30);
    list.print_list();

    try list.delete_node(20);
    list.print_list();
}
