/*
 * BlockConnect.cpp
 *
 *  Created on: 2019-9-29
 *      Author: root
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

#include "ConnectTest.h"

#define BUFFER_SIZE 512

//int BlockConnectTest(int argc, char* argv[])

int BlockConnectTest(const char* ip, int port)
{
//	if(argc <= 3) {
//		printf("usage: %s ip_address port_number send_bufer_size\n", basename(argv[0]));
//		return 1;
//	}

	struct sockaddr_in server_address; bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_address.sin_addr);
	server_address.sin_port = htons(port);

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

//	int sendbuf = atoi(argv[3]);
//	int len = sizeof(sendbuf);
//	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
//	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t*) &len);
//	printf("the tcp send buffer size after setting is %d\n", sendbuf);

	int old_option = fcntl(sock, F_GETFL);
	printf("noblock: %d\n", old_option & O_NONBLOCK); //0-->block mode

	//int oldopt = setnonblocking(sock); set nonblock mode!

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	int ret = connect(sock, (struct sockaddr*) &server_address, sizeof(server_address));
	printf("connect ret code is: %d\n", ret);
	if(ret == 0) {
		//
		printf("call getsockname ...\n");
		struct sockaddr_in local_address;
		socklen_t length;
		int ret = getpeername(sock, (struct sockaddr*) &local_address, &length);
		assert(ret == 0);
		char local[INET_ADDRSTRLEN];
		printf("local with ip: %s and port: %d\n", inet_ntop(AF_INET, &local_address.sin_addr, local, INET_ADDRSTRLEN), ntohs(
		        local_address.sin_port));
		//

		char buffer[BUFFER_SIZE];
		memset(buffer, 'a', BUFFER_SIZE);
		send(sock, buffer, BUFFER_SIZE, 0);
	}
	else if(ret == -1) {
		gettimeofday(&tv2, NULL);
		suseconds_t msec = tv2.tv_usec - tv1.tv_usec;
		time_t sec = tv2.tv_sec - tv1.tv_sec;
		printf("Connect time used:%fs\n", (double) msec / 1000000+sec);

		printf("connect failed...\n");
		if(errno == EINPROGRESS) {
			printf("unblock mode ret code...\n");
		}
	}
	else {
		printf("ret code is: %d\n", ret);
	}

	printf("after connected!\n");

	close(sock);
	return 0;
}
