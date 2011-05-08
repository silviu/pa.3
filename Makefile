SOURCE = holes.c
PROG = holes

build: clean
	gcc -Wall -g $(SOURCE) -o $(PROG)

run: build
	time ./$(PROG) < map.in

clean:
	rm -rf *.o *~ $(PROG)
