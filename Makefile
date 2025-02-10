arduino_env := nanoevery

RASPI_CXX = g++
RASPI_CXXFLAGS = -Wall -Werror
RASPI_CXX_STD = c++20
RASPI_BIN = typewriter
RASPI_OBJ_DIR = ./obj
RASPI_CPP = $(wildcard Raspi/*.cpp)
RASPI_OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
RASPI_DEP = $(OBJ:%.o=%.d)
RASPI_LDFLAGS = -l wiringPi

all: clean raspi arduino

arduino: arduino_upload

arduino_upload:
	pio run -d ./Arduino -e $(arduino_env) -t upload

$(RASPI_BIN): $(RASPI_OBJ)
	mkdir -p $(@D)
	$(RASPI_CXX) $(RASPI_CXX_FLAGS) -std=$(RASPI_CXX_STD) $^ $(RASPI_LDFLAGS) -o $@

-include $(RASPI_DEP)

$(RASPI_OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(RASPI_CXX) $(RASPI_CXX_FLAGS) -MMD -std=$(RASPI_CXX_STD) -c $< -o $@

.PHONY: clean

clean:
	-rm $(RASPI_BIN) $(RASPI_OBJ) $(RASPI_DEP)
