/*
 * ServerSocket.cpp
 *
 *  Created on: 2019-10-23
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */


int CreateListenSocket(int port)
{
	puts("Create socket");
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0);

	puts("bind socket");
	struct sockaddr_in serverAddr; memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
//	inet_pton(AF_INET, ip, &server_address.sin_addr);
	serverAddr.sin_port = htons(port);

	int iRet = bind(sockfd, (sockaddr*)&serverAddr, sizeof(sockaddr_in));
	assert(iRet == 0);

	puts("listen socket");
	iRet = listen(sockfd, 5);
	assert(iRet == 0);

	return sockfd;

//	socklen_t clientAddrLen = 0;
//	struct sockaddr_in clientAddr; memset(&clientAddr, 0, sizeof(clientAddr));
//	int clientfd = accept(sockfd, (sockaddr*)&clientAddr, &clientAddrLen);
}


