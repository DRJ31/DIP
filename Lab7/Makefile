CPP = g++
CFLAGS = -Wall -Wextra -pedantic
LIBS = $(shell pkg-config --cflags --libs opencv) -fopenmp
RM = rm -f
BIN = lab7
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
IMGS = $(wildcard *.jpg) $(wildcard *.png) $(wildcard *.pgm)

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(BIN) $(OBJS) $(IMGS)

lab7: $(OBJS)
	$(CPP) -o $@ $^ $(LIBS) $(CFLAGS)

%.o: %.cpp
	$(CPP) -g -o $@ -c $< $(CFLAGS) -fopenmp 

%: %.cxx
	$(CPP) -o $@ $< $(LIBS) $(CFLAGS)
