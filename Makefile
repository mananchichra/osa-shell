CC = gcc
CFLAGS = -Wall

# List of object files
OBJS = shell.o builtins.o history.o 

# Target executable
TARGET = my_shell

# Default target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
