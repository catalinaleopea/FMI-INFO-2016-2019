#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>

union semun {
    int              val;    
    struct semid_ds *buf;    
    unsigned short  *array; 
    struct seminfo  *__buf;                               
};

//Programul exemplifica folosirea apelurilor sistem ce citesc informatii despre diferitele tipuri de IPC uri
int main(int argc, char *argv[]) {


    if (argc < 4) {
    	puts("Numar insuficient de argumente");
    	return -1;
    }

    long msg_key;
    long shm_key;
    long sem_key;

    //citim cheile externe ale ipc urilor
    sscanf(argv[1], "%li", &msg_key);
    sscanf(argv[2], "%li", &shm_key);
    sscanf(argv[3], "%li", &sem_key);
 
    int msgqid = msgget(msg_key, 0);
    int shmid = shmget(shm_key, 0/*numarul de octeti este luat in considerare doar daca aceasta operatie creeaza un IPC nou*/, 0);
    int semid = semget(sem_key, 0/*numarul de semafoare din vector este luat in considerare doar daca aceasta operatie creeaza un IPC nou */, 
                        0);

    //structurile ce incapsuleaza informatiile despre fiecare tip de IPC in parte
    struct msqid_ds info_msg;
    struct shmid_ds info_shm;
    struct semid_ds info_sem;

    union semun semopts;
    //campul buf este un pointer, deci trebuie sa indice catre o zona de memorie alocata in prealabil
    semopts.buf = &info_sem;

    msgctl(msgqid, IPC_STAT, &info_msg);
    shmctl(shmid, IPC_STAT, &info_shm);

    //apelul semctl are o definitie mai complicata decat celelalte doua, si necesita definirea tipului de date union in programul nostru
    //cum am facut mai sus
    semctl(semid, 0, IPC_STAT, semopts);

    printf("Numarul de mesage din coada este %d si numarul de octeti maxim este %d\n", (int) info_msg.msg_qnum, (int) info_msg.msg_qbytes);
    printf("Dimensiunea in octeti a zonei de memorie este %d iar pid ul procesului creator este %d\n", (int) info_shm.shm_segsz, (int) info_shm.shm_cpid );
    printf("Numarul de semafoare din vectorul de semafoare este %d\n", (int) info_sem.sem_nsems); 

	return 0;
}