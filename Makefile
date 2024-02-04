CC := g++
CFLAGS := -std=c++17 -Wall
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR := src
OBJ_DIR := obj

# List of source files
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: main run clean

main: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o main $^ $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./main

clean:
	rm -f main $(OBJ_DIR)/**/*.o $(OBJ_DIR)/*.o
	find $(OBJ_DIR) -type d -empty -delete