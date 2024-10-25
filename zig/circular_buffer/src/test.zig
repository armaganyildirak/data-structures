const std = @import("std");
const CircularBuffer = @import("circular_buffer.zig").CircularBuffer;
const CircularBufferError = @import("circular_buffer.zig").CircularBufferError;
const BUFFER_SIZE = @import("circular_buffer.zig").BUFFER_SIZE;

test "test circular buffer basic functionality" {
    var cb = CircularBuffer.new();

    try std.testing.expect(cb.is_empty());
    try std.testing.expect(!cb.is_full());

    try cb.write(42);
    try std.testing.expect(!cb.is_empty());

    const data = try cb.read();
    try std.testing.expectEqual(data, 42);
    try std.testing.expect(cb.is_empty());
}

test "test circular buffer full condition" {
    var cb = CircularBuffer.new();

    for (0..(BUFFER_SIZE - 1)) |i| {
        try cb.write(@truncate(i));
    }

    try std.testing.expect(cb.is_full());

    const result = cb.write(255);
    try std.testing.expectError(CircularBufferError.BufferFull, result);
}

test "test circular buffer empty condition after full read" {
    var cb = CircularBuffer.new();

    for (0..(BUFFER_SIZE - 1)) |i| {
        try cb.write(@truncate(i));
    }

    for (0..(BUFFER_SIZE - 1)) |i| {
        const data = try cb.read();
        try std.testing.expectEqual(i, data);
    }

    try std.testing.expect(cb.is_empty());

    const result = cb.read();
    try std.testing.expectError(CircularBufferError.BufferEmpty, result);
}

test "test circular buffer wraparound" {
    var cb = CircularBuffer.new();

    for (0..(BUFFER_SIZE / 2)) |i| {
        try cb.write(@truncate(i));
    }

    for (0..(BUFFER_SIZE / 4)) |i| {
        const data = try cb.read();
        try std.testing.expectEqual(i, data);
    }

    for (BUFFER_SIZE / 2..(BUFFER_SIZE / 2 + BUFFER_SIZE / 4)) |i| {
        try cb.write(@truncate(i));
    }

    for (BUFFER_SIZE / 4..(BUFFER_SIZE / 2 + BUFFER_SIZE / 4)) |i| {
        const data = try cb.read();
        try std.testing.expectEqual(i, data);
    }
}
