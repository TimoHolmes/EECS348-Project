# Makefile

# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Header files directory
INCLUDES = -I.

# Source files
SOURCES = main.cpp errorHandler.cpp expression.cpp historyLog.cpp UI.cpp

# Object files to generate
OBJECTS = $(SOURCES:.cpp=.o)

# Executable to build
EXECUTABLE = myprogram

# Default target
all: $(EXECUTABLE)

# Linking all the object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Rule to create object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up all compiled files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Dependency rule for header files changes
%.o: %.h
