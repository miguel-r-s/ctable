#ifndef UTILS_H
#define UTILS_H

#define min(x,y) ((x) < (y)) ? (x):(y);
#define max(x,y) ((x) > (y)) ? (x):(y);

void error(char* func_name, char* message) {
	
	fprintf(stderr, "[ERROR] %s: %s\n", func_name, message);
}

void fatal_error(char* func_name, char* message) {

	error(func_name, message);
	exit(-1);
}

#endif
