# Define the cargo command
CARGO = cargo

# Default target: build the project
all: build

# Build the project
build:
	$(CARGO) build

# Run the tests
test:
	$(CARGO) test

# Clean the project
clean:
	$(CARGO) clean

# Run clippy for linting
lint:
	$(CARGO) clippy -- -D warnings

# Generate documentation
fmt:
	$(CARGO) fmt --all
