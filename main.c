#include <stdio.h>
#include <stdlib.h>
#include "table.h"

Table* tab;
Type* types;

void create_headers(int n_cols, char** names) {

	types = malloc( n_cols * sizeof(Type));
	
	types[0] = INT;
	types[1] = STRING;
	types[2] = CHAR;
	tab = new_table(n_cols, names, types);
}

void free_all() {
	
	free_table(tab);
	free(types);
}

int main(  ) {

	int n_cols = 3;
	char* cols[3] = {"col1", "this is the name of the column", "column3"};
	char* column1;
	int i, n_elements; 
	
	create_headers(n_cols, cols);
	print_table(tab);
	
	read_file(tab, "test2.dat");
	printf("\n\n");
	print_table(tab);
	
	column1 = (char*)get_column(tab, 2, &n_elements);
	for( i = 0; i < n_elements; i++ ) {
		printf("%c ", column1[i]);
	}
	printf("\n");
	free(column1);
	free_all();
	
	return 0;
}
