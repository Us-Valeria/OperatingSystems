#include <stdio.h>
#include <sys/types.h>
#include <unictd.h>

int main(){
	int x = 0;
	fprintf(stdout, "SubProcess1\n");
	fprintf(stdout, "Input the number\n");
	scanf("%d",&x);
	fprintf(stdout, "Number squared is %d \n\n",x*x);
	return 0;
}