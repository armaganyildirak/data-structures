const std = @import("std");
const List = @import("list.zig").List;
const ListError = @import("list.zig").ListError;

test "List initialization should set head to null" {
    const list = List.init();
    try std.testing.expect(list.head == null);
}

test "Inserting multiple nodes should link them correctly" {
    var list = List.init();
    try list.insert_node(10);
    try list.insert_node(20);
    try list.insert_node(30);

    const head = list.head;
    try std.testing.expect(head != null);
    try std.testing.expect(head.?.data == 10);
    try std.testing.expect(head.?.prev == null);
    try std.testing.expect(head.?.next != null);

    const second_node = head.?.next;
    try std.testing.expect(second_node != null);
    try std.testing.expect(second_node.?.data == 20);
    try std.testing.expect(second_node.?.prev == head);
    try std.testing.expect(second_node.?.next != null);

    const third_node = second_node.?.next;
    try std.testing.expect(third_node != null);
    try std.testing.expect(third_node.?.data == 30);
    try std.testing.expect(third_node.?.prev == second_node);
    try std.testing.expect(third_node.?.next == null);
}

test "Deleting a node from an empty list should throw an exception" {
    var list = List.init();
    const result = list.delete_node(10);
    try std.testing.expectError(ListError.EmptyList, result);
}

test "Deleting a non-existent node should throw an exception" {
    var list = List.init();
    try list.insert_node(10);
    try list.insert_node(20);
    const result = list.delete_node(30);
    try std.testing.expectError(ListError.NodeNotFound, result);
}

test "Deleting a node should update the list correctly" {
    var list = List.init();
    try list.insert_node(10);
    try list.insert_node(20);
    try list.insert_node(30);

    try list.delete_node(20);

    try std.testing.expect(list.head.?.data == 10);

    try std.testing.expect(list.head.?.next.?.data == 30);
    try std.testing.expect(list.head.?.next.?.prev == list.head);
}
