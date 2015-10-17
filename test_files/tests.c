#include <stdio.h>
#include <stdlib.h>
#include "../table.h"

#define n_elements(a) sizeof((a))/sizeof((a)[0])

Table* tab;
Type types_iisii[5] =  {INT, INT, STRING, INT, INT};
char* col_names[n_elements(types_iisii)] = {
	"c1",
	"c2",
	"coluna com uma string",
	"coluna c12om um numero",
	"outro numero"
};

int main( int argc, char** argv ) {

	int n;
	int i;
	char** str_column;
	tab = new_table(n_elements(types_iisii), col_names, types_iisii);

	print_table(tab);
	read_file(tab, "test_files/test_iisii.table");
	swap_columns(tab, 4, 2);
	print_table(tab);
	
 	str_column = (char**)get_column(tab, 4, &n);
	for( i = 0; i < n; i++ ){
		printf("%s ", str_column[i]);
	}
	printf("\n");
	printf("\n");
	print_table(tab);
	
	free(str_column);
	free_table(tab);
	return 0;
}

