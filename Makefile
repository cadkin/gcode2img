PROG = gcode2img

CXX = g++

LINKFLAGS =
CXXFLAGS = -g -Wall -MD -std=c++17

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(PROG)

%.o: %.c
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(PROG): $(OBJ)
	$(CXX) $(LINKFLAGS) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf $(PROG) $(OBJ) $(OBJ:.o=.d)

-include $(OBJ:.o=.d)
