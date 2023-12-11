#include <stdio.h>
#include <sys/types.h>
#include <unictd.h>
int main(){
	int x = 0, y = 0;
	double z = 1;
	fprintf(stdout, "SubProcess3\n");
	fprintf(stdout, "Input the number and degree: \n");
	scanf("%d %d", &x, &y);
	for (int i = 0; i < y; i++){
		z*=x;
	}
	fprintf(stdout, "Your number %d in %d degree is %.0f \n\n" ,x,y,z);
	return 0;
}