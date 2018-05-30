#include <stdio.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main()
{
    for(int i=0; i<10; ++i)
    {
        int msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666);
        printf("msgid is [%d][%#010X]\n", msgid, msgid);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
    
}