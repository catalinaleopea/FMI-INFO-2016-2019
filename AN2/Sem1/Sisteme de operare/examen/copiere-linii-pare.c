#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void copiere (char *fisierInput, char* fisierOutput)
{
    int descriptor1 = open (fisierInput, O_RDONLY);
    
    if (descriptor1 < 0)
    {
        puts ("Nu am gasit fisierul de intrare");
        return;
    }
    
    int descriptor2 = open (fisierOutput, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    
    char ch;
    int par = 0;
    
    while (read (descriptor1, &ch, 1) == 1)
    {
        if (par == 1)
        {
            write (descriptor2, &ch, 1);
        }
        if (ch == '\n')
        {
            par = 1 - par;
        }
    }
    
    close (descriptor1);
    close (descriptor2);
}

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        puts ("Numar invalid de argumente");
        return -1;
    }
    
    copiere (argv[1], argv[2]);
    
    return 0;
}
