# Variables
BINARY_NAME=app
SRC_DIR=.
TEST_DIR=.
GO_FILES=$(SRC_DIR)/*.go

# Default target: build the binary
build: $(GO_FILES)
	@echo "Building the application..."
	@go build -o $(BINARY_NAME) $(SRC_DIR)

# Run the binary
run: build
	@echo "Running the application..."
	@./$(BINARY_NAME)

# Run tests
test:
	@echo "Running tests..."
	@go test -v $(TEST_DIR)

# Clean up binaries and other generated files
clean:
	@echo "Cleaning up..."
	@rm -f $(BINARY_NAME)
	@go clean

# Format Go code
fmt:
	@echo "Formatting Go code..."
	@go fmt $(SRC_DIR)

# Check for common errors in the Go code
lint:
	@echo "Linting Go code..."
	@go vet $(SRC_DIR)

# Run the build, tests, and linter
all: fmt lint test build

.PHONY: build run test clean fmt lint all