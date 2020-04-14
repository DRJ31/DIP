CPP = g++
CFLAGS = -Wall -Wextra -pedantic
LIBS = $(shell pkg-config --cflags --libs opencv) -fopenmp
RM = rm -f
BIN = lab6
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
IMGS = $(wildcard *.jpg) $(wildcard *.png) $(wildcard *.pgm)

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(BIN) $(OBJS) $(IMGS)

$(BIN): $(OBJS)
	$(CPP) -o $@ $^ $(LIBS) $(CFLAGS)

%.o: %.cpp
	$(CPP) -g -o $@ -c $< $(CFLAGS) -fopenmp 
