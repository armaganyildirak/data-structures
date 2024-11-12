const std = @import("std");

pub const HashTableError = error{
    NodeNotFound,
};

pub fn HashTable(comptime T: type) type {
    return struct {
        const This = @This();
        const HashEntry = struct {
            value: T,
            key: []const u8,
            next: ?*HashEntry,
        };

        gpa: std.mem.Allocator,
        buckets: []?*HashEntry,
        size: usize,

        pub fn init(gpa: std.mem.Allocator, size: usize) !This {
            const table = This{
                .gpa = gpa,
                .buckets = try gpa.alloc(?*HashEntry, size),
                .size = size,
            };
            var i: u32 = 0;
            while (i < table.size) : (i += 1) {
                table.buckets[i] = null;
            }

            return table;
        }

        fn hash_function(key: []const u8) u64 {
            var hash: u64 = 5381;
            for (key) |c| {
                hash = (hash << 5) + hash + c;
            }
            return hash;
        }

        pub fn put(this: *This, key: []const u8, value: T) !void {
            const index = hash_function(key) % this.size;
            var current = this.buckets[index];

            while (current) |entry| {
                if (std.mem.eql(u8, entry.key, key)) {
                    entry.value = value;
                    return;
                }

                current = entry.next;
            }

            const new_entry = try this.gpa.create(HashEntry);
            new_entry.* = HashEntry{
                .key = key,
                .value = value,
                .next = this.buckets[index],
            };
            this.buckets[index] = new_entry;
        }

        pub fn get(this: *This, key: []const u8) !T {
            const index = hash_function(key) % this.size;
            var current = this.buckets[index];

            while (current) |entry| {
                if (std.mem.eql(u8, entry.key, key)) {
                    return entry.value;
                }
                current = entry.next;
            }

            return HashTableError.NodeNotFound;
        }

        pub fn remove(this: *This, key: []const u8) !void {
            const index = hash_function(key) % this.size;
            var current = this.buckets[index];
            var prev: ?*HashEntry = null;

            while (current) |entry| {
                if (std.mem.eql(u8, entry.key, key)) {
                    if (prev) |p| {
                        p.next = entry.next;
                    } else {
                        this.buckets[index] = entry.next;
                    }
                    this.gpa.destroy(entry);
                    return;
                }
                prev = entry;
                current = entry.next;
            }

            return HashTableError.NodeNotFound;
        }
    };
}
