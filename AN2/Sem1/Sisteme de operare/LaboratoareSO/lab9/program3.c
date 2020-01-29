#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <signal.h>

int main(int argc, char const * argv[]){
	sigset_t multime_de_semnale;
//	sigemptyset(&multime_de_semnale); // il transf in multimea vida
//	sigsilset(&multime_de_semnale); //il face sa contina toate semnalele posibile

	// ne asiguram ca multimea este vida
	printf("Rezultatul este: %d\n", sigemptyset(&multime_de_semnale));

	//populam multimea de semnale
	sigaddset(&multime_de_semnale, SIGINT);
	sigaddset(&multime_de_semnale, SIGQUIT);
	
	//blocam aceste semnale--nu mai putem inchide prog cu ^C, ^/
	//nu putem bloca SIGKILL,SIGTELL,SIGCOUNT?
	printf("Apelul la sigprogmask: %d\n", sigprogmask(SIG_SETMASK, &multime_de_semnale, NULL));
	while(1){
		//ciclarea infinita blocheaza prog
	}
	return 0;
}

