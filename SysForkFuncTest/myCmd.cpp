#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /*
    puts("Test begin");
    for(int i=0; i<argc; ++i)
    {   
        puts(argv[i]);
    }
    puts("Test end!");
    //abort();
    */
    int iRet = 0x2f;
    if(argc > 1)
        iRet = strtol(argv[1], NULL, 10);
    printf("iRet = %d[%#X]\n", iRet, iRet);
    abort();
    exit(iRet);
}
