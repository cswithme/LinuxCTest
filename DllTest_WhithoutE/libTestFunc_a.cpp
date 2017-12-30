#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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


