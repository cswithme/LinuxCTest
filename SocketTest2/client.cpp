#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HELLO_WORLD_SERVER_PORT 6666
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
	if(argc != 2) {
		printf("Usage: ./%s ServerIPAddress\n", argv[0]);
		exit(1);
	}

	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);

	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(client_socket < 0) {
		printf("Create Socket Failed!\n");
		exit(1);
	}

	if(bind(client_socket, (struct sockaddr*) &client_addr, sizeof(client_addr))) {
		printf("Client Bind Port Failed!\n");
		exit(1);
	}

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if(inet_aton(argv[1], &server_addr.sin_addr) == 0) {
		printf("Server IP Address Error!\n");
		exit(1);
	}
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
	socklen_t server_addr_length = sizeof(server_addr);
	if(connect(client_socket, (struct sockaddr*) &server_addr, server_addr_length) < 0) {
		printf("Can Not Connect To %s!\n", argv[1]);
		exit(1);
	}

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);
	int length = recv(client_socket, buffer, BUFFER_SIZE, 0);
	if(length < 0) {
		printf("Recieve Data From Server %s Failed!\n", argv[1]);
		exit(1);
	}
	printf("From Server %s :\t%s", argv[1], buffer);

	bzero(buffer, BUFFER_SIZE);
	strcpy(buffer, "Hello, World! From Client\n");

	while(1) {
		// sleep(1);
        usleep(100);
        bzero(buffer, BUFFER_SIZE);
        length = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if(length < 0) {
            printf("Server Recieve Data Failed!\n");
            exit(1);
        }
        printf("\n%s", buffer);
	}

	close(client_socket);
	return 0;
}