# Variables
ZIG=zig
SRC_DIR=./src
TEST_FILE=$(SRC_DIR)/test.zig
OUT_BINARY=circular_buffer

# Default target: run tests
test:
	@echo "Running tests..."
	$(ZIG) test $(TEST_FILE)

# Build the executable for the circular_buffer
build:
	@echo "Building circular_buffer executable..."
	$(ZIG) build-exe $(SRC_DIR)/main.zig -O ReleaseSafe --name $(OUT_BINARY)

# Run the built executable
run: build
	@echo "Running circular_buffer executable..."
	./$(OUT_BINARY)

# Format the code
fmt:
	@echo "Formatting code..."
	$(ZIG) fmt $(SRC_DIR)

# Clean the build files
clean:
	@echo "Cleaning up..."
	rm -rf $(OUT_BINARY) $(OUT_BINARY).o zig-out .zig-cache

# Run the test and build all together
all: test build run

.PHONY: test build run fmt clean all