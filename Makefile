all: board.o main.o BloomFilter.o Trie.o diccTrie.o program.x diccDHashing.o

board.o: board.cc board.hh
	g++ -c board.cc board.hh

main.o: main.cc
	g++ -c main.cc

BloomFilter.o: BloomFilter.cc BloomFilter.hh
	g++ -c BloomFilter.cc BloomFilter.hh

Trie.o: Trie.cc Trie.hh
	g++ -c Trie.cc Trie.hh

diccTrie.o: diccTrie.cc diccTrie.hh
	g++ -c diccTrie.cc diccTrie.hh

diccDHashing.o: diccDHashing.cc diccDHashing.hh
	g++ -c diccDHashing.cc diccDHashing.hh

program.x: board.o main.o BloomFilter.o Trie.o diccTrie.o diccDHashing.o
	g++ -o program.x board.o main.o BloomFilter.o Trie.o diccTrie.o diccDHashing.o

clean:
	rm -f *.o
	rm -f *.x
	rm -f *.gch
	rm -f *.out
	rm -f h{1..6}
