CXX = g++
CXXFLAGS := -g
OBJS = main.o

all:exe1 main


# build child process
exe1: exec1.cpp
	${CXX} ${CXXFLAGS} -o $@ $^
	
# build parent process
main: main.cpp
	${CXX} ${CXXFLAGS} -o $@ $^
	
run:
	./main
	
clean:
	rm -f *.o core.* main test exe1

	
	
