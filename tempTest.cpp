#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main()
{
    //int iArry[5] = {0};
    //printf("iArry[255] = %d\n", iArry[255]);

    char *szTemp = strdup("hahahaha");
    printf("%s\n",szTemp);
    free(szTemp);
    free(szTemp);
    return 0;
}
