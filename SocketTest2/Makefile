CXX = g++
CXXFLAGS := -g

all:client server


# client
client: client.cpp
	${CXX} ${CXXFLAGS} -o $@ $^
	
server: server.cpp
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm -f *.o core.* client server;

	
	
