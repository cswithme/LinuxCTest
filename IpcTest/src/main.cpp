#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int Pipe1Test();
int Pipe2Test(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	printf("Test Begin!\n");
//	Pipe1Test();
	Pipe2Test(0, NULL);
	printf("Test End!\n");
	return 0;
}
