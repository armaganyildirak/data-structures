const std = @import("std");

pub const StackNode = struct {
    data: i32,
    next: ?*StackNode = null,
};

pub const Stack = struct {
    top: ?*StackNode = null,

    pub fn init() Stack {
        return Stack{ .top = null };
    }

    pub fn push(self: *Stack, value: anytype) !void {
        const new_node = try std.heap.page_allocator.create(StackNode);
        new_node.* = StackNode{
            .data = value,
            .next = self.top,
        };
        self.top = new_node;
    }

    pub fn pop(self: *Stack) i32 {
        if (self.is_empty()) {
            std.debug.panic("Stack is empty\n", .{});
        }
        const node = self.top;
        self.top = node.?.next;
        return node.?.data;
    }

    pub fn peek(self: *Stack) i32 {
        if (self.is_empty()) {
            std.debug.panic("Stack is empty\n", .{});
        }
        return self.top.?.data;
    }

    pub fn is_empty(self: *Stack) bool {
        return self.top == null;
    }

    pub fn free(self: *Stack) void {
        while (self.top != null) {
            const node = self.top;
            self.top = node.?.next;
            std.heap.page_allocator.destroy(node.?);
        }
    }
};
