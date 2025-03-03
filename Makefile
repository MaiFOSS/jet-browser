
# Makefile
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`
LIBS = `pkg-config --libs gtk+-3.0 webkit2gtk-4.0`
SRC_DIR = src
BIN_DIR = bin
TARGET = $(BIN_DIR)/browser

# Source files
SOURCES = $(SRC_DIR)/browser.c $(SRC_DIR)/tabs.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean