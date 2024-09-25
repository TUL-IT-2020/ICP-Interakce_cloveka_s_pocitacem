# Makefile for icp.cpp

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 `pkg-config --cflags opencv4`

# Linker flags
LDFLAGS = `pkg-config --libs opencv4`

# Target executable
TARGET = icp.out

# Source files
SRCS = icp.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the application
run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean run