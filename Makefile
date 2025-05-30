
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
ASM = nasm
ASMFLAGS = -f elf64

SRC_DIR = src
BUILD_DIR = .build
BIN = $(BUILD_DIR)/alloc

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
ASMS = $(wildcard $(SRC_DIR)/*.asm)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o) $(ASMS:$(SRC_DIR)/%.asm=$(BUILD_DIR)/%.o)

all: build

build: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

run: build
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build clean run
