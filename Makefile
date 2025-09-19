# Debian-only Makefile for building tests against lib/libtree.so

# === Compiler and Flags ===
CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11 -g -Iinclude -D_POSIX_C_SOURCE=200809L
LDFLAGS  := -Wl,-rpath,'$$ORIGIN/../lib' -Llib
# NOTE: The LDFLAGS ensure the program can find libworldgen.so at runtime.
# The '$$ORIGIN' variable refers to the folder containing the final executable.
# This makes the runtime linker look in ../lib (relative to the binary) for libworldgen.so,
# instead of relying on system-wide library paths.

# === Check Unit Test Flags (via pkg-config) ===
CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null)
CHECK_LIBS   := $(shell pkg-config --libs   check 2>/dev/null)

# === Directories ===
BIN_DIR := bin

# === 🔧 STUDENTS: Fill these in ===

# Test source files (should include main)
TEST_SRC :=          # e.g., tests/test_main.c tests/test_controller_access.c

# Source files under test
SRC :=               # e.g., src/dungeon_controller.c src/tree.c

# Combined sources
ALL_SRC := $(TEST_SRC) $(SRC)

# Output binary
TARGET :=            # e.g., $(BIN_DIR)/a1_tests

# === Build rules ===

.PHONY: all
all: $(TARGET)

# Ensure bin directory exists
$(BIN_DIR):
	mkdir -p $@

# 🔧 STUDENTS: Fill in the rule to build $(TARGET)

# $(TARGET) should depend on $(ALL_SRC) and $(BIN_DIR)
$(TARGET):            # e.g., $(BIN_DIR) $(ALL_SRC)
	# 🔧 Replace this with your compiler command:
	# Example:
	# $(CC) $(CFLAGS) $(CHECK_CFLAGS) -o $@ $(ALL_SRC) $(LDFLAGS) -lworldgen $(CHECK_LIBS)
	@echo "🔧 TODO: build command goes here"


# 🔧 STUDENTS: Fill in the rule to run your test binary
.PHONY: test
test: $(TARGET)
	@echo "==> Running unit tests"
	# 🔧 Example:
	# @$(TARGET)
	@echo "🔧 TODO: run command goes here"




# === The targets below are working and don't need editing ===

.PHONY: lint
lint:
	cppcheck --enable=all --inconclusive --std=c11 --quiet \
		--suppress=missingIncludeSystem \
		-Iinclude src tests

.PHONY: memcheck
memcheck: test
	valgrind --leak-check=full --error-exitcode=1 $(TARGET)

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

.PHONY: setup-lib
setup-lib:
	@arch=$$(dpkg --print-architecture 2>/dev/null || uname -m); \
	if [ "$$arch" = "amd64" ] || [ "$$arch" = "x86_64" ]; then \
		cp lib/libworldgen-linux-amd64.so lib/libtree.so; \
		echo "Using libworldgen-linux-amd64.so"; \
	else \
		cp lib/libworldgen-linux-arm64.so lib/libtree.so; \
		echo "Using libworldgen-linux-arm64.so"; \
	fi