const std = @import("std");

pub const ListNode = struct {
    data: i32,
    next: ?*ListNode = null,
    prev: ?*ListNode = null,
};

pub const ListError = error{
    EmptyList,
    NodeNotFound,
};

pub const List = struct {
    head: ?*ListNode = null,

    pub fn init() List {
        return List{ .head = null };
    }

    pub fn insert_node(self: *List, data: i32) !void {
        const new_node = try std.heap.page_allocator.create(ListNode);
        new_node.* = ListNode{
            .data = data,
            .next = null,
            .prev = null,
        };

        if (self.head == null) {
            self.head = new_node;
        } else {
            var temp = self.head;
            while (temp.?.next != null) {
                temp = temp.?.next;
            }
            temp.?.next = new_node;
            new_node.prev = temp;
        }
    }

    pub fn delete_node(self: *List, data: i32) !void {
        if (self.head == null) {
            return ListError.EmptyList;
        }

        var temp = self.head;
        while (temp != null and temp.?.data != data) {
            temp = temp.?.next;
        }
        if (temp == null) {
            return ListError.NodeNotFound;
        }
        if (temp == self.head) {
            self.head = temp.?.next;
            if (self.head != null) {
                self.head.?.prev = null;
            }
        } else {
            if (temp.?.prev != null) {
                temp.?.prev.?.next = temp.?.next;
            }
            if (temp.?.next != null) {
                temp.?.next.?.prev = temp.?.prev;
            }
        }
    }

    pub fn print_list(self: *List) void {
        var temp = self.head;
        while (temp != null) {
            std.debug.print("{} -> ", .{temp.?.data});
            temp = temp.?.next;
        }
        std.debug.print("NULL\n", .{});
    }
};
