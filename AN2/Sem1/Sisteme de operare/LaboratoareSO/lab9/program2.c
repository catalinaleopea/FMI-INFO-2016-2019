#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <signal.h>

int main(int argc, char const * argv[]){
	if(argc < 2){
		puts("No process pid is provided");
		return -1;
	}

	int pid = atoi(argv[1]);
	printf("Apelil kill a avut valoarea : %d",kill(pid,SIGKILL));
//	char destinatie[100];
//	strcpy(destinatie, sursa);	
	raise(SIGSEGV);
	return 0;
}
