const std = @import("std");

pub const ListError = error{
    EmptyList,
    NodeNotFound,
    OutofBounds,
};

pub fn List(comptime T: type) type {
    return struct {
        const This = @This();
        const ListNode = struct {
            data: T,
            next: ?*ListNode,
            prev: ?*ListNode,
        };

        gpa: std.mem.Allocator,
        head: ?*ListNode = null,
        size: u32 = 0,

        pub fn init(gpa: std.mem.Allocator) This {
            return This{
                .gpa = gpa,
                .head = null,
                .size = 0,
            };
        }

        pub fn insert_node(this: *This, data: T, idx: u32) !void {
            const new_node = try this.gpa.create(ListNode);
            new_node.* = ListNode{
                .data = data,
                .next = null,
                .prev = null,
            };

            if (idx > this.size) {
                return ListError.OutofBounds;
            }

            if (idx == 0) {
                if (this.head) |head| {
                    new_node.next = head;
                    head.prev = new_node;
                } else {
                    this.head = new_node;
                }
            } else {
                var current = this.head;
                var i: u32 = 0;
                while (i < idx - 1) : (i += 1) {
                    if (current) |temp| {
                        current = temp.next;
                    }
                }
                if (current) |temp| {
                    new_node.next = temp.next;
                    new_node.prev = temp;

                    if (temp.next) |next| {
                        next.prev = new_node;
                    }
                    temp.next = new_node;
                }
            }
            this.size += 1;
        }

        pub fn delete_node(this: *This, idx: u32) !void {
            if (this.size == 0) {
                return ListError.EmptyList;
            }

            if (idx >= this.size) {
                return ListError.OutofBounds;
            }

            var current = this.head;
            var i: u32 = 0;
            while (i < idx) : (i += 1) {
                if (current) |temp| {
                    current = temp.next;
                }
            }

            if (current) |temp| {
                if (temp.prev) |prev| {
                    prev.next = temp.next;
                } else {
                    this.head = temp.next;
                }

                if (temp.next) |next| {
                    next.prev = temp.prev;
                }

                this.gpa.destroy(temp);
                this.size -= 1;
            }
        }

        pub fn print_list(this: *This) void {
            var current = this.head;
            while (current) |node| {
                std.debug.print("{} -> ", .{node.data});
                current = node.next;
            }
            std.debug.print("NULL\n", .{});
        }

        pub fn free(this: *This) void {
            while (this.head) |head| {
                this.head = head.next;
                head.prev = null;
                this.gpa.destroy(head);
            }
        }
    };
}
