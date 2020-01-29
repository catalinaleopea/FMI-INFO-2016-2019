#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/sem.h>

void fibonacci (int nr)
{
    int i;
    for (i = 1; i <= nr; i++)
    {
        if (fork() == 0)
        {
            if (i == 1 || i == 2)
            {
                exit (1);
            }
            
            int a, b, c;
            a = 1, b = 1, c;
            
            int j;
            for (j = 3; j <= i; j++)
            {
                c = a + b;
                a = b;
                b = c;
            }

            exit (c);
        }
    }
    
    int status;
    
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status) != 0)
        {
            printf ("%d ", WEXITSTATUS(status));
        }
    }
    
    printf ("%s", "\n");
}

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        puts ("Numar invalid de argumente");
        return -1;
    }
    
    int nr; // numarul primit ca argument
    sscanf (argv[1], "%d", &nr);
    
    fibonacci (nr);
    
    return 0;
}
