//============================================================================
// Name        : SocketTest.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ConnectTest.h"
#include "SocketRW.h"

using namespace std;

int main() {
	cout << "23333" << endl; // prints 23333
//	BlockConnectTest("192.168.159.66", 23333);

//	UnblockConnectTest("127.0.0.1", 23333);


	int socketfd = BlockConnectTest("127.0.0.1", 23333);
	if(-1 != socketfd){
		SocketRWTest(socketfd);
	}

	return 0;
}
