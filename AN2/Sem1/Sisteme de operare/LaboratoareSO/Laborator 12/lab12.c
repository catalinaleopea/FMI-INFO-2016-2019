#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>

struct message {
	long type;
	int zi;
	int luna;
	int an;
	char nume[100];
};

int main(int argc, char *argv[])
{
	/*int msgqid=msgget(0x7e7fc756,0);
	if(msgqid==1)
	{
		puts("Nu s-a putut identifica coada de mesaje");
		return -1;
	}
	struct message mymessage;
	mymessage.type=7;
	mymessage.zi=1;
	mymessage.luna=2;
	mymessage.an=1969;
	strcpy(mymessage.nume, "Vasile Pielosu");
	msgsnd(msgqid, &mymessage, sizeof(struct message), 0);*/
    if(argc<2)
    {
		puts("Numar insuficient de argumente");
        return -1;
    }
    long key;
    sscanf(argv[1],"%li",&key);
    int msgqid=msgget(key,0);
    if(msgqid==-1){
        puts("Nu s-a putut identifica coada de mesaje");
        return -1;
     }
    struct message mymessage;
    mymessage.type=7;
    mymessage.zi=1;
    mymessage.luna=3;
    mymessage.an=1997;
    strcpy(mymessage.nume,"Popescu Ion");
    msgsnd(msgqid,&mymessage,sizeof(struct message),0);
	return 0;
}



