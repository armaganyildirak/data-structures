const std = @import("std");
const Queue = @import("queue.zig").Queue;
const QueueError = @import("queue.zig").QueueError;

test "enqueue and dequeue operations" {
    var queue = Queue.init();

    try std.testing.expect(queue.head == null);
    try std.testing.expect(queue.tail == null);

    try queue.enqueue(10);
    try std.testing.expect(queue.head != null);
    try std.testing.expect(queue.tail != null);
    try std.testing.expect(queue.head.?.data == 10);
    try std.testing.expect(queue.tail.?.data == 10);

    try queue.enqueue(20);
    try std.testing.expect(queue.head != null);
    try std.testing.expect(queue.tail != null);
    try std.testing.expect(queue.head.?.data == 10);
    try std.testing.expect(queue.tail.?.data == 20);

    const dequeued1 = try queue.dequeue();
    try std.testing.expect(dequeued1 == 10);
    try std.testing.expect(queue.head != null);
    try std.testing.expect(queue.head.?.data == 20);

    const dequeued2 = try queue.dequeue();
    try std.testing.expect(dequeued2 == 20);
    try std.testing.expect(queue.head == null);
    try std.testing.expect(queue.tail == null);

    const result = queue.dequeue();
    try std.testing.expectError(QueueError.EmptyQueue, result);
}

test "dequeue on an empty queue" {
    var queue = Queue.init();

    const result = queue.dequeue();
    try std.testing.expectError(QueueError.EmptyQueue, result);
}
