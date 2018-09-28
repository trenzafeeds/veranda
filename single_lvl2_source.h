/*
Testing Latin Squares Header File
Single Square, Testing to Level 2

v0.1.0
Kat Cannon-MacMartin
Marlboro College
*/

#ifndef TESTSINGLELVL2
#define TESTSINGLELVL2

#define MAXORDER 30

int order;

typedef struct _first_line *first_line;
struct _first_line{
  int order;
  int values[MAXORDER];
}
;
/*Make a _first_line struct for the next order*/
first_line generate_line(int order);

/*Delete first_line struct*/
void free_line(first_line line);

/*Prints line values to output file*/
void print_line(first_line subject, FILE *target_file);

/*Generate list of divisors of a number*/
void generate_divisors(int target, int *divisor_list);

/*Tests if line "works". Returns 1 (works) or 0 (does not work).*/
int test_line(first_line target);

/*Alters line in place to create every possible permutation and tests each one as it goes. Prints sucsessful results to the results file*/
void permute_test(first_line target, int start, FILE *result_file); 

/*Tests all iterations of a given order and writes results to a file.*/
void test_all_iterations(first_line subject, FILE *results_file);

#endif
