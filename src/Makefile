CFLAGS = -Wall -Wextra -std=c++17 -lglut -lGLU -lGL

lava: main.o image.o animation.o object.o
	g++ $^ $(CFLAGS) -o $@
	
main.o: main.cpp image.h animation.hpp object.hpp
	g++ -c $< $(CFLAGS)
	
image.o: image.c image.h
	g++ -c $< $(CFLAGS)
	
object.o: object.cpp object.hpp
	g++ -c $< $(CFLAGS)

animation.o: animation.cpp animation.hpp
	g++ -c $< $(CFLAGS)
	
	
.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

