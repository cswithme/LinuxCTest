#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libTestFunc.h"

void printTestFunc_b()
{
    printf("[%s][%s][%u] in libTest.so!\n", __FILE__ , __FUNCTION__, __LINE__);
}



