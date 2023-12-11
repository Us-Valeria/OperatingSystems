#include <stdio.h>
#include <sys/types.h>
#include <unictd.h>
int main(){
	int x = 0;
	fprintf(stdout, "SubProcess2\n");
	fprintf(stdout, "Input the number\n");
	scanf("%d",&x);
	fprintf(stdout, "Number cubed is %d \n\n",x*x*x);
	return 0;
}