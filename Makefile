MAKEOPTS="-O2"

all: board.o main.o BloomFilter.o program.x diccDHashing.o diccTernary.o Ternary.o diccSortedVector.o

board.o: board.cc board.hh
	g++ $(MAKEOPTS) -c board.cc board.hh

main.o: main.cc
	g++ $(MAKEOPTS) -c main.cc

BloomFilter.o: BloomFilter.cc BloomFilter.hh
	g++ $(MAKEOPTS) -c BloomFilter.cc BloomFilter.hh

diccDHashing.o: diccDHashing.cc diccDHashing.hh
	g++ $(MAKEOPTS) -c diccDHashing.cc diccDHashing.hh

Ternary.o: Ternary.cc Ternary.hh
	g++ $(MAKEOPTS) -c Ternary.cc Ternary.hh

diccTernary.o: diccTernary.cc diccTernary.hh
	g++ $(MAKEOPTS) -c diccTernary.cc diccTernary.hh

diccSortedVector.o: diccSortedVector.cc diccSortedVector.hh
	g++ $(MAKEOPTS) -c diccSortedVector.cc diccSortedVector.hh

program.x: board.o main.o BloomFilter.o diccDHashing.o diccTernary.o Ternary.o diccSortedVector.o
	g++ $(MAKEOPTS) -o program.x board.o main.o BloomFilter.o diccDHashing.o diccTernary.o Ternary.o diccSortedVector.o

clean:
	rm -f *.o
	rm -f *.x
	rm -f *.gch
	rm -f *.out
	rm -f h{1..6}
