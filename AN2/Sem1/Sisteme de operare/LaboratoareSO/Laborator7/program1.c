#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
int is_special_director(char *name)
{
	if(strcmp(".",name) == 0 || strcmp("..",name) == 0)
		return 1;
	return 0;
}

int is_directory(char *name)
{
	struct stat info;
	stat(name, &info);
	return S_ISDIR(info.st_mode);
}

void operation(char *name)
{
	puts(name);
}
void listdir(char *name)
{
	DIR *director;
	struct dirent* entry;
	director = opendir(name);
	chdir(name);
	while((entry = readdir(director)) != NULL)
	{
		if(is_special_director(entry->d_name))
			continue;
		if(is_directory(entry->d_name))
		{
			listdir(entry->d_name);
		}
		operation(entry->d_name);
	}
	chdir("..");
	closedir(director);
}
int main(int argc, char *argv[])
{
	puts(argv[1]);
	listdir(argv[1]);
	return 0;
}