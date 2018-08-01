CXX = g++
CXXFLAGS := -g
OBJS = main.o

all:libtest.so main mainWithDynamicLoad


# build lib
libtest.so: libTestFunc_a.o libTestFunc_b.o
	${CXX} ${CXXFLAGS} -std=gnu++0x -fPIC -shared -o $@ $^

libTestFunc_a.o: libTestFunc_a.cpp
	${CXX} -c -std=gnu++0x ${CXXFLAGS} -o $@ $^
	
libTestFunc_b.o: libTestFunc_b.cpp
	${CXX} -c -std=gnu++0x ${CXXFLAGS} -o $@ $^
	
# main FUNC
main: ${OBJS} libtest.so
	${CXX} ${CXXFLAGS} -ltest -ldl -L. -o $@ ${OBJS}

main.o: main.cpp
	${CXX} -c ${CXXFLAGS} -o $@ $^
	
#mainWithDynamicLoad
mainWithDynamicLoad: mainWithDynamicLoad.o
	${CXX} ${CXXFLAGS} -ldl -o $@ $^
	
mainWithDynamicLoad.o: mainWithDynamicLoad.cpp
	${CXX} -c ${CXXFLAGS} -o $@ $^
	
clean:
	rm -f *.o core.*;echo "Test"

	
	
