OBJS = fdtd1d.o initialize.o initialize_plasma.o output_E.o update_E.o update_H.o \
 update_E_pml.o update_H_pml.o update_j.o update_e_pml.o make_dir.o \
 output_pal.o

HEADERS = fdtd.h

OPTS = -O3 -Wall -std=gnu++17

all: main

main: $(OBJS)
	g++ -o $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	g++ -c $< $(OPTS)

clean:
	rm -rf main *.o

.PHONY: all clean