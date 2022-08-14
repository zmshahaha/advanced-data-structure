cc = g++
ccflags = -std=c++17 -g -O0
prog = main
objects = main.o HashTable.o SkipList.o

$(prog): $(objects)
	$(cc) $(ccflags) -o $(prog) $(objects)

main.o : main.cpp
	$(cc) $(ccflags) -c main.cpp -o main.o
HashTable.o: HashTable.cpp
	$(cc) $(ccflags) -c HashTable.cpp -o HashTable.o
SkipList.o: SkipList.cpp
	$(cc) $(ccflags) -c SkipList.cpp -o SkipList.o

.PHONY:grade
grade:
	@make
	@./main g

.PHONY:clean
clean:
	rm -rf *.o $(prog) temp