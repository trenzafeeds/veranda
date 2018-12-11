/*
Testing Latin Squares Implementation File
Single Square, Testing to Level 2

v1.0z.0
Kat Cannon-MacMartin
Marlboro College

Sources:
SRC1 - Permutations - https://stackoverflow.com/a/9148661
*/

#include <stdlib.h>
#include <stdio.h>

#include "single_lvl2_source.h"

#define MAXORDER 30
#define MAXDIVISORS 10

int modulo(int x,int N){
    return (x % N + N) %N;
}

first_line generate_line(int order){
  first_line line = malloc(sizeof(struct _first_line));
  line->order = order;
  for (int i = 0; i < order; i++){
    line->values[i] = i;
  }
  return line;
}

void free_line(first_line line){
  free(line);
}

void wipe_lists(int *list_1, int *list_2, int order){
  for (int y = 0; y < order - 1; y++){
    list_1[y] = 0;
  }

  for (int z = 0; z < order - 2; z++){
    list_2[z] = 0;
  }
}
		
void print_line(first_line subject, FILE *target_file){
  for (int i = 0; i < subject->order; i++){
    fprintf(target_file, "%i ", subject->values[i]);
  }
  fprintf(target_file, "\n");
}

void generate_divisors(int target, int *divisor_list){
  int array_counter = 0;
  for (int t = 0; t < MAXDIVISORS; t++){
    divisor_list[t] = 0;
  }
  for (int i = 1; i < target; i++){
    if (target % i == 0){
	divisor_list[array_counter] = i;
	array_counter++;
      }
  }
}

int test_lines(first_line target1, first_line target2, int *single_inc_level1, int *single_inc_level2, int* double_inc_level1, int *double_inc_level2, FILE *result_file){

  int added = 0;
  int counter = 0;

  int i = 0;
  int l = 0;
  
  for (i = 0; i < (target1->order - 1); i++){
    added = modulo((target1->values[i] - target1->values[i+1]), target1->order);
    //fprintf(result_file, "Added: %i\n", added);
    for (l = 0; l < i; l++){
      if (added == single_inc_level1[l]){
        counter++;
	//fprintf(result_file, "Counter: %i\n", counter);
        if (counter > 1){
          return 0;
        }
      }
    }
    counter = 0;
    single_inc_level1[i] = added;
  }

  for (i = 0; i < (target2->order - 1); i++){
    added = modulo((target2->values[i] - target2->values[i+1]), target1->order);
    //fprintf(result_file, "Added: %i\n", added);
    for (l = 0; l < (target1->order - 1); l++){
      if (added == single_inc_level1[l]){
	counter++;
	//fprintf(result_file, "Counter: %i\n", counter);
	if (counter > 1){
	  return 0;
	}
      }
    }
    for (l = 0; l < i; l++){
      if (added == single_inc_level2[l]){
	counter++;
	//fprintf(result_file, "Counter: %i\n", counter);
	if (counter > 1){
	  return 0;
	}
      }
    }
    counter = 0;
    single_inc_level2[i] = added;
  }

  for (i = 0; i < (target1->order - 2); i++){
    added = modulo((target1->values[i] - target1->values[i+2]), target1->order);
    //fprintf(result_file, "Added: %i\n", added);
    for (l = 0; l < i; l++){
      if (added == double_inc_level1[l]){
	counter++;
	//fprintf(result_file, "Counter: %i\n", counter);
	if (counter > 1){
	  return 0;
	}
      }
    }
    counter = 0;
    double_inc_level1[i] = added;
  }

  for (i = 0; i < (target2->order - 2); i++){
    added = modulo((target2->values[i] - target2->values[i+2]), target1->order);
    //fprintf(result_file, "Added: %i\n", added);
    for (l = 0; l < (target1->order - 2); l++){
      if (added == double_inc_level1[l]){
	counter++;
	//fprintf(result_file, "Counter: %i\n", counter);
	if (counter > 1){
	  return 0;
	}
      }
    }
    for (l = 0; l < i; l++){
      if (added == double_inc_level2[l]){
	counter++;
	//fprintf(result_file, "Counter: %i\n", counter);
	if (counter > 1){
	  return 0;
	}
      }
    }
    counter = 0;
    double_inc_level2[i] = added;
  }
  
  return 1;
}

