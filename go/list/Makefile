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

# Run tests with the race detector
race_test:
	@echo "Running tests with race detector..."
	@go test -race -v $(TEST_DIR)

# Run memory profiling (heap, cpu, etc.)
mem_profile:
	@echo "Running memory profile..."
	@go test -v -bench=. -cpuprofile=cpu.out -memprofile=mem.out

# Clean up binaries and other generated files
clean:
	@echo "Cleaning up..."
	@rm -f $(BINARY_NAME) cpu.out mem.out
	@go clean

# Format Go code
fmt:
	@echo "Formatting Go code..."
	@go fmt $(SRC_DIR)

# Check for common errors in the Go code
lint:
	@echo "Linting Go code..."
	@go vet $(SRC_DIR)

# Run gosec security checks
security:
	@echo "Running security checks with gosec..."
	@gosec ./...

# Check dependencies for known vulnerabilities
vulncheck:
	@echo "Checking dependencies for vulnerabilities..."
	@govulncheck -show verbose ./...

# Run the build, tests, and linter
all: fmt lint test build

.PHONY: build run test clean fmt lint all race_test mem_profile security vulncheck
