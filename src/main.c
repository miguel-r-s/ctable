#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "table.h"
#include "minunit.h"

int tests_run = 0;
int tests_passed = 0;

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

static char* test_column_read_iii() {
	int i, n_elements;
	Type types[3] = {INT, FLOAT, DOUBLE};
	Table* tab = new_table(3, NULL, types); 
	read_file(tab, "test_files/sum_cols.table");
	
	int i_arr[5] = {0,0,0,0,0};
	float f_arr[5] = {1,1,1,1,1};
	double d_arr[5] = {2,2,2,2,2};
	
	int* i_arr_table = (int*)get_column(tab, 0, &n_elements);
	float* f_arr_table = (float*)get_column(tab, 1, &n_elements);
	double* d_arr_table = (double*)get_column(tab, 2, &n_elements);
	
	mu_assert("Wrong number of elements!\n", n_elements == 5);
	for( i = 0; i < 5; i++ ){
		mu_assert("Wrong int element!", i_arr[i] == i_arr_table[i]);
		mu_assert("Wrong float element!", f_arr[i] == f_arr_table[i]);
		mu_assert("Wrong double element!", d_arr[i] == d_arr_table[i]);
	}
	
	free(i_arr_table);
	free(f_arr_table);
	free(d_arr_table);
	free_table(tab);
	return 0;
}

static char* test_column_read_ifds() {
	int i, n_elements;
	Type types[4] = {INT, FLOAT, DOUBLE, STRING};
	Table* tab = new_table(4, NULL, types); 
	read_file(tab, "test_files/test_ifds.table");
	
	int i_arr[2] = {1,4};
	float f_arr[2] = {1.2,2.3};
	double d_arr[2] = {3.1234, 12.341234};
	char* s_arr[2] = {"test_string", "this_is_a_test"};
	
	int* i_arr_table = (int*)get_column(tab, 0, &n_elements);
	float* f_arr_table = (float*)get_column(tab, 1, &n_elements);
	double* d_arr_table = (double*)get_column(tab, 2, &n_elements);
	char** s_arr_table = (char**)get_column(tab, 3, &n_elements);
	
	mu_assert("Wrong number of elements!\n", n_elements == 2);
	for( i = 0; i < 2; i++ ){
		mu_assert("Wrong int element!", i_arr[i] == i_arr_table[i]);
		mu_assert("Wrong float element!", f_arr[i] == f_arr_table[i]);
		mu_assert("Wrong double element!", d_arr[i] == d_arr_table[i]);
		mu_assert("Wrong string element!", strcmp(s_arr[i], s_arr_table[i]) == 0);
	}
	
	free(i_arr_table);
	free(f_arr_table);
	free(d_arr_table);
	free(s_arr_table);
	free_table(tab);
	return 0;
}

static char* test_sum_columns() {
	
	double result;
	Type types[3] = {INT, INT, INT};
	Table* tab = new_table(3, NULL, types); 
	read_file(tab, "test_files/sum_cols.table");
	insert_calc_column(tab, "c0+c1+c2", NULL);
	result = sum_column(tab, 3);
	mu_assert("Wrong sum!\n", result == 15.);
	
	free_table(tab);
	return 0;
}

static char* test_sum_columns_and_powers() {
	
	double result;
	Type types[3] = {INT, INT, INT};
	Table* tab = new_table(3, NULL, types); 
	read_file(tab, "test_files/sum_cols.table");
	insert_calc_column(tab, "c1*c2^2", NULL);
	result = sum_column(tab, 3);
	mu_assert("Wrong sum of powers!\n", result == 20.);
	
	free_table(tab);
	return 0;
}

