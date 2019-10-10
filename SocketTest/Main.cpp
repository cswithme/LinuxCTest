//============================================================================
// Name        : SocketTest.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ConnectTest.h"

using namespace std;

int main() {
	cout << "23333" << endl; // prints 23333
//	BlockConnectTest("192.169.1.244", 2333);
	UnblockConnectTest("192.169.1.244", 2333);
	return 0;
}
