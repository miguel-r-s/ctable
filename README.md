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

## Performing calculations on data

The scouts are out to sell some cake! Scouts sell cake at different prices, and also collect donations.
The columns represent the scout's name, number of slices sold, price of each slice and total donations reveived.

```
Joe 10 3.99 2
Marta 8 14.49 10
Mike 3 39.00 2
Billy 220 0.99 2
```
Once we parse the file automatically into the structure, we get:

```
+------------+------------+-----------+-----------+
| Scout name | Units Sold | Price     | Donations | 
+------------+------------+-----------+-----------+
| Joe        | 10         | 3.990000  | 2.000000  | 
| Marta      | 8          | 14.490000 | 10.000000 | 
| Mike       | 3          | 39.000000 | 2.000000  | 
| Billy      | 220        | 0.990000  | 2.000000  | 
+------------+------------+-----------+-----------+
```
We now want to know how much money each of the scouts actually made. That's `column 1 * column 2 + column 3`, considering the column numbers are zero-indexed.

So we write `insert_calc_column(table, "c1*c2 + c3", "Scout's Total");`, and we get:

```
+------------+------------+-----------+-----------+---------------+
| Scout name | Units Sold | Price     | Donations | Scout's Total | 
+------------+------------+-----------+-----------+---------------+
| Joe        | 10         | 3.990000  | 2.000000  | 41.900000     | 
| Marta      | 8          | 14.490000 | 10.000000 | 125.920000    | 
| Mike       | 3          | 39.000000 | 2.000000  | 119.000000    | 
| Billy      | 220        | 0.990000  | 2.000000  | 219.800000    | 
+------------+------------+-----------+-----------+---------------+
```
It's simple and easy!

In the next commits, I'll probably add functions that allow us to operate on a specific column in an elegant way. For instance, we may want to calculate how much money all scouts generated. 

# Contributions
Any code is welcome!
