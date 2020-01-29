#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define SCANDAL -1
/* Programul numara liniile dintr un fisier transmis ca parametru si returneaza in codul de retur valoarea numaratoarei.
   Se verifica posibilele cazuri de eroare (numar insuficient de argumente, daca fisierul poate sa fie deschis) si returneaza 0
   in acest caz.

   Se compileaza cu :
   $ gcc count-lines.c -o count-lines
*/

int main(int argc,char* argv[]){
  if(argc != 2) {
    puts("nr de parametrii incorect");
    exit(SCANDAL); 
  }
  
  int descriptor_de_citire=open(argv[1], O_RDONLY);
  
  if(descriptor <0){
    puts("Nu e bine frate");
    exit(SCANDAL);
  }

  char de_citit;

  int numaratoare=0;
  while(read(descriptor,&de_citit,sizeof(de_citit))){
  //citeste bites si ret 1-nr bites cititi sau 0
    if(de_citit== '\n'){
      numaratoare++;
    }
  }
  return numaratoare;
}
