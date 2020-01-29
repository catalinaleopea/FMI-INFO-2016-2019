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
    struct semid_ds *informatii_despre_vector;    
    unsigned short  *valorile_semafoarelor; 
    struct seminfo  *__buf;                               
};

int main(int argc, char *argv[]) {


    if (argc < 2) {
    	puts("Numar insuficient de argumente");
    	return -1;
    }

    long sem_key;

    //citim cheia externa a semaforului
    sscanf(argv[1], "%li", &sem_key);

    int semid = semget(sem_key, 0/*numarul de semafoare din vector este luat in considerare doar daca aceasta operatie creeaza un IPC nou */, 
                        0);

    //asa aflam valorile fiecarui semafor in parte
    int valoarea_semaforului_de_pe_prima_pozitie_din_vector = semctl(semid, 0/*pozitia din vector*/, GETVAL, 0/*parametrul nu este luat in considerare in cazul asta*/);
    printf("Valoarea primului semafor din vector este: %d\n",  valoarea_semaforului_de_pe_prima_pozitie_din_vector); 

    //in continuare vedem cum putem sa aflam valorile fiecarui semafor din vector

     //structura ce incapsuleaza informatiile despre vectorul de semafoare
    struct semid_ds info_sem;

    union semun semopts;
    semopts.informatii_despre_vector = &info_sem;
  
    //facem un apel ca sa vedem cate semafoare sunt in vector
    semctl(semid, 0, IPC_STAT, semopts);
    int numarul_de_semafoare_din_vector = info_sem.sem_nsems;
    
    //alocam memorie unde o sa fie stocate valorile semafoarelor
    semopts.valorile_semafoarelor = malloc(sizeof(unsigned short) * 100);

    //apelul pentru a afla valorile semafoarelor
    semctl(semid, 0, GETALL, semopts);

    
    for(int i = 0; i < numarul_de_semafoare_din_vector; i++) {
    	printf("Valoarea semaforului de pe pozitia %d este %d\n", i, semopts.valorile_semafoarelor[i]);
    }

    //eliberam memoria alocata
    free(semopts.valorile_semafoarelor);

	return 0;
}