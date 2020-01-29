#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
 #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>

#define SCANDAL -1

struct msgbuf {
	long x;
	char mesaj[69];
};

//Program care citeste un mesaj dintr o coada de mesaje a carui cheie este data ca argument in linia de comanda
//Programul o sa fie compilat cu optiunea -fno-stack-protector


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		puts("muie");
		exit(SCANDAL);
	}

	long keya;
	sscanf(argv[1], "%li", &keya);
	
	int curve = msgget(keya,0);
	struct msgbuf snitzel;

	//snitzel.x = 1;
	//strcpy(snitzel.mesaj, "muie pe bat");

	msgrcv(curve, &snitzel, sizeof(snitzel),1,0);
	//printf("%lu\n", keya);
	printf("%s\n", snitzel.mesaj);

	return 0;
}