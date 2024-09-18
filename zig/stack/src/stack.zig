const std = @import("std");

pub const StackNode = struct {
    data: i32,
    next: ?*StackNode = null,
};

pub const StackError = error{
    StackEmpty,
};

pub const Stack = struct {
    top: ?*StackNode = null,

    pub fn init() Stack {
        return Stack{ .top = null };
    }

    pub fn push(self: *Stack, data: i32) !void {
        const new_node = try std.heap.page_allocator.create(StackNode);
        new_node.* = StackNode{
            .data = data,
            .next = self.top,
        };
        self.top = new_node;
    }

    pub fn pop(self: *Stack) !i32 {
        if (self.is_empty()) {
            return StackError.StackEmpty;
        }
        const temp = self.top;
        const popped_value = temp.?.data;
        self.top = temp.?.next;
        std.heap.page_allocator.destroy(temp.?);
        return popped_value;
    }

    pub fn peek(self: *Stack) !i32 {
        if (self.is_empty()) {
            return StackError.StackEmpty;
        }
        return self.top.?.data;
    }

    pub fn is_empty(self: *Stack) bool {
        return self.top == null;
    }

    pub fn free(self: *Stack) void {
        while (self.top != null) {
            const temp = self.top;
            self.top = temp.?.next;
            std.heap.page_allocator.destroy(temp.?);
        }
    }
};
