#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>

struct message
{
	long tip;
    int zi;
    int luna;
    int an;
};

//Program care citeste un mesaj dintr o coada de mesaje a carui cheie este data ca argument in linia de comanda
//Programul o sa fie compilat cu optiunea -fno-stack-protector
int main(int argc, char *argv[]) {

    if (argc < 2){
        puts("Numar insuficiente de argumente");
        return -1;
    }

    long key;

    //Retineti modul prin care convertim cheia intr o variabila de tip long
    sscanf(argv[1], "%li", &key);

    int msgqid = msgget(key, 0);

    struct message mymessage;

    msgrcv(msgqid, &mymessage, sizeof(struct message), 1, 0);

    printf("Zi: %d Luna: %d An:%d\n", mymessage.zi, mymessage.luna, mymessage.an);

	return 0;
}