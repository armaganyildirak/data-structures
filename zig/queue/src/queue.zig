const std = @import("std");

pub const QueueNode = struct {
    data: i32,
    next: ?*QueueNode = null,
};

pub const QueueError = error{
    EmptyQueue,
};

pub const Queue = struct {
    head: ?*QueueNode = null,
    tail: ?*QueueNode = null,

    pub fn init() Queue {
        return Queue{ .head = null, .tail = null };
    }

    pub fn enqueue(self: *Queue, data: i32) !void {
        const new_node = try std.heap.page_allocator.create(QueueNode);
        new_node.* = QueueNode{
            .data = data,
            .next = null,
        };
        if (self.tail == null) {
            self.head = new_node;
            self.tail = new_node;
        } else {
            self.tail.?.next = new_node;
            self.tail = new_node;
        }
    }

    pub fn dequeue(self: *Queue) !i32 {
        if (self.head == null) {
            return QueueError.EmptyQueue;
        }
        const dequeued_data = self.head.?.data;
        const old_head = self.head;
        self.head = self.head.?.next;
        if (self.head == null) {
            self.tail = null;
        }
        std.heap.page_allocator.destroy(old_head.?);
        return dequeued_data;
    }
};
