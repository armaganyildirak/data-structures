const std = @import("std");

pub const StackError = error{
    StackEmpty,
};

pub fn Stack(comptime T: type) type {
    return struct {
        const This = @This();
        const StackNode = struct {
            data: T,
            next: ?*StackNode,
        };

        gpa: std.mem.Allocator,
        top: ?*StackNode = null,

        pub fn init(gpa: std.mem.Allocator) This {
            return This{
                .gpa = gpa,
                .top = null,
            };
        }

        pub fn push(this: *This, data: T) !void {
            const new_node = try this.gpa.create(StackNode);
            new_node.* = StackNode{
                .data = data,
                .next = this.top,
            };
            this.top = new_node;
        }

        pub fn pop(this: *This) !T {
            if (this.top) |top| {
                const popped_value = top.data;
                this.top = top.next;
                this.gpa.destroy(top);
                return popped_value;
            } else {
                return StackError.StackEmpty;
            }
        }

        pub fn peek(this: *This) !T {
            if (this.top) |top| {
                return top.data;
            } else {
                return StackError.StackEmpty;
            }
        }

        pub fn is_empty(this: *This) bool {
            return this.top == null;
        }

        pub fn free(this: *This) void {
            while (this.top) |top| {
                this.top = top.next;
                this.gpa.destroy(top);
            }
        }
    };
}
