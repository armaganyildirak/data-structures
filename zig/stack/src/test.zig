const std = @import("std");
const Stack = @import("stack.zig").Stack;

test "test stack operations" {
    var stack = Stack(i32).init(std.testing.allocator);

    try stack.push(10);
    try stack.push(20);
    try stack.push(30);

    const top_value = try stack.peek();
    try std.testing.expectEqual(30, top_value);

    const pop_value1 = try stack.pop();
    try std.testing.expectEqual(30, pop_value1);

    const pop_value2 = try stack.pop();
    try std.testing.expectEqual(20, pop_value2);

    const pop_value3 = try stack.pop();
    try std.testing.expectEqual(10, pop_value3);

    try std.testing.expect(stack.is_empty());

    stack.free();
}

test "test stack underflow" {
    var stack = Stack(i32).init(std.testing.allocator);

    try std.testing.expect(stack.is_empty());

    stack.free();
}
