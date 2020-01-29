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

/* Programul numara cate linii se afla in fisierul transmis ca parametru. Pentru a face acest lucru el se foloseste de utilitarele 
   din linia de comanda cat si wc. "cat" afiseaza continutul unui fisier la standard output iar "wc" citeste de la standard input si
   afiseaza cate cuvinte citeste, cu argumentul "-l" el numara cate linii citeste. Echivalentul in linia de comanda este:

   $ cat fisier | wc -l

   Astfel, o sa avem doua tuburi. Un tub prin care comunica procesul lansat dupa imaginea lui "cat" cu procesul lansat dupa imaginea
   lui "wc", si un tub prin care comunica procesul "wc" cu procesul tata. Redirectam iesirea standard a lui cat si intrarea standard
   al lui wc in primul tub, iar iesirea standard a lui wc si intrarea standard al tatalui in cel de al doilea tub

*/

int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		puts("muie vlad si aaa");
		exit(SCANDAL);
	}

	int cat_to_wc[2];
	int wc_to_tata[2];

	pipe(cat_to_wc);

	if(fork() == 0){
		close(1);
		close(cat_to_wc[0]);
		dup(cat_to_wc[1]);
		close(cat_to_wc[1]);
		execlp("cat","cat",argv[1],NULL);
	}

	pipe(wc_to_tata);
	if(fork() == 0){
		close(cat_to_wc[1]);
		close(0);
		dup(cat_to_wc[0]);
		close(wc_to_tata[0]);
		close(1);
		dup(wc_to_tata[1]);
		close(wc_to_tata[1]);
		//close(wc_to_tata[0]);
		execlp("wc","wc","-l",NULL);
	}

	close(cat_to_wc[0]);
	close(cat_to_wc[1]);
	close(wc_to_tata[1]);
	close(0);
	dup(wc_to_tata[0]);

	close(wc_to_tata[0]);
	
	int muie_cu_cacat;
	printf("%d\n", muie_cu_cacat);
	scanf("%d",&muie_cu_cacat);
	printf("%d\n", muie_cu_cacat);
	return 0;
}