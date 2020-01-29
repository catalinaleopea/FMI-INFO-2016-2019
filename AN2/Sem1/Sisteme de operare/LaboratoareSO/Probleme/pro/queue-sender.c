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

//Program care trimite un mesaj intr o coada de mesaje a carui cheie este data ca argument in linia de comanda
int main(int argc, char *argv[]) {


    if (argc < 2) {
    	puts("Numar insuficient de argumente");
    	return -1;
    }

    long key;
    //Pentru a citi cheia de mesaje si a o stoca intr o variabila de tip long folosim functia sscanf
    //deoarece atoi() functioneaza pe reprezentare in baza 10 a numerelor
    sscanf(argv[1], "%li", &key);

	int msgqid = msgget(key, 0);

    struct message mymessage;

    mymessage.tip = 1;
    mymessage.zi = 1;
    mymessage.luna = 2;
    mymessage.an = 2018;

    //apelul sistem de trimitere a unui mesaj in coada
    msgsnd(msgqid, &mymessage, sizeof(mymessage), 0);

	return 0;
}