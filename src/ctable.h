#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

#define CORNER '+'
#define VLINE  '|'
#define HLINE  '-'

typedef enum {
	CHAR,
	STRING,
	INT,
	FLOAT,
	DOUBLE
} Type;

typedef struct table Table;
typedef struct column Column;
typedef struct line Line;

Table* new_table(int n_cols, char** column_names, Type* types);
Type get_column_type(Table* tab, int col);
void* get_column(Table* tab, int col, int* n_elements);
void swap_columns(Table* tab, int col1, int col2);
void read_file(Table* tab, char* file_name);
void append_column(Table* tab, char* col_name, void* content, Type type);
void insert_column(Table* tab, char* col_name, void* content, Type type, int col_position);
void insert_calc_column(Table* tab, const char* expr, char* col_name);
bool tables_equal(Table* tab1, Table* tab2);
double sum_column(Table* tab, int col);
void print_table(Table* tab);
void write_to_file( Table* tab, FILE* fp );
void delete_column(Table* tab, int col);
void free_table(Table* tab);

int num_rows(Table* tab);
int num_cols(Table* tab);

#endif
