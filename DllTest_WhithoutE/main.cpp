#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libTestFunc.h"

int main()
{
    puts("Test Begin!");
    
    // aaa;
    
    printTestFunc_a();
    printTestFunc_b();
    
    puts("cpp11Func Test Begin!!!!");
    cpp11Func();
    puts("cpp11Func Test end!!!!");
    
    genCoreFunc();
    
    puts("Test End!");
}
