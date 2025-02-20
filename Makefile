arduino_env := nanoevery

CXX = g++
CXX_FLAGS = -Wall -Wextra -Wpedantic -Werror -I./Raspi/dependencies/toml11/single_include
CXX_STD = c++20
BIN = typewriter
OBJ_DIR = ./obj
CPP = $(wildcard Raspi/*.cpp)
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)
LDFLAGS = -s -l wiringPi

all: raspi arduino

arduino: arduino_upload

arduino_upload:
	pio run -d ./Arduino -e $(arduino_env) -t upload

raspi: $(BIN)

$(BIN): $(OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -std=$(CXX_STD) $^ $(LDFLAGS) -o $@

-include $(DEP)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -std=$(CXX_STD) -c $< -o $@

.PHONY: clean

clean:
	-rm $(BIN) $(OBJ) $(DEP)
