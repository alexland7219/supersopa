all: board.o main.o BloomFilter.o Trie.o diccTrie.o program.exe

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

program.exe: board.o main.o BloomFilter.o Trie.o diccTrie.o
	g++ -o program.exe board.o main.o BloomFilter.o Trie.o diccTrie.o

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.gch