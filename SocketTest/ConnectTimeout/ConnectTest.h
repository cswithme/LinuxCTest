/*
 * ConnectTest.h
 *
 *  Created on: 2019-9-29
 *      Author: root
 */

#ifndef CONNECTTEST_H_
#define CONNECTTEST_H_

int BlockConnectTest(const char* ip, int port); //ret socketfd
int UnblockConnectTest(const char* ip, int port);

int unblock_connect(const char* ip, int port, int iConnectTimeoutMs); //ret socketfd

#endif /* CONNECTTEST_H_ */
