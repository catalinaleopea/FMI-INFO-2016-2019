#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		puts("nr insuficient de param");
		return -1;
	}
	DIR* director = opendir(argv[1]);
	if(director == NULL)
	{
		puts("madafaka");
		return -1;
	}
	struct dirent* intrareInDirector;
	intrareInDirector = readdir(director);
	while(intrareInDirector != NULL)
	{
		puts(intrareInDirector->d_name);
		intrareInDirector = readdir(director);
	}
	rewinddir(director);
	intrareInDirector = readdir(director);
	while(intrareInDirector != NULL)
	{
		puts(intrareInDirector->d_name);
		intrareInDirector = readdir(director);
	}
	closedir(director);
}