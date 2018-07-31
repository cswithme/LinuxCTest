#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int Pipe1Test();
int Pipe2Test(int argc, char *argv[]);
int SemTest();
void popenTest();

int main(int argc, char *argv[])
{
	printf("Test Begin!\n");
//	Pipe1Test();
//	Pipe2Test(0, NULL);
//	SemTest();

	popenTest();

	printf("Test End!\n");
	return 0;
}
