CXX=g++
OBJECTS=fsa.o

all:$(OBJECTS)
	$(CXX) -o fsa $(OBJECTS)

fsa.o: fsa.cc
	$(CXX) -g -c fsa.cc

clean:
	rm -f *~ *.gch a.out fsa.o fsa
