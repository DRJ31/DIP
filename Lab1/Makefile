CC = gcc
CPP = g++
BIN = $(patsubst %.c,%,$(wildcard *.c)) $(patsubst %.cpp,%,$(wildcard *.cpp))
CFLAGS = $(shell pkg-config --cflags --libs opencv)
RM = rm -f

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(BIN)

%: %.c
	$(CC) -o $@ $<

%: %.cpp
	$(CPP) -o $@ $< $(CFLAGS)
