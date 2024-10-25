const std = @import("std");
const Stack = @import("stack.zig").Stack;
const StackError = @import("stack.zig").StackError;

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var stack = Stack(i32).init(arena.allocator());
    defer stack.free();

    try stack.push(10);
    try stack.push(20);
    try stack.push(30);

    const peeked_value = try stack.peek();
    std.debug.print("Peeked: {}\n", .{peeked_value});

    var popped_value = try stack.pop();
    std.debug.print("Popped: {}\n", .{popped_value});

    popped_value = try stack.pop();
    std.debug.print("Popped: {}\n", .{popped_value});

    popped_value = try stack.pop();
    std.debug.print("Popped: {}\n", .{popped_value});

    if (stack.is_empty()) {
        return StackError.StackEmpty;
    }
}
