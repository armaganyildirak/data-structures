const BUFFER_SIZE: usize = 255;

pub struct CircularBuffer {
    buffer: [u8; BUFFER_SIZE],
    head: usize,
    tail: usize,
}

#[derive(Debug, PartialEq)]
pub enum CircularBufferError {
    BufferEmpty,
    BufferFull,
}

impl Default for CircularBuffer {
    fn default() -> Self {
        Self::new()
    }
}

impl CircularBuffer {
    pub fn new() -> Self {
        Self {
            buffer: [0; BUFFER_SIZE],
            head: 0,
            tail: 0,
        }
    }

    pub fn is_full(&self) -> bool {
        ((self.head + 1) % BUFFER_SIZE) == self.tail
    }

    pub fn is_empty(&self) -> bool {
        self.head == self.tail
    }

    pub fn write(&mut self, data: u8) -> Result<(), CircularBufferError> {
        if self.is_full() {
            return Err(CircularBufferError::BufferFull);
        }

        self.buffer[self.head] = data;
        self.head = (self.head + 1) % BUFFER_SIZE;

        Ok(())
    }

    pub fn read(&mut self) -> Result<u8, CircularBufferError> {
        if self.is_empty() {
            return Err(CircularBufferError::BufferEmpty);
        }

        let data = self.buffer[self.tail];
        self.tail = (self.tail + 1) % BUFFER_SIZE;

        Ok(data)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_circular_buffer() {
        let mut cb = CircularBuffer::new();

        assert!(cb.is_empty());
        assert!(!cb.is_full());

        // Write to the buffer
        cb.write(42).unwrap();
        assert!(!cb.is_empty());
        assert_eq!(cb.read().unwrap(), 42);
        assert!(cb.is_empty());

        // Fill the buffer and check for full condition
        for i in 0..(BUFFER_SIZE - 1) {
            cb.write(i as u8).unwrap();
        }
        assert!(cb.is_full());

        // Check if it returns an error when trying to write to a full buffer
        assert_eq!(cb.write(255), Err(CircularBufferError::BufferFull));

        // Read all elements and check for empty condition
        for i in 0..(BUFFER_SIZE - 1) {
            assert_eq!(cb.read().unwrap(), i as u8);
        }
        assert!(cb.is_empty());
    }
}
