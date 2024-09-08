# Variables
ZIG=zig
SRC_DIR=./src
TEST_FILE=$(SRC_DIR)/test.zig
OUT_BINARY=stack

# Default target: run tests
test:
	@echo "Running tests..."
	$(ZIG) test $(TEST_FILE)

# Build the executable for the stack
build:
	@echo "Building stack executable..."
	$(ZIG) build-exe $(SRC_DIR)/main.zig -O ReleaseSafe --name $(OUT_BINARY)

# Run the built executable
run: build
	@echo "Running stack executable..."
	./$(OUT_BINARY)

# Clean the build files
clean:
	@echo "Cleaning up..."
	rm -rf $(OUT_BINARY) $(OUT_BINARY).o zig-out .zig-cache

# Run the test and build all together
all: test build run

.PHONY: test build run clean all