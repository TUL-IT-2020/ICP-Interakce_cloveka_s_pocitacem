# Makefile for icp.cpp

# Compiler
CXX = g++

# Default to C++17 if CXX_STD is not set
CXX_STD ?= c++17

# Compiler flags
CXXFLAGS = -std=$(CXX_STD) `pkg-config --cflags opencv4`

# Linker flags
LDFLAGS = `pkg-config --libs opencv4`

# Target executable
TARGET = App.out

# Source files
#SRCS = main_threads.cpp
SRCS = App.cpp

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