int test_two(first_line target1, first_line target2, int *single_inc_level1, int *single_inc_level2, int *double_inc_level1, int *double_inc_level2, FILE *result_file){

  for (int i = 0; i < (target1->order - 1); i++){
    single_inc_level1[i] = 0;
    single_inc_level2[i] = 0;
  }
  for (int l = 0; l < (target1->order - 2); l++){
    double_inc_level1[l] = 0;
    double_inc_level2[l] = 0;
  }

  if (test_lines(target1, target2, single_inc_level1, single_inc_level2, double_inc_level1, double_inc_level2, result_file) == 1){
    return 1;
  }
  else{
    return 0;
  }
}
 
void permute_test(first_line target1, first_line target2, int start, FILE *result_file, int *single_inc_level1, int *single_inc_level2, int *double_inc_level1, int *double_inc_level2, int which){
  if (target1->order == start){

    if (which == 0){
      permute_test(target2, target1, 1, result_file, single_inc_level1, single_inc_level2, double_inc_level1, double_inc_level2, which + 1);
    }
    
    else if (which == 1){
      if (test_two(target1, target2, single_inc_level1, single_inc_level2, double_inc_level1, double_inc_level2, result_file) == 1){
        fprintf(result_file, "\n");
        print_line(target1, result_file);
        print_line(target2, result_file);
      }
    }
    
    else{
      fprintf(result_file, "$which HAS VALUE %i", which);
    }
      
    //print_line(target, result_file);
    return;
  }

  int j = start;
  for (j = start; j < target1->order; j++){
    int holder = target1->values[start];
    target1->values[start] = target1->values[j];
    target1->values[j] = holder;
    permute_test(target1, target2, start + 1, result_file, single_inc_level1, single_inc_level2, double_inc_level1, double_inc_level2, which);
    holder = target1->values[j];
    target1->values[j] = target1->values[start];
    target1->values[start] = holder;
  }
  return;
}

void test_all_iterations(first_line target1, first_line target2, FILE *results_file){

  int *divisor_list = malloc(sizeof(int) * MAXDIVISORS);
  int *single_inc_level1 = malloc(sizeof(int) * (target1->order - 1));
  int *single_inc_level2 = malloc(sizeof(int) * (target1->order - 1));
  int *double_inc_level1 = malloc(sizeof(int) * (target1->order - 2));
  int *double_inc_level2 = malloc(sizeof(int) * (target1->order - 2));

  generate_divisors(target1->order, divisor_list);

  /* ----TESTING PRINT----
  fprintf(results_file, "\nDIVISOR LIST: ");
  for (int t = 0; t < 9; t++){
    fprintf(results_file, "%i ", divisor_list[t]);
  }
  fprintf(results_file, "\n\n");*/
  

  for (int i = 0; i < MAXDIVISORS; i++){

    if (divisor_list[i] == target1->values[1]){
      goto TESTY;
    }
    
    if (divisor_list[i] == 0){
      break;
    }
    
    fprintf(results_file, "\n");
    for (int x = 2; x <= target1->order; x++){
      if (divisor_list[i] == target1->values[x]){
	target1->values[x] = target1->values[1];
	target1->values[1] = divisor_list[i];
        break;
      }
    }
  TESTY:permute_test(target1, target2, 2, results_file, single_inc_level1, single_inc_level2, double_inc_level1, double_inc_level2, 0);
  }
  free(divisor_list);
  free(single_inc_level1);
  free(single_inc_level2);
  free(double_inc_level1);
  free(double_inc_level2);
}

    
