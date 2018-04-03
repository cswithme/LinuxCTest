XX = g++
CXXFLAGS := -g -Wall

all: pipe_write pipe_read
	@echo "makefile all"

# build pipe_write.cpp
pipe_write: pipe_write.o
	${CXX} ${CXXFLAGS} -o $@ $^; 
	@echo "bulid pipe_write"
	
pipe_write.o: pipe_write.cpp
	${CXX} -c ${CXXFLAGS} -o $@ $^;
	@echo "bulid pipe_write.o"
	
	
# build pipe_read.cpp
pipe_read: pipe_read.o
	@echo "bulid pipe_read"
	${CXX} ${CXXFLAGS} -o $@ $^

pipe_read.o: pipe_read.cpp
	@echo "bulid pipe_read.o"
	${CXX} -c ${CXXFLAGS} -o $@ $^
	

clean:
	rm -f *.o core.* pipe_read pipe_write;