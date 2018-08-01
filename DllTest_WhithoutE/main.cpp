#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libTestFunc.h"

#include <dlfcn.h> //dladdr 可以根据函数指针获取函数所在动态库的信息，做个测试

// int dladdr(void *addr, Dl_info *info);


int main()
{
    puts("Test Begin!");
    
    // aaa;
    
    printTestFunc_a();
    printTestFunc_b();
    
    Dl_info stdlInfo;
    memset(&stdlInfo, 0, sizeof(Dl_info));
    
    if(0 == dladdr((void *)printTestFunc_a, &stdlInfo))
    {
        puts("dladdr 获取printTestFunc_a 所在动态库信息失败");
    }
    else
    {
        puts("func printTestFunc_a lib info:");
        printf("dli_fname[%s], dli_fbase{%p}\n", stdlInfo.dli_fname, stdlInfo.dli_fbase);
        printf("dli_sname[%s], dli_saddr{%p}\n", stdlInfo.dli_sname, stdlInfo.dli_saddr);
    }
    
    if(0 == dladdr((void *)printTestFunc_b, &stdlInfo))
    {
        puts("dladdr printTestFunc_b 所在动态库信息失败");
    }
    else
    {
        puts("func printTestFunc_b lib info:");
        printf("dli_fname[%s], dli_fbase{%p}\n", stdlInfo.dli_fname, stdlInfo.dli_fbase);
        printf("dli_sname[%s], dli_saddr{%p}\n", stdlInfo.dli_sname, stdlInfo.dli_saddr);
    }
    
    if(0 == dladdr((void *)puts, &stdlInfo))
    {
        puts("dladdr puts 所在动态库信息失败");
    }
    else
    {
        puts("func puts lib info:");
        printf("dli_fname[%s], dli_fbase{%p}\n", stdlInfo.dli_fname, stdlInfo.dli_fbase);
        printf("dli_sname[%s], dli_saddr{%p}\n", stdlInfo.dli_sname, stdlInfo.dli_saddr);
    }
    
   
    puts("cpp11Func Test Begin!!!!");
    cpp11Func();
    puts("cpp11Func Test end!!!!");
    
    genCoreFunc();
    
    puts("Test End!");
}
