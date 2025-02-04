arduino_env := mega

raspi_sources := Raspi/main.cpp Raspi/Keymap.hpp Raspi/PseudoTTY.cpp Raspi/PseudoTTY.hpp

raspi_cpp_std := c++20
raspi_out := typewriter

all: clean raspi arduino

clean:
	rm -f $(raspi_out)


raspi: raspi_build

raspi_build: $(raspi_sources)
	g++ $(raspi_sources) -std=$(raspi_cpp_std) -l wiringPi -o $(raspi_out)

arduino: arduino_upload

arduino_upload:
	pio run -d ./Arduino -e $(arduino_env) -t upload
