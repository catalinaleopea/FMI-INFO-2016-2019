#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct message
{
	long tip;
    char buffer[50];
    int size;
};

/* Programul primeste doua argumente, un nume de fisier din directorul curent de lucru si o cale catre un director. Programul
   copiaza fisierul transmis ca prim argument in directorul transmis ca al doilea argument sub acelasi nume. 

   Pentru a face acest lucru, procesul tata creeaza un proces fiu care face chdir() in directorul destinatie. Procesul tata trimite
   continutul fisierului destinatie la procesul fiu pentru a il scrie in destinatie. Comunicarea intre ei se face prin o coada de mesage.
   Continutul fisierul este transmis in bucati de cate 50 de octeti maxim. IPC ul este de tip privat, deci este accesibil numai procesului creator
   si a descendentilor acestuia. Acesta trebuie sters dupa ce nu mai este folosit

*/
int main(int argc, char *argv[]) {

    if (argc < 3) {
    	puts("Numar insuficient de argumente");
    	return -1;
    }


    //Am creat un IPC privat cu drepturi de citire si scriere pentru propietar
	int msgqid = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR );

    int child_pid;

    if ((child_pid = fork())) {
        //instructiuni executate doar de procesul tata    

        int descriptor = open(argv[1], O_RDONLY);

        //tipul mesajului este pid ul procesului destinatar
        struct message message_for_child;
        message_for_child.tip = child_pid;

        //citim din fisier si trimitem continutul in coada de mesaje
        while((message_for_child.size = read(descriptor, message_for_child.buffer, 50)) > 0) {
             msgsnd(msgqid, &message_for_child, sizeof(message_for_child), 0);
        }
        
        //dupa ce am terminat de parcurs fisierul ii trimitem fiului un mesaj de dimensiune 0 pentru ca acesta sa stie
        //ca a terminat de primit continutul fisierului si nu ar mai trebui sa astepte dupa alte mesaje
        message_for_child.size = 0;
        msgsnd(msgqid, &message_for_child, sizeof(message_for_child), 0);

        close(descriptor);

        //asteptam fiul sa isi termine executia
        wait(NULL);
        
    } else {

        chdir(argv[2]);

        int descriptor = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        struct message message_from_father;
        
        //fiul citeste din coada de mesaje doar mesajele care ii sunt destinate lui (adica cele care au ca "tip" pid ul sau)
        msgrcv(msgqid, &message_from_father, sizeof(message_from_father), getpid()/*aici specificam tipul mesajului asteptat*/, 0);

        //citim bucati din fisier atata timp cat nu au dimensiunea 0
        while (message_from_father.size > 0) { 
            write(descriptor, message_from_father.buffer, message_from_father.size);
            msgrcv(msgqid, &message_from_father, sizeof(message_from_father), getpid(), 0);
        }

        close(descriptor);

        //dupa ce am terminat de folosit coada, o stergem. este datoria fiului sa stearga coada deoarece el este ultimului care
        //actioneaza asupra sa. daca am sterge coada din interiorul procesului tata este posibil ca instructiunile de trimitere
        //al ultimului mesaj si cea de a sterge coada sa se execute inainte ca fiul sa apuce sa citeasca ultimul mesaj. Astfel, 
        //o sa ne aflam intr o stare de inconsistenta
        msgctl(msgqid, IPC_RMID, NULL);

    }
 
	return 0;
}