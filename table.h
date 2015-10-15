#ifndef TABLE_H
#define TABLE_H

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

void* get_column(Table* tab, int col, int* n_elements);
void read_file(Table* tab, char* file_name);
void apply_to_columns(Table* tab, void (*func)(Column));
void print_table(Table* tab);
void free_table(Table* tab);

#endif
