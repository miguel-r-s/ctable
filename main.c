#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "table.h"

Table* tab;
Type* types;

void create_headers(int n_cols, char** names) {

	types = malloc(n_cols * sizeof(Type));	
	types[0] = INT;
	types[1] = STRING;
	types[2] = CHAR;
	tab = new_table(n_cols, names, types);
}

void free_all() {
	
	free_table(tab);
	free(types);
}

int main( int argc, char** argv ) {

	int n_cols = 3;
	char* cols[3] = {"col1", "col2", "col3"};
	int* integer_column;
	int i, n_elements; 
	
	create_headers(n_cols, cols);
	print_table(tab);
	
	assert(argc > 1);
	read_file(tab, argv[1]);
	printf("\n\n");
	print_table(tab);
	
	integer_column = (int*)get_column(tab, 0, &n_elements);
	for( i = 0; i < n_elements; i++ ) {
		printf("%d ", integer_column[i]);
	}
	printf("\n");
	
	append_column(tab, "c", integer_column, INT);
	insert_column(tab, "mycol", integer_column, INT, 0);
	
	free(integer_column);
	print_table(tab);
	free_all();
	
	return 0;
}

