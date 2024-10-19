const std = @import("std");
const CircularBuffer = @import("circular_buffer.zig").CircularBuffer;

pub fn main() !void {
    var cb = CircularBuffer.new();

    for (0..5) |i| {
        cb.write(@truncate(i + 1)) catch |err| {
            std.debug.print("Error: {}\n", .{err});
        };
    }

    while (!cb.is_empty()) {
        const result = cb.read() catch |err| {
            std.debug.print("Error: {}\n", .{err});
            return;
        };
        std.debug.print("Read: {}\n", .{result});
    }

    const result = cb.read() catch |err| {
        std.debug.print("Error: {}\n", .{err});
        return;
    };
    std.debug.print("Read: {}\n", .{result});
}
