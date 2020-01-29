#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define SCANDAL -1
/* Programul se foloseste de programul count-lines pe care il gasiti in arhiva pentru a numara toate liniile din toate fisierele
   transmise ca parametru. Ca sa realizeze acest lucru se foloseste de o strategie de tip "fork-join" in care lanseaza un proces
   pentru fiecare fisier in parte. Dupa aceasta asteapta toti fii sa isi termine executia pentru ca la final sa faca agregarea 
   rezultatelor.
*/

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		puts("du-te acasa");
		exit(SCANDAL);
	}

	int i;
	for(i = 1; i < argc; i++){
		if(fork() == 0){
			execl("count_lines.out","count_lines.out",argv[i],NULL);
		}
	}
	int balamuc = 0;
	int sloboz = 0;
	while(wait(&balamuc) != -1){
		if(WIFEXITED(balamuc)){
			sloboz = sloboz + WEXITSTATUS(balamuc);
			printf("(%d)\n",sloboz );
		}
	}
	return 0;
}