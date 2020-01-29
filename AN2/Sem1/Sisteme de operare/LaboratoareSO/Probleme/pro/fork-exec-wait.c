#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/* Programul se foloseste de programul count-lines pe care il gasiti in arhiva pentru a numara toate liniile din toate fisierele
   transmise ca parametru. Ca sa realizeze acest lucru se foloseste de o strategie de tip "fork-join" in care lanseaza un proces
   pentru fiecare fisier in parte. Dupa aceasta asteapta toti fii sa isi termine executia pentru ca la final sa faca agregarea 
   rezultatelor.
*/
int main(int argc, char *argv[]) {

  //verific daca am argumente
  if (argc < 2){
    puts("No arguments");
    return -1;
  }

  //lansez toate procesele fiu
  for (int i = 1; i < argc; i++) {
      if (fork() == 0){
        //instructiuni executate de procesul fiu
        //Retineti diferenta dintre execl, execlp, execv, execvp
        execl("./count-lines", "count-lines", argv[i], NULL);
      }
  }

  int aggregate = 0;
  int status;

  //asteptam toate procesele fiu
  while(wait(&status) != -1) {
    if (WIFEXITED(status)){
      aggregate += WEXITSTATUS(status);
    }
  }

  printf("Numarul de total de linii din fisiere este:%d\n", aggregate);

  return 0;
}