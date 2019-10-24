/*
 * main.cpp
 *
 *  Created on: 2019-10-23
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include "ServerSocket.h"
#include "libeventTest.h"

int main()
{
	using namespace std;

	cout << "Test Begin" << endl; // prints 23333

//	evTimerTest();
//	CreateListenSocket(23333);

	evServerSocketTest();

	cout << "Test End" << endl; // prints 23333
	return 0;
}
