#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define SCANDAL -1

/* Programul numara liniile dintr un fisier transmis ca parametru si returneaza in codul de retur valoarea numaratoarei.
   Se verifica posibilele cazuri de eroare (numar insuficient de argumente, daca fisierul poate sa fie deschis) si returneaza 0
   in acest caz.

   Se compileaza cu :
   $ gcc count-lines.c -o count-lines
*/

int main(int argc, char *argv[])
{
	if(argc != 2){
		puts("du-te acasa");
		exit(SCANDAL);
	}

	int descriptor_de_citire_plm = open(argv[1],O_RDONLY);

	if(descriptor_de_citire_plm < 0){
		puts("esti prost in plm");
		exit(SCANDAL);
	}

	int numaratoare_in_plm = 1; 
	char penis;

	while(read(descriptor_de_citire_plm, &penis,sizeof(penis))){
		if(penis == '\n'){
			numaratoare_in_plm++;
		}
	}
	printf("%d",numaratoare_in_plm);
	return numaratoare_in_plm;
}