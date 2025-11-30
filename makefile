# Directories
BIN_DIR = bin
BUILD_DIR = build
INCLUDE_DIR = include
SRC_DIR = src

# Files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)
OUT = $(BIN_DIR)/snake

# Compiler and flags
CXX = g++
CXXFLAGS = -I"$(INCLUDE_DIR)" -O2 -Wall -MMD -MP
CXXFLAGS += $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

# Targets
.PHONY: all clean run

all: $(OUT)

$(OUT): $(OBJ) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if missing
$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

# Clean artifacts and executables
clean:
	rm -f $(OUT) $(OBJ) $(DEP)
	rm -rf $(BIN_DIR) $(BUILD_DIR)

# Run the game
run: $(OUT)
	$(OUT)

# Include dependencies
-include $(DEP)
