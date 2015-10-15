#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "table.h"

struct column {

	char* name;
	int width;
	char** content;
	Type type;
};

struct table {

	int n_cols;
	int n_rows;
	Column* columns;
};

Table* new_table(int n_cols, char** column_names, Type* types) {
	
	int i;
	Table* tab = malloc(sizeof(Table));
	tab->n_cols = n_cols;
	tab->n_rows = 0;
	tab->columns = malloc(n_cols * sizeof(Column));
	
	for( i = 0; i < n_cols; i++ ) {
		
		tab->columns[i].name = malloc(strlen(column_names[i]) + 1);
		strcpy(tab->columns[i].name, column_names[i]);
		
		tab->columns[i].width = strlen(column_names[i]);
		tab->columns[i].content = NULL;
		tab->columns[i].type = types[i];
	}
	
	return tab;
}

char* table_format_string(Table* tab) {
	
	
	int i;
	int len = 2*tab->n_cols;
	int size = len + strlen("\n");
	char* fstring = malloc(size + 1);
	memset(fstring, '\0', size);

	for( i = 0; i < tab->n_cols; i++ ) {
		strcat(fstring, "%s");
	}
	strcat(fstring, "%s\n");

	return fstring;
}

int count_lines(FILE* file) {

	int n_lines = 0;
	char buff[1024];
	while( fgets(buff, 1024, file) ) {
		if(!(strlen(buff) == 1 && *buff == '\n'))
			n_lines++;
	}
	rewind(file);
	
	return n_lines;
}

int width(char* content) {
	return strlen(content);
}

void insert(Table* tab, char* content, int col, int row) {
	
	Column column = tab->columns[col];
	char* ptr = malloc(strlen(content) + 1);
	strcpy(ptr, content);
	
	column.content[row] = ptr;
	column.width = max(tab->columns[col].width, width(content));
}

void read_file(Table* tab, char* file_name) {
	
	int i, col;
	int n_lines;
	int n_rows = tab->n_rows, n_cols = tab->n_cols;
	char buff[2048];
	FILE* table_file;
	
	memset(buff, '\0', 2028); 
	table_file = fopen(file_name, "r");

	n_lines = count_lines(table_file);
	tab->n_rows += n_lines;
	
	/* Realloc columns */
	for( col = 0; col < n_cols; col++ ) {
		tab->columns[col].content = realloc(tab->columns[col].content, 
									tab->n_rows * sizeof(char*)); 
	}
	
	for( i = 0; i < n_lines; i++ ) {
		n_rows++;
		for( col = 0; col < n_cols; col++ ) {
		
			fscanf(table_file, "%s", buff);		
			insert(tab, buff, col, n_rows - 1);			
		}
	}
	fclose(table_file);
}

int* get_cols_width(Table* tab) {
	
	int i;
	int* cols_width = malloc(tab->n_cols * sizeof(int));
	for( i = 0; i < tab->n_cols; i++ ) {
		cols_width[i] = tab->columns[i].width;
	}
	return cols_width;
}

int print_content( char* content ) {

	if( content == NULL ) 
		fatal_error("print_content(...)", "NULL content");

	fprintf(stdout, "%s", content);
	return width(content);
}

void print_table(Table* tab) {
	
	int i, j;
	int printed_len;
	int n_rows = tab->n_rows;
	int n_cols = tab->n_cols;
	int* cols_width = get_cols_width(tab);
	
	print_full_line(cols_width, n_cols);
	fprintf(stdout, "%c ", VLINE);
	for( i = 0; i < tab->n_cols; i++ ) {
		fprintf(stdout, "%s%n", tab->columns[i].name, &printed_len);
		print_spaces(cols_width[i] - printed_len + 1);
		printf("%c ", VLINE);
	}
	fprintf(stdout, "\n");
	print_full_line(cols_width, n_cols);
	
	for( j = 0; j < n_rows; j++ ) {
		printf("%c ", VLINE);
		for( i = 0; i < n_cols; i++ ) {
		
			char* content = tab->columns[i].content[j];
			printed_len = print_content( content );
			print_spaces(cols_width[i] - printed_len + 1);
			printf("%c ", VLINE);
		}
		fprintf(stdout, "\n");
	}
	print_full_line(cols_width, n_cols);
	free(cols_width);
}

void free_table(Table* tab) {
	
	int col, row;
	for( col = 0; col < tab->n_cols; col++ ) {
		free(tab->columns[col].name);
		for( row = 0; row < tab->n_rows; row++ ) {
			free(tab->columns[col].content[row]);
		}
		free(tab->columns[col].content);
	}
	free(tab->columns);
	free(tab);
}

void* get_column(Table* tab, int col, int* n_elements){
	
	int i, n_rows = tab->n_rows;
	Column column = tab->columns[col];
	Type type = column.type;
	*n_elements = n_rows;
	
	if( type == STRING ){
		error("get_column(...)", "This part is not implemented yet!");
		return NULL;
	}
	else {
		
		if( type == CHAR ){
		
			char* ptr = malloc( n_rows * type_size(type));
			for( i = 0; i < n_rows; i++ ){
				ptr[i] = *(column.content[i]);
			}
			return (void*)ptr;
		}
		else if( type == INT ) {
			
			int* ptr = malloc( n_rows * type_size(type));
			for( i = 0; i < n_rows; i++ ){
				ptr[i] = atoi(column.content[i]);
			}
			return (void*)ptr;
		}
		else if( type == FLOAT ) {
			float* ptr = malloc( n_rows * type_size(type));
			for( i = 0; i < n_rows; i++ ){
				ptr[i] = (float)atof(column.content[i]);
			}
			return (void*)ptr;
		}
		else if( type == DOUBLE ) {
			
			double* ptr = malloc( n_rows * type_size(type));
			for( i = 0; i < n_rows; i++ ){
				ptr[i] = atof(column.content[i]);
			}
			return (void*)ptr;
		}	
		else {
			fatal_error("get_column(...)", "Unknown type!");
			return NULL;
		}
	}
}

void apply_to_columns(Table* tab, void (*func)(Column)) {

	int col;
	int n_cols = tab->n_cols;
	for( col = 0; col < n_cols; col++ ) {
		func(tab->columns[col]);
	}
}
