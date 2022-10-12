all: board.o main.o BloomFilter.o program.x diccDHashing.o diccTernary.o Ternary.o diccSortedVector.o

board.o: board.cc board.hh
	g++ -c board.cc board.hh

main.o: main.cc
	g++ -c main.cc

BloomFilter.o: BloomFilter.cc BloomFilter.hh
	g++ -c BloomFilter.cc BloomFilter.hh

diccDHashing.o: diccDHashing.cc diccDHashing.hh
	g++ -c diccDHashing.cc diccDHashing.hh

Ternary.o: Ternary.cc Ternary.hh
	g++ -c Ternary.cc Ternary.hh

diccTernary.o: diccTernary.cc diccTernary.hh
	g++ -c diccTernary.cc diccTernary.hh

diccSortedVector.o: diccSortedVector.cc diccSortedVector.hh
	g++ -c diccSortedVector.cc diccSortedVector.hh

program.x: board.o main.o BloomFilter.o diccDHashing.o diccTernary.o Ternary.o diccSortedVector.o
	g++ -o program.x board.o main.o BloomFilter.o diccDHashing.o diccTernary.o Ternary.o diccSortedVector.o

clean:
	rm -f *.o
	rm -f *.x
	rm -f *.gch
	rm -f *.out
	rm -f h{1..6}
