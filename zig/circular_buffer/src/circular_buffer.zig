const std = @import("std");

pub const BUFFER_SIZE = 256;

pub const CircularBufferError = error{
    BufferEmpty,
    BufferFull,
};

pub const CircularBuffer = struct {
    buffer: [BUFFER_SIZE]u8,
    head: usize,
    tail: usize,

    pub fn new() CircularBuffer {
        return CircularBuffer{
            .buffer = [_]u8{0} ** BUFFER_SIZE,
            .head = 0,
            .tail = 0,
        };
    }

    pub fn is_full(self: *const CircularBuffer) bool {
        return ((self.head + 1) % BUFFER_SIZE) == self.tail;
    }

    pub fn is_empty(self: *const CircularBuffer) bool {
        return self.head == self.tail;
    }

    pub fn write(self: *CircularBuffer, data: u8) !void {
        if (self.is_full()) {
            return CircularBufferError.BufferFull;
        }

        self.buffer[self.head] = data;
        self.head = (self.head + 1) % BUFFER_SIZE;
    }

    pub fn read(self: *CircularBuffer) !u8 {
        if (self.is_empty()) {
            return CircularBufferError.BufferEmpty;
        }

        const data = self.buffer[self.tail];
        self.tail = (self.tail + 1) % BUFFER_SIZE;

        return data;
    }
};
