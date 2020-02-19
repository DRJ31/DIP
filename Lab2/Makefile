CPP = g++
BIN = $(patsubst %.cpp,%,$(wildcard *.cpp))
CFLAGS = $(shell pkg-config --cflags --libs opencv)
RM = rm -f

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(BIN)

%: %.cpp
	$(CPP) -o $@ $< $(CFLAGS)
