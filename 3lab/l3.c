#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {

	pid_t processes[5];

	printf("|%d parent pid|\n", getpid());

	for (int i = 0; i < 5; i++) {
		processes[i] = fork();
		if (processes[i] == 0) {
			printf("%d child pid\n", getpid());
			//exit(5);
			while(1){
			}
		}
		else {
			printf("%d step-parent pid\n", getpid());
			while(1){
			}
		}
	}

	return 0;
}
