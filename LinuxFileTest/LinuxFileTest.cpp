//============================================================================
// Name        : LinuxFileTest.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "extern.h"
using namespace std;

int main() {
	cout << "main entry" << endl; // prints
	printf ("The process ID is %d ", (int) getpid ()) ; //本进程
	DupTest();

	cout << "main exit" << endl; // prints
	return 0;
}
