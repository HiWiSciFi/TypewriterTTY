cc := g++
std := c++20
out := typewriter

all: clean typewriter

typewriter: main.cpp
	$(cc) main.cpp -std=$(std) -o $(out)

clean:
	rm -f $(out)
