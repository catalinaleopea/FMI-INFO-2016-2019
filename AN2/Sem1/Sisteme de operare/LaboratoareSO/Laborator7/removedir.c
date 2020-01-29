#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

int my_remove(char *name)
{
	struct stat info;
	stat(name, &info);
	if(S_ISDIR(info.st_mode)){
		return rmdir(name);
	}
	else{
		return unlink(name);
	}
}

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
	//my_remove(name);
}
void removedir(char *name)
{
	DIR *director;
	struct dirent* entry;
	static int i = 0;
	director = opendir(name);
	if(director == NULL)
		return;
	chdir(name);
	i++;
	printf("nivelul: %d\n", i);
	while((entry = readdir(director)) != NULL)
	{
		if(is_special_director(entry->d_name))
			continue;
		if(is_directory(entry->d_name))
		{
			removedir(entry->d_name);
		}
		operation(entry->d_name);
	}
	chdir("..");
	i--;
	my_remove(name);
	closedir(director);
}
void func()
{
	static int i = 0;
	i++;
	printf("%d\n", i);
}
int main(int argc, char *argv[])
{
	puts(argv[1]);
	removedir(argv[1]);
	return 0;
}