CPP = g++
CFLAGS = -Wall -Wextra -pedantic
LIBS = $(shell pkg-config --cflags --libs opencv)
RM = rm -f
BIN = $(patsubst %.cpp,%,$(wildcard *.cpp))
EOBJS = $(patsubst enlarge/%.cpp,enlarge/%.o,$(wildcard enlarge/*.cpp))
ROBJS = $(patsubst reduce/%.cpp,reduce/%.o,$(wildcard reduce/*.cpp))
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
IMGS = $(wildcard *.jpg) $(wildcard *.png) $(wildcard *.pgm)

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(BIN) $(EOBJS) $(ROBJS) $(OBJS) $(IMGS)

negative: %: %.o
	$(CPP) -o $@ $< $(LIBS) $(CFLAGS)

enlargement: %: %.o $(EOBJS)
	$(CPP) -o $@ $^ $(LIBS) $(CFLAGS)

reduction: %: %.o $(ROBJS) enlarge/bilinear.o
	$(CPP) -o $@ $^ $(LIBS) $(CFLAGS)

%.o: %.cpp
	$(CPP) -g -o $@ -c $< $(CFLAGS)
