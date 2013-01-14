CXX=g++
OBJECTS=eightpuzzle.o

all:$(OBJECTS)
	$(CXX) -o puzzle  $(OBJECTS) 

eightpuzzle.o: eightpuzzle.cc priority_queue.H eight_puzzle.H
	$(CXX) -g -c eightpuzzle.cc

clean:
	rm -f *~ *.gch a.out eightpuzzle.o puzzle
