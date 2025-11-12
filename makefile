# Directories
BIN_DIR = bin
BUILD_DIR = build
INCLUDE_DIR = include
VENDOR_DIR = vendor
LIB_DIR = lib
SRC_DIR = src

# Files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)
OUT = $(BIN_DIR)/main.exe

# Compiler and flags
CXX = clang++
CXXFLAGS = -I"$(INCLUDE_DIR)" -I"$(VENDOR_DIR)" -O3 -Wall -MMD -MP
LDFLAGS = -L"$(LIB_DIR)" -mwindows -lraylib -lopengl32 -lgdi32 -lwinmm

# Targets
.PHONY: all clean run

all: $(OUT)

$(OUT): $(OBJ) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if missing
$(BIN_DIR):
	mkdir $@

$(BUILD_DIR):
	mkdir $@

# Clean artifacts and executable
clean:
	del $(subst /,\,$(OUT))
	del $(subst /,\,$(OBJ))
	del $(subst /,\,$(DEP))

# Run the game
run: $(OUT)
	$(OUT)

# Include dependencies
-include $(DEP)
