#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<sys/stat.h>

void process(char* value) {
    //functia de procesare
    printf("Proccesing %s.....\n", value);
    //Simulam o procesare indelungata
    sleep(30);
}

/* Programul exemplifica conceptul de pooling de procese. Descrierea detaliata a fost predata in cadrul laboratorului.

*/
int main(int argc, char* argv[]){


    int shmid = shmget( IPC_PRIVATE, 50, S_IRUSR | S_IWUSR );

    int semafor_slave = semget( IPC_PRIVATE, 1, S_IRUSR | S_IWUSR );
    int semafor_master = semget( IPC_PRIVATE, 1, S_IRUSR | S_IWUSR );


    semctl(semafor_slave,0,SETVAL,0);
    semctl(semafor_master,0,SETVAL,0);

    for (int i = 0; i <  7; ++i) {
        if (fork() == 0) {

            //Slaves
            char* shared_memory = shmat( shmid, NULL, SHM_RND );

            struct sembuf wait_for_data;
            wait_for_data.sem_num = 0;
            wait_for_data.sem_op = -1;
            wait_for_data.sem_flg = 0;
   
            struct sembuf notify_master;
            notify_master.sem_num = 0;
            notify_master.sem_op = 1;
            notify_master.sem_flg = 0;
            
            while(1) {
                 char value[50];   

                 semop(semafor_slave,&wait_for_data,1);
                 sscanf(shared_memory, "%s", value);
                 semop(semafor_master,&notify_master,1);
                 process(value);

            }   

        }
    }

    //Master
    struct sembuf notify_slaves;
    notify_slaves.sem_num = 0;
    notify_slaves.sem_op = 1;
    notify_slaves.sem_flg = 0;

    struct sembuf wait_for_slaves;
    wait_for_slaves.sem_num = 0;
    wait_for_slaves.sem_op = -1;
    wait_for_slaves.sem_flg = 0;

    char* shared_memory = shmat( shmid, NULL, SHM_RND );

    while(1) {
        char value[50];
        printf("Please input data:");
        scanf("%s", value);

        sprintf(shared_memory, "%s", value);

        semop(semafor_slave, &notify_slaves, 1);
        semop(semafor_master, &wait_for_slaves, 1);
    }

    return 0;
}