static char* test_column_swap() {

	int i, n_elements;
	Type types[4] = {INT, FLOAT, DOUBLE, STRING};
	Table* tab = new_table(4, NULL, types); 
	read_file(tab, "test_files/test_ifds.table");
	
	int i_arr[2] = {1,4};
	float f_arr[2] = {1.2,2.3};
	double d_arr[2] = {3.1234, 12.341234};
	char* s_arr[2] = {"test_string", "this_is_a_test"};
	
	int* i_arr_table = (int*)get_column(tab, 0, &n_elements);
	float* f_arr_table = (float*)get_column(tab, 1, &n_elements);
	double* d_arr_table = (double*)get_column(tab, 2, &n_elements);
	char** s_arr_table = (char**)get_column(tab, 3, &n_elements);
		
	mu_assert("Wrong number of elements!\n", n_elements == 2);
	for( i = 0; i < 2; i++ ){
		mu_assert("Wrong int element!", i_arr[i] == i_arr_table[i]);
		mu_assert("Wrong float element!", f_arr[i] == f_arr_table[i]);
		mu_assert("Wrong double element!", d_arr[i] == d_arr_table[i]);
		mu_assert("Wrong string element!",
			strcmp(s_arr[i], s_arr_table[i]) == 0);
	}
	
	free(i_arr_table);
	free(f_arr_table);
	free(d_arr_table);
	free(s_arr_table);
	
	swap_columns(tab, 0, 2);
	swap_columns(tab, 1, 3);
	
	i_arr_table = (int*)get_column(tab, 2, &n_elements);
	f_arr_table = (float*)get_column(tab, 3, &n_elements);
	d_arr_table = (double*)get_column(tab, 0, &n_elements);
	s_arr_table = (char**)get_column(tab, 1, &n_elements);
	
	mu_assert("Wrong number of elements!\n", n_elements == 2);
	for( i = 0; i < 2; i++ ){
		mu_assert("Wrong int element!", i_arr[i] == i_arr_table[i]);
		mu_assert("Wrong float element!", f_arr[i] == f_arr_table[i]);
		mu_assert("Wrong double element!", d_arr[i] == d_arr_table[i]);
		mu_assert("Wrong string element!",
			strcmp(s_arr[i], s_arr_table[i]) == 0);
	}
	
	free(i_arr_table);
	free(f_arr_table);
	free(d_arr_table);
	free(s_arr_table);
	free_table(tab);
	
	return 0;
}

static char* test_write_to_file() {
	
	FILE* fp;
	Table* tab1;
	Table* tab2;
	Type types[4] = {INT, FLOAT, DOUBLE, STRING};
	
	tab1 = new_table(4, NULL, types);
	tab2 = new_table(4, NULL, types); 
	
	fp = fopen("/tmp/test_write.txt", "w");
	read_file(tab1, "test_files/test_ifds.table");
	write_to_file(tab1, fp);
	fclose(fp);
	
	int n_elements;
	int* t1c0 = (int*)get_column(tab1, 0, &n_elements);
	float* t1c1 = (float*)get_column(tab1, 1, &n_elements);
	double* t1c2 = (double*)get_column(tab1, 2, &n_elements);
	char** t1c3 = (char**)get_column(tab1, 3, &n_elements);
	
	read_file(tab2, "/tmp/test_write.txt");
	
	int* t2c0 = (int*)get_column(tab2, 0, &n_elements);
	float* t2c1 = (float*)get_column(tab2, 1, &n_elements);
	double* t2c2 = (double*)get_column(tab2, 2, &n_elements);
	char** t2c3 = (char**)get_column(tab2, 3, &n_elements);
	
	int i;
	for( i = 0; i < 2; i++ ){
		mu_assert("Wrong int element!", t1c0[i] == t2c0[i]);
		mu_assert("Wrong float element!", t1c1[i] == t2c1[i]);
		mu_assert("Wrong double element!", t1c2[i] == t2c2[i]);
		mu_assert("Wrong string element!",
			strcmp(t1c3[i], t2c3[i]) == 0);
	}
	
	free_table(tab1);
	free_table(tab2);

	return 0;
}

static char* test_column_append() {
	return 0;
}

static char* test_column_insert() {
	return 0;
}

static char* all_tests() {

	mu_run_test(test_column_read_iii);
	mu_run_test(test_column_read_ifds);
	mu_run_test(test_column_swap);
	mu_run_test(test_column_append);
	mu_run_test(test_column_insert);
	mu_run_test(test_sum_columns);
	mu_run_test(test_sum_columns_and_powers);
	mu_run_test(test_write_to_file);
	return 0;
}

void tests_statistics() {
	
	int failed = tests_run - tests_passed;
	double ratio = (double)tests_passed/tests_run;
	printf("Passed %d tests out of %d.\n", tests_passed, tests_run);
	printf("Ratio: %f\n", ratio);
	printf("Failed: %d\n", failed);
}

int main( int argc, char** argv ) {
	
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
  
	tests_statistics();
  	
    return 0;
}

