#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		write(STDOUT_FILENO, "Nr insuficient de argumente",strlen("Nr insuficient de argumente"));
		return -1;
	}
	int descriptorcitire = open(argv[1],O_RDWR);
	if(descriptorcitire < 0)
	{
		printf("Nu s-a putut deschide fisierul\n");
		return -1;
	}
	char ch1;
	char ch2;
	ch1 = argv[2][0];
	ch2 = argv[3][0];
	char aux;
	while(read(descriptorcitire,&aux,1) > 0)
	{
		if(aux == ch1)
		{
			lseek(descriptorcitire,-1,SEEK_CUR);
			write(descriptorcitire,&ch2,1);
		}
	}
	close(descriptorcitire);
	return 0;
}