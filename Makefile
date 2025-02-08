# Compiler and flags
CXX = g++ -g
CXXFLAGS = -Wall -Werror -pedantic -Wshadow -std=c++14

# SDL2 flags (includes and libraries)
LDFLAGS = -lssl -lcrypto
INCLUDE_DIR= -I /usr/include

BUILDDIR = build
SRCDIR = src

# The source and target files
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
EXEC = ssltuts

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(BUILDDIR)/$(EXEC) $(LDFLAGS)

# Compiling the object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@

run: $(EXEC)
	./$(BUILDDIR)/$(EXEC)

# Clean up
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXEC)

