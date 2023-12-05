OBJS = fdtd1d.o initialize.o output_ez.o update_e.o update_h.o

HEADERS = fdtd.h

OPTS = -O3 -Wall

all: main

main: $(OBJS)
	g++ -o $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	g++ -c $< $(OPTS)

clean:
	rm -rf main *.o

.PHONY: all clean