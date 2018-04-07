XX = g++
CXXFLAGS := -g -Wall

all: shmread shmwrite
	@echo "makefile all"

# build pipe_write.cpp
shmread: shmread.cpp
	@echo "bulid shmread"
	${CXX} ${CXXFLAGS} -o $@ $^; 
	
# build shmwrite.cpp
shmwrite: shmwrite.cpp
	@echo "bulid shmwrite"
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm -f *.o core.* shmread shmwrite;