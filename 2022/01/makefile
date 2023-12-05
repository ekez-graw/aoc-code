CC = g++
CXXFLAGS = -g -Wall -Wextra -Weffc++ -Wstrict-aliasing -ansi -pedantic
CSRC = $(wildcard *.cpp)
OBJECTS = $(CSRC:.cpp=.o)

%.o : %.cpp
	$(CC) -c $(CXXFLAGS) -o $@ $<

p1: $(OBJECTS)
	$(CC) $(CXXFLAGS) -o p1 $(OBJECTS) $(LDFLAGS) 

clean:
	rm p1 *.o 
