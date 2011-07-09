SOURCE = holes.cpp
PROG = holes

build:
	g++ $(SOURCE) -o $(PROG)

run:
	./$(PROG)

clean:
	rm -rf *.o *~ $(PROG)
