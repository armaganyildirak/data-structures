const std = @import("std");

pub const QueueError = error{
    EmptyQueue,
};

pub fn Queue(comptime T: type) type {
    return struct {
        const This = @This();
        const QueueNode = struct {
            data: T,
            next: ?*QueueNode,
        };

        gpa: std.mem.Allocator,
        head: ?*QueueNode = null,
        tail: ?*QueueNode = null,
        size: u32 = 0,

        pub fn init(gpa: std.mem.Allocator) This {
            return This{
                .gpa = gpa,
                .head = null,
                .tail = null,
                .size = 0,
            };
        }

        pub fn enqueue(this: *This, data: T) !void {
            const new_node = try this.gpa.create(QueueNode);
            new_node.* = QueueNode{
                .data = data,
                .next = null,
            };
            if (this.tail == null) {
                this.head = new_node;
                this.tail = new_node;
                this.size += 1;
            } else {
                if (this.tail) |tail| {
                    tail.next = new_node;
                    this.tail = new_node;
                    this.size += 1;
                }
            }
        }

        pub fn dequeue(this: *This) !T {
            if (this.head) |head| {
                const dequeued_data = head.data;
                this.head = head.next;
                if (this.head == null) {
                    this.tail = null;
                }
                this.gpa.destroy(head);
                this.size -= 1;
                return dequeued_data;
            } else {
                return QueueError.EmptyQueue;
            }
        }

        pub fn free(this: *This) void {
            while (this.head) |head| {
                this.head = head.next;
                if (this.head == null) {
                    this.tail = null;
                }
                this.size -= 1;
                this.gpa.destroy(head);
            }
        }
    };
}
