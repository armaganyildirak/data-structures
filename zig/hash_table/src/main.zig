const std = @import("std");
const HashTable = @import("hash_table.zig").HashTable;

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var ht = try HashTable(i32).init(arena.allocator(), 5);

    try ht.put("fruit", 500);
    try ht.put("meat", 700);

    const g1 = try ht.get("fruit");
    std.debug.print("{}\n", .{g1});

    try ht.remove("meat");
    const g2 = try ht.get("meat");
    std.debug.print("{}\n", .{g2});
}
