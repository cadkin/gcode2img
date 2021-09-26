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

.PHONY: clean ex

ex:
	./ex/gen_example.sh
	cp ./ex/out1.png ./
	cp ./ex/out2.png ./
	cp ./ex/out3.png ./
	cp ./ex/out4.png ./
	cp ./ex/out5.png ./

clean:
	rm -rf $(PROG) $(OBJ) $(OBJ:.o=.d)

-include $(OBJ:.o=.d)
