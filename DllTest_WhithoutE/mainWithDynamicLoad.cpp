#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

/*
void printTestFunc_a();
void printTestFunc_b();
void genCoreFunc();
*/
typedef void (*P_PrintFunca) ();
typedef void (*P_PrintFuncb) ();
typedef void (*P_GenCoreFunc) ();

int main()
{
    puts("Test begin!");
    
    void *libHandle;            /* Handle for shared library */
    P_PrintFunca pFuncA = NULL;
    P_PrintFuncb pFuncB = NULL;
    P_GenCoreFunc pGenCoreFunc = NULL;
    char *err;
    
    libHandle = dlopen("./libtest.so", RTLD_NOW);
    if (libHandle == NULL) {
        fprintf(stderr, "Error on dlopen: %s\n", dlerror());
        dlclose(libHandle);
        exit(EXIT_FAILURE);
    }
    puts("dlopen sucess!");
    
    //load void printTestFunc_a();
    pFuncA = (P_PrintFunca)dlsym(libHandle, "printTestFunc_a");
    //如果函数不声明 extern "C" ,则函数名会被name mangling,此处的函数名可用readelf -s找出来
    // pFuncA = (P_PrintFunca)dlsym(libHandle, "_Z15printTestFunc_av"); 
    if(pFuncA == NULL)
        printf("Get printTestFunc_a address error[%s]!\n", dlerror());
    
    //load void printTestFunc_b();
    pFuncB = (P_PrintFuncb)dlsym(libHandle, "printTestFunc_b");
    if(pFuncB == NULL)
        printf("Get printTestFunc_b address error[%s]!\n", dlerror());
    
    pGenCoreFunc = (P_GenCoreFunc)dlsym(libHandle, "genCoreFunc");
    if(pGenCoreFunc == NULL)
        printf("Get genCoreFunc address error[%s]!\n", dlerror());

    
    if(pFuncA != NULL) pFuncA();
    if(pFuncB != NULL) pFuncB();
    if(pGenCoreFunc != NULL) pGenCoreFunc();
    dlclose(libHandle);
    
    puts("Test end!");
    
    return 0;
}