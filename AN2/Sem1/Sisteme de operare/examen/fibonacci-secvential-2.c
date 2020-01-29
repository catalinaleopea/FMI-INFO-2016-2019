#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

void fibonacci (int n)
{
    int firstVal = 1, secondVal = 1, aux;


    for (int i = 0; i < 2 && n > 0; ++i, n--) {
    	printf("%d ", 1);
    }

    // IMPORTANT: trebuie fflush
    fflush(stdout);

    while (n != 0) 
    {
        if (fork() == 0) 
        {
        	aux = firstVal + secondVal;
        	firstVal = secondVal;
       		secondVal = aux;
       		
            n--;
            
            printf("%d ", aux);
            
            fflush(stdout);
        } 
        else 
        {
        	 wait(NULL);
        	 break;
        }    
    }
}

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        puts ("Numar invalid de argumente");
        return -1;
    }
    
    int n; // numarul de ordine din sirul Fibo
    sscanf (argv[1], "%d", &n);
   
    fibonacci (n);

    return 0;
}

