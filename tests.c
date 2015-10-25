#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	double solution, arr[] = {0,1,2,3,4,5,6,7,8,9,10};
	char* s = expression_string("c0*(c5*c2+c3^c4)", arr);
	shunting_yard(s, &solution);
	
	printf("%s, %lf\n", s, solution);
	free(s);
	return 0;
}
