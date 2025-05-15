CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -MMD -MP
LDFLAGS = -L$(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm

INCLUDE_DIR = include
LIB_DIR = lib
SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
OUT = snake.exe

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-@del $(BUILD_DIR)\*.o 2>nul
	-@del $(BUILD_DIR)\*.d 2>nul
	-@del $(OUT) 2>nul

-include $(OBJ:.o=.d)
