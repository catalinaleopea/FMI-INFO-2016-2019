#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <signal.h>

int flag = 1;

void handler(int signal){
	printf("Am primit semnalul: %d\n", signal);
	flag = 0;
}

int main(int argc, char const * argv[]){
	signal(SIGINT, handler);
	
	puts("Am intrat in while");
	while(flag){
	
	}
	puts("Am iesit din while");
	return 0;
}
