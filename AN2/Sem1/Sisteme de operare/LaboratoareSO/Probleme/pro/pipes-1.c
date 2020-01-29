#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>

/*
  Programul primeste in linia de comanda calea catre doua fisiere, un fisier de input si un fisier de output. Programul
  copiaza din fisierul de input tot continutul in fisierul de output transformand fiecare litera in uppercase. 

  Pentru a face acest lucru procesul tata lanseaza un proces fiu care transforma literele mici in litere mari. Comunicarea dintre 
  tata si fiu se face prin intermediul tuburilor. Se foloseste un tub pentru a transmite informatie dinspre tata catre fiu si un tub
  pentru a transmite informatii dinspre fiu catre tata. Se verifica posibilele cazuri de eroare ce pot aparea.
*/  

int main(int argc, char *argv[]) {

  if (argc < 3){
    puts("Numar insuficiente de argumente");
    return -1;
  }

  //vectorii cu descriptorii catre cele doua tuburi
  int pipe_from_father_to_child[2];
  int pipe_from_child_to_father[2];

  //apelul sistem pipe() prin care cerem kernel-ului sa ne creeze mecanismele
  pipe(pipe_from_father_to_child);
  pipe(pipe_from_child_to_father);

  if (fork()){
    //instructiuni specifice procesului tata

    /*La apelul fork() descriptorii tatalui sunt mosteniti de catre procesul fiu astfel ca acum avem doi descriptori
      pentru scriere in pipe_from_father_to_child (unul in tata si unul in fiu) si doi de citire (unul in tata si unul in fiu),
      la fel s a intamplat si pentru tubul pipe_from_child_to_father. Cum tatal foloseste pipe_from_father_to_child doar sa scrie
      informatia catre fiu si pipe_from_child_to_father doar sa citeasca informatia de la fiu nu are nevoie de descriptorul de citire
      catre primul tub si de cel de scriere pentru al doilea. Le inchidem ca sa nu avem problema de sincronizare.
    */
    close(pipe_from_father_to_child[0]);
    close(pipe_from_child_to_father[1]);

    int descriptor_input_file = open(argv[1], O_RDONLY);

    //verificam daca fisierul de input s a deschis cu succes
    if (descriptor_input_file < 0){
      puts("Nu se poate deschide fisierul de input");

      //inchidem si ceilalti descriptori ai tatalui
      close(pipe_from_father_to_child[1]);
      close(pipe_from_child_to_father[0]);

      //asteptam ca procesul fiu sa isi termine executia nu vrem sa retinem vreo informatie despre procesul fiu astfel ca 
      //transmitem pointerul NULL catre apelul sistem wait()
      wait(NULL);
      return -1;
    }

    int descriptor_ouput_file = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    char buffer[50];
    int numer_of_bytes_read_from_input_file;

    //citim cat timp avem informatie in fisier
    while ((numer_of_bytes_read_from_input_file = read(descriptor_input_file, buffer, 50)) > 0) {
      //transmitem fiecare bucata de informatie cititat din fisier catre fiu prin tubul aferent
      //apelul va fi blocant doar daca tubul devine plin si inca exista un descriptor de citire catre acest pipe (vezi laborator 6)
      write(pipe_from_father_to_child[1], buffer, numer_of_bytes_read_from_input_file);

      //citim informatia procesata venita de la fiu prin cel de al doilea tub
      //apelul va fi blocant daca nu exista informatie disponibila in fisier
      read(pipe_from_child_to_father[0], buffer, numer_of_bytes_read_from_input_file);

      //scriem in fisierul de output informatia
      write(descriptor_ouput_file, buffer, numer_of_bytes_read_from_input_file);
    }

    //inchidem toti descriptorii folositi de procesul tata (cele doua catre fisiere si cele doua catre tuburi)
    close(pipe_from_father_to_child[1]);
    close(pipe_from_child_to_father[0]);
    close(descriptor_input_file);
    close(descriptor_ouput_file);

    //asteptam ca procesul fiu sa isi termine executia
    wait(NULL);

  } else {
    //instructiuni specifice procesului fiu

    /* Aceasi explicatie ca mai sus, fiul nu are nevoie sa scrie in pipe_from_father_to_child si nu are nevoie sa citeasca din cel
       de al doilea tub. Astfel, inchidem cei doi descriptori inainte sa facem alte operatii.
    */
    close(pipe_from_father_to_child[1]);
    close(pipe_from_child_to_father[0]);

    char buffer[50];
    int numer_of_bytes_read_from_pipe;

    //Citirea din tub este blocanta daca nu exista informatii disponibile. Procesul fiu va intra in asteptare pana cand o sa fie 
    //octeti disponibili. In momentul in care tatal inchide descriptorul de scriere in pipe_from_father_to_child, nu o sa mai existe
    //scriitori pentru acest tub deoarece si fiul l a inchis pe al lui anterior, astfel ca apelul read() va intoarce end-of-file si se 
    //va iesi din bucla while(). Daca nu am inchide in procesul tata descriptorul de scriere se va creea o situatie de deadlock
    //deoarece tatal o sa fie blocat la wait() pe un fiu care este si el blocat la randul lui de un apel la read()
    while((numer_of_bytes_read_from_pipe = read(pipe_from_father_to_child[0], buffer, 50)) > 0) {

      //logica efectiva de transformare a literelor
      for (int i = 0; i < numer_of_bytes_read_from_pipe; ++i) {
         if (isalpha(buffer[i]) && islower(buffer[i])){
           buffer[i] = toupper(buffer[i]);
         }
      }

      //scriem informatia procesata in tubul catre tata. regulile de scriere intr un tub le am discutat mai sus
      write(pipe_from_child_to_father[1], buffer, numer_of_bytes_read_from_pipe);
    }

    //inchidem ceilalti descripotri folositi de procesul fiu
    close(pipe_from_father_to_child[0]);
    close(pipe_from_child_to_father[1]);
    
  }

  //aici o sa ajunga si procesul tata si procesul fiu
  return 0;
}