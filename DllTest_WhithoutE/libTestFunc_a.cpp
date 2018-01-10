#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "libTestFunc.h"

void printTestFunc_a()
{
    printf("[%s][%s][%u] in libTest.so!\n", __FILE__ , __FUNCTION__, __LINE__);
}


void genCoreFunc()
{
    int i=0;
    // scanf("%d", &i);
    printf("input a number: ");
    scanf("%d", i); //should use &i
    
    printf("Get input %d \n", i);
}

void cpp11Func()
{
    using namespace std;
    enum class Color { red, green = 20, blue };
	Color r = Color::blue;
	switch(r)
	{
	    case Color::red  : std::cout << "red\n";   break;
	    case Color::green: std::cout << "green\n"; break;
	    case Color::blue : std::cout << "blue\n";  break;
	}
	// int n = r; // error: no scoped enum to int conversion
	int n = static_cast<int>(r); // OK, n = 21
	printf("int n = %d\n", n);
}

