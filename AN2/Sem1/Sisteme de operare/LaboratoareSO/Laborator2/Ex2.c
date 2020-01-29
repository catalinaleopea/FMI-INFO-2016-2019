#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
int getint(int descriptor)
{
	char caracter;
	int result;
	while((result = read(descriptor,&caracter,1)) > 0)
	{
		if(strchr(" \t \n",caracter) != NULL)
			if(result == 0)
				return 0;
	}
	while(result)	
}
int main(int argc, char *argv[])
{
	return 0;
}