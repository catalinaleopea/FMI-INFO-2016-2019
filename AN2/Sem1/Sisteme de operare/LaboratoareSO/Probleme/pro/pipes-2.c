#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>


/* Programul numara cate linii se afla in fisierul transmis ca parametru. Pentru a face acest lucru el se foloseste de utilitarele 
   din linia de comanda cat si wc. "cat" afiseaza continutul unui fisier la standard output iar "wc" citeste de la standard input si
   afiseaza cate cuvinte citeste, cu argumentul "-l" el numara cate linii citeste. Echivalentul in linia de comanda este:

   $ cat fisier | wc -l

   Astfel, o sa avem doua tuburi. Un tub prin care comunica procesul lansat dupa imaginea lui "cat" cu procesul lansat dupa imaginea
   lui "wc", si un tub prin care comunica procesul "wc" cu procesul tata. Redirectam iesirea standard a lui cat si intrarea standard
   al lui wc in primul tub, iar iesirea standard a lui wc si intrarea standard al tatalui in cel de al doilea tub

*/
int main(int argc, char *argv[]) {

  if (argc < 2){
    puts("Numar insuficiente de argumente");
    return -1;
  }

  //cele doua tuburi
  int pipe_from_cat_to_wc[2];
  int pipe_from_wc_to_father[2];
 
  //apelul sistem pentru a creea tubul prin care o sa comunice procesele cat si wc
  pipe(pipe_from_cat_to_wc);

  if (fork() == 0) {
     //inchidem descriptorul de citire din primul tub deoarece "cat" nu are nevoie de el
     close(pipe_from_cat_to_wc[0]);

     //redirectam iesirea standard al acestui proces fiu in tubul nostru
     close(STDOUT_FILENO);
     dup(pipe_from_cat_to_wc[1]);
     close(pipe_from_cat_to_wc[1]);

     //inlocuim imaginea procesului cu imaginea lui "cat" cu fisierul transmis ca parametru
     execlp("cat", "cat", argv[1], NULL);
  }

  //apelul sistem pentru a creea tubul prin care o sa comunice procesul "wc" cu tatal
  pipe(pipe_from_wc_to_father);

  if (fork() == 0) {

     //inchidem descriptorul de scriere in primul tub deoarece "wc" nu are nevoie de el
     close(pipe_from_cat_to_wc[1]);
     
     //redirectam intrarea standar al lui "wc" in primul tub
     close(STDIN_FILENO);
     dup(pipe_from_cat_to_wc[0]);
     close(pipe_from_cat_to_wc[0]);

    //inchidem descriptorul de citire din cel de al doilea tub deoarece nu este nevoie de el
     close(pipe_from_wc_to_father[0]);

     //redirectam iesirea standard in cel de al doilea tub, prin care se face comunicare cu tatal
     close(STDOUT_FILENO);
     dup(pipe_from_wc_to_father[1]);
     close(pipe_from_wc_to_father[1]);

    //inlocuim imaginea acestui proces fiu cu imaginea lui wc
     execlp("wc", "wc", "-l", NULL);

  }

  //inchidem in toti descriptorii catre primul tub din procesul tata deoarece nu sunt folositi de catre el
  close(pipe_from_cat_to_wc[0]);
  close(pipe_from_cat_to_wc[1]);

  //inchidem descriptorul de scriere in cel de al doilea tub
  close(pipe_from_wc_to_father[1]);

  //redirectam intrarea standard a tatalui in tubul prin care comunica cu fiul lansat dupa imaginea lui "wc"
  close(STDIN_FILENO);
  dup(pipe_from_wc_to_father[0]);
  close(pipe_from_wc_to_father[0]);

  //citim rezultatul procesarii 
  int numer_of_lines;
  scanf("%d", &numer_of_lines);

  printf("Numarul de linii din fisierul %s este %d\n",  argv[1], numer_of_lines);
  
  return 0;
}