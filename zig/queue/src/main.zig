const std = @import("std");
const Queue = @import("queue.zig").Queue;

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var queue = Queue(i32).init(arena.allocator());
    try queue.enqueue(10);
    try queue.enqueue(20);
    try queue.enqueue(30);

    std.debug.print("head: {} \n", .{queue.head.?.data});
    std.debug.print("tail: {} \n", .{queue.tail.?.data});

    var dequeued_data = try queue.dequeue();
    std.debug.print("dequeued: {} \n", .{dequeued_data});

    dequeued_data = try queue.dequeue();
    std.debug.print("dequeued: {} \n", .{dequeued_data});

    dequeued_data = try queue.dequeue();
    std.debug.print("dequeued: {} \n", .{dequeued_data});

    dequeued_data = try queue.dequeue();
    std.debug.print("dequeued: {} \n", .{dequeued_data});
}
