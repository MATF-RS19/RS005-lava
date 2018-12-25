CFLAGS = -Wall -Wextra -std=c++11 -lglut -lGLU -lGL

lava: main.o image.o
	g++ $^ $(CFLAGS) -o $@
	
main.o: main.cpp image.h
	g++ -c $< $(CFLAGS)
	
image.o: image.c image.h
	g++ -c $< $(CFLAGS)
	
.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

