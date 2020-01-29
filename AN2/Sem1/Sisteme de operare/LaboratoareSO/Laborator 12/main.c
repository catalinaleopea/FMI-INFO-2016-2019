#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
/*
struct messages {
    long type;
    int zi;
    int luna;
    int an;
    char nume[50];
};
*/
struct messages {
    long type;
    char buffer[50];
    int dim;
};

int main(int agrc, char **argv[]) {
    if(argc < 3) {
        puts("Numar insuficient de argumente");
        return -1;
    }
    int msgid = msgget(key, IPC_CREAT | IPC_EPC_EXC | IPC_IRUSR | S_IWUSR);
    if(msgid == -1) {
        puts("Nu a creat ipc-ul private");
        return -1;
    }
    int childPid;
    if(childPid = fork()) {
        int descriptorCitire = open(argv[1], O_RDONLY);
        struct message mesajPentruFiu;
        mesajPentruFiu.type = childPid;
        while((result = read(descriptorCitire, mesajPentruFiu.buffer, 50)) > 0) {
            mesajPentruFiu.dim = result;
            msgsnd(msgid,&mesajPentruFiu,sizeof(struct message), 8);
        }
        close(descriptorCitire);
    } else {
        chdir(argv[2]);
        int descriptorScriere = open(argv[1], O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR);
        struct message mesajDeLaTata;
        msgrcv(msgid, &mesajDeLaTata, sizeof(struct message), getpid(), 0);
        while(mesajDeLaTata.dim != 0){
            write(descriptorScriere, mesajDeLaTata.buffer, mesajDeLaTata.dim);
            msgrcv(msgid, &mesajDeLaTata, sizeof(struct message), getpid(), 0);
        }
        close(descriptorScriere);
    }
//programul creeaza 4 cozi private, deci inaccesibile

    /*
    long key = ftok("");
    int msgid = msgget(key, IPC_CREAT | IPC_EPC_EXC | S_IRUSR | S_IWUSR);

    if(msgid == -1){
        puts("Nu s-a putut identifica coada de mesaje");
        return -1;
    }

    struct message mymessage;

    mymessage.type = 7;
    mymessage.zi = 1;
    mymessage.luna = 3;
    mymessage.an = 1997;
    strcpy(mymessage.nume,"Popescu Ion");
    msgsnd(msgid,&myymessage,sizeof(struct message), 8);*/
    return 0;
}
