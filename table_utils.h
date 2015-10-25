#ifndef TABLE_UTILS_H
#define TABLE_UTILS_H

#include <stdbool.h>
#include "table.h"
#include "utils.h"

void print_spaces(int n) {
	
	if( n <= 0 ) 
		return;
	while(n--)
		printf(" ");
}

void print_full_line(int* widths, int n_cols) {

	int i, j;
	for( i = 0; i < n_cols; i++ ) {
		printf("%c", CORNER);
		for( j = 0; j < widths[i] + 2; j++ ) {
			printf("%c", HLINE);
		}
	}
	printf("%c\n", CORNER);
}

int type_size(Type type){
		
	if(type == CHAR) return sizeof(char);
	if(type == STRING) return sizeof(char*);
	if(type == INT) return sizeof(int);
	if(type == FLOAT) return sizeof(float);
	if(type == DOUBLE) return sizeof(double);
	fatal_error("type_size(...)", "Unknown type!");
	return -1;
}

char* format_string(Type type){

	if(type == CHAR) return "%c";
	if(type == STRING) return "%s";
	if(type == INT) return "%d";
	if(type == FLOAT) return "%f";
	if(type == DOUBLE) return "%lf";

	error("format_string(...)", "Unknown type!"); 
	return NULL;
}

bool is_numeric(Type type) {
	if(type == INT || type == FLOAT || type == DOUBLE)
		return true;
	return false;
}

int get_int_len (int value){
  
  char n_str[2048];
  memset(n_str, '\0', 2048);
  sprintf(n_str, "%d", value); 
  return strlen(n_str);
}

int get_double_len (double value){
  
  char n_str[2048];
  memset(n_str, '\0', 2048);
  sprintf(n_str, "%f", value); 
  return strlen(n_str);
}

#endif
