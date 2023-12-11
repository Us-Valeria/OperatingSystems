#include <stdio.h>
#include <sys/types.h>
#include <unictd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int args, char* argv[]){
	pid_t pid;
	int t = 0;
	fprintf(stdout, "start at process %i \n\n",(int)getpid());
	for (int i = 1; i < argc; i++){
		pid = fork();
		if(pid == 0) {
			fprintf(stdout, "process %i : \n\n ",(int)getpid());
			execvp(argv[i],argv);
		}
		wait(&t);
		kill(pid, 0);
	}
	fprintf(stdout, "end \n");
	scanf("%d", &t);
	return 0;
}