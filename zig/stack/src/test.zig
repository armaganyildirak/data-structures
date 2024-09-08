const std = @import("std");
const Stack = @import("stack.zig").Stack;

test "test stack operations" {
    var stack = Stack.init();

    try stack.push(10);
    try stack.push(20);
    try stack.push(30);

    const top_value = stack.peek();
    try std.testing.expectEqual(30, top_value);

    const pop_value1 = stack.pop();
    try std.testing.expectEqual(30, pop_value1);

    const pop_value2 = stack.pop();
    try std.testing.expectEqual(20, pop_value2);

    const pop_value3 = stack.pop();
    try std.testing.expectEqual(10, pop_value3);

    try std.testing.expect(stack.is_empty());

    stack.free();
}

test "test stack underflow" {
    var stack = Stack.init();

    try std.testing.expect(stack.is_empty());

    stack.free();
}
