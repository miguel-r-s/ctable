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

void tests_columns( int argc, char** argv ) {

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
}

void test_calc_column() {

	Type types[4] = {INT, FLOAT, DOUBLE, STRING};
	char* col_names[] = {
		"integer",
		"floating point",
		"double precision",
		"ascii string"
	};
	
	Table* tab = new_table(4, col_names, types );
	read_file(tab, "test_files/test_ifds.dat");
	print_table(tab);
	
	insert_calc_column(tab, "c0", NULL);
	insert_calc_column(tab, "c1", NULL);
	insert_calc_column(tab, "c2", NULL);
	insert_calc_column(tab, "c3", NULL);
	insert_calc_column(tab, "c0+c1+c2+c3", NULL);
	print_table(tab);
	free_table(tab);
}

int main( int argc, char** argv ) {
	
	/*tests_columns(argc, argv);*/
	test_calc_column();
	return 0;
}

