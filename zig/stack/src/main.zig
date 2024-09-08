const std = @import("std");
const Stack = @import("stack.zig").Stack;

pub fn main() !void {
    var stack = Stack.init();

    try stack.push(10);
    try stack.push(20);
    try stack.push(30);

    const peeked_value = stack.peek();
    std.debug.print("Peeked: {}\n", .{peeked_value});

    var popped_value = stack.pop();
    std.debug.print("Popped: {}\n", .{popped_value});

    popped_value = stack.pop();
    std.debug.print("Popped: {}\n", .{popped_value});

    popped_value = stack.pop();
    std.debug.print("Popped: {}\n", .{popped_value});

    if (stack.is_empty()) {
        std.debug.print("Stack is empty\n", .{});
    }

    stack.free();
}
