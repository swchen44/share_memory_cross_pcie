# Makefile

CC = clang
CFLAGS = -Wall -Wextra -g -O2 -std=c++14
ASAN_FLAGS = -fsanitize=address,undefined
GTEST_FLAGS = -lgtest -pthread -I/opt/homebrew/Cellar/googletest/1.16.0/include -L/opt/homebrew/Cellar/googletest/1.16.0/lib

# Source files
SRCS = main.c emi_writer.c emi_reader.c

# Executable name
TARGET = emi_sim

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Create object files
%.o: %.c
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(OBJS) -o $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Test using gtest (example - you'll need to create test files)
test:
	clang++ $(CFLAGS) $(ASAN_FLAGS) $(GTEST_FLAGS) test.c -o test
	./test

.PHONY: all run clean test
