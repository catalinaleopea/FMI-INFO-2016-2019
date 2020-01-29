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

/*
  Programul primeste in linia de comanda calea catre doua fisiere, un fisier de input si un fisier de output. Programul
  copiaza din fisierul de input tot continutul in fisierul de output transformand fiecare litera in uppercase. 

  Pentru a face acest lucru procesul tata lanseaza un proces fiu care transforma literele mici in litere mari. Comunicarea dintre 
  tata si fiu se face prin intermediul tuburilor. Se foloseste un tub pentru a transmite informatie dinspre tata catre fiu si un tub
  pentru a transmite informatii dinspre fiu catre tata. Se verifica posibilele cazuri de eroare ce pot aparea.
*/  

int main(int argc, char *argv[])
{
	if(argc != 3){
		puts("badeci e homosexual");
		exit(SCANDAL);
	}

	int tata_fiu[2];
	int fiu_tata[2];
	pipe(fiu_tata);
	pipe(tata_fiu);
	if(fork() == 0){
		close(tata_fiu[1]);
		close(fiu_tata[0]);
		char car;
		while(read(tata_fiu[0],&car,1)){
			if(car <= 'z' && car >= 'a'){
				car = car - 32;
			}
			write(fiu_tata[1], &car,1);
		}
		close(tata_fiu[0]);
		close(fiu_tata[1]);
	}else{
		close(tata_fiu[0]);
		close(fiu_tata[1]);
		int descriptor_citire = open(argv[1],O_RDONLY);
		int descriptr_scriere = open(argv[2],O_WRONLY);
		char pula;
		while(read(descriptor_citire,&pula,1)){
			write(tata_fiu[1],&pula,1);
			read(fiu_tata[0],&pula,1);
			write(descriptr_scriere,&pula,1);
		}
		close(descriptr_scriere);
		close(descriptor_citire);
		close(tata_fiu[0]);
		close(fiu_tata[1]);
	}
	return 0;
}