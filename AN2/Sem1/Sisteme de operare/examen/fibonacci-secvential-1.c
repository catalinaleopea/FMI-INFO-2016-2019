#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

void seqChildFork (int firstVal, int secondVal, int n)
{
    if (n == 1)
    {
        return;
    }
    
    if (fork() == 0)
    {
        int myVal = firstVal + secondVal;
        printf ("%d ", myVal);
        
        // IMPORTANT
        fflush(stdout);
        seqChildFork (secondVal, myVal, (n - 1));
    }
    else 
    {
        wait (NULL);
    }
}

void fibonacci (int n)
{

    int child_pid;
    
    int i = 0;
    if ((child_pid = fork()) == 0)
    {
        // sunt copilul cu numarul de ordine i
        // lansez copilul i + 1
        int firstVal, secondVal;
        firstVal = secondVal = 1;
        printf ("%d ", firstVal);
        
        if (n >= 2)
        {
            printf ("%d ", secondVal);
            fflush(stdout);
            seqChildFork (firstVal, secondVal, n - 1);
        }
    }
    
    else 
    {
        wait (NULL);
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

