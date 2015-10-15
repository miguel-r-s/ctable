# ctable
A lightweight library for tabular representations of data in C.

# Example

Consider the info in `armstrong.txt`:

```
  1 one a
  2 small b
  3 step c
  4 for d
  5 man e
  6 one f
  7 giant g
  8 leap h 
  9 for i
  10 mankind j
```

You want to store it in some sort of data structure and later print it, add new information or simply retrieve it.
This is not the most interesting task to do in C, specially if you later want to change the column types, or add more columns. 

This library implements these functions in a simple-to-use way.

## Reading and printing information

```
  char* col_names[3] = {"integer column", "string column", "char column"};
  Type* types[3] = {INT, STRING, CHAR};
  Table* tab = new_table(3, names, types);

  read_file(tab, "armstrong.txt");
```
As simpe as these 4 lines of code, your info is now stored in the `Table* tab`.

For a visual representation of the information in the structure, we use `print_table(tab)`, which prints:
```
+----------------+---------------+-------------+
| integer column | string column | char column | 
+----------------+---------------+-------------+
| 1              | one           | a           | 
| 2              | small         | b           | 
| 3              | step          | c           | 
| 4              | for           | d           | 
| 5              | man           | e           | 
| 6              | one           | f           | 
| 7              | giant         | g           | 
| 8              | leap          | h           | 
| 9              | for           | i           | 
| 10             | mankind       | j           | 
+----------------+---------------+-------------+
```

You can also later retrieve the information in a given column with:
```
char_column = (char*)get_column(tab, 2, &n_elements)
```

`get_column` returns a `void*` type you can later cast to whatever type you are fetching. 

The return in this example would be the array containing `a b c d e f g h i j`.

# Contributions
Any code is welcome!
