const std = @import("std");
const HashTable = @import("hash_table.zig").HashTable;
const HashTableError = @import("hash_table.zig").HashTableError;

test "HashTable insert and retrieve" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var table = try HashTable(i32).init(arena.allocator(), 16);

    try table.put("key1", 42);
    const value1 = try table.get("key1");
    try std.testing.expect(value1 == 42);
}

test "HashTable update existing key" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var table = try HashTable(i32).init(arena.allocator(), 16);

    try table.put("key1", 42);
    try table.put("key1", 100);
    const value = try table.get("key1");
    try std.testing.expect(value == 100);
}

test "HashTable handle collisions" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var table = try HashTable(i32).init(arena.allocator(), 4);

    try table.put("key1", 42);
    try table.put("key2", 100);

    const value1 = try table.get("key1");
    const value2 = try table.get("key2");
    try std.testing.expect(value1 == 42);
    try std.testing.expect(value2 == 100);
}

test "HashTable remove existing key" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var table = try HashTable(i32).init(arena.allocator(), 16);

    try table.put("key1", 42);
    try table.remove("key1");

    const get_result = table.get("key1");
    try std.testing.expect(get_result == HashTableError.NodeNotFound);
}

test "HashTable remove non-existing key" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var table = try HashTable(i32).init(arena.allocator(), 16);

    const remove_result = table.remove("none");
    try std.testing.expect(remove_result == HashTableError.NodeNotFound);
}

test "HashTable handle multiple entries and chaining" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var table = try HashTable(i32).init(arena.allocator(), 4);

    try table.put("key1", 1);
    try table.put("key2", 2);
    try table.put("key3", 3);
    try table.put("key4", 4);

    const value1 = try table.get("key1");
    const value2 = try table.get("key2");
    const value3 = try table.get("key3");
    const value4 = try table.get("key4");

    try std.testing.expect(value1 == 1);
    try std.testing.expect(value2 == 2);
    try std.testing.expect(value3 == 3);
    try std.testing.expect(value4 == 4);
}

test "HashTable overwriting existing key in a chain" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    var table = try HashTable(i32).init(arena.allocator(), 4);

    try table.put("key1", 1);
    try table.put("key2", 2);
    try table.put("key1", 42);

    const value1 = try table.get("key1");
    const value2 = try table.get("key2");

    try std.testing.expect(value1 == 42);
    try std.testing.expect(value2 == 2);
}
