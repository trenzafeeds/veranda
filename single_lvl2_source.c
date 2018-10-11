/*
Testing Latin Squares Implementation File
Single Square, Testing to Level 2

v0.1.0
Kat Cannon-MacMartin
Marlboro College

Sources:
SRC1 - Permutations - https://stackoverflow.com/a/9148661
*/

#include <stdlib.h>
#include <stdio.h>

#include "single_lvl2_source.h"

#define MAXORDER 30
#define MAXDIVISORS 7

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

int find_level_add(int first, int second, int order){
  int val = (second - first) % 7;
  if (val < ((float) order / 2)){
    return val;
  }
  else{
    return (order - val);
  }
}

int test_line(first_line target){
  int lvl2_line[target->order - 1];
  int lvl3_line[target->order - 2];
  int lvl1_add;
  int lvl2_add;
  int cntr = 0;
  for (int x = 0; x < (target->order - 1); x++){
    lvl1_add = find_level_add(target->values[x], target->values[x+1], target->order);
    for (int i = 0; i < x; i++){
	if (lvl1_add == lvl2_line[i]){
          cntr++;
	  if (cntr > 0){
	    return 0;
	  }
	}
	cntr = 0;
    }
    lvl2_line[x] = lvl1_add;
    if (x){
      lvl2_add = find_level_add(lvl2_line[x-1], lvl2_line[x], target->order);
      lvl2_add = lvl2_line[x-1] - lvl2_line[x];
      for(int i = 0; i < (x - 1); i++){
	if (lvl2_add == lvl3_line[i]){
          cntr++;
	  if (cntr > 1){
	    return 0;
	  }
	}
	cntr = 0;
      }
      lvl3_line[x-1] = lvl2_add;
    }
  }
  return 1;
}

void permute_test(first_line target, int start, FILE *result_file){
  if (target->order == start){

    if (test_line(target) == 1){
      print_line(target, result_file);
    }
    return;
  }

  int j = start;
  for (j = start; j < target->order; j++){
    int holder = target->values[start];
    target->values[start] = target->values[j];
    target->values[j] = holder;
    permute_test(target, start + 1, result_file);
    holder = target->values[j];
    target->values[j] = target->values[start];
    target->values[start] = holder;
  }
  return;
}

void test_all_iterations(first_line subject, FILE *results_file){

  int *divisor_list = malloc(sizeof(int) * MAXDIVISORS);

  generate_divisors(subject->order, divisor_list);

  /* ----TESTING PRINTS----
  fprintf(results_file, "\nDIVISOR LIST: ");
  for (int t = 0; t < 9; t++){
    fprintf(results_file, "%i ", divisor_list[t]);
  }
  fprintf(results_file, "\n");
  */

  for (int i = 0; i < MAXDIVISORS; i++){

    if (divisor_list[i] == subject->values[1]){
      goto TESTY;
    }
    
    if (divisor_list[i] == 0){
      break;
    }
    
    fprintf(results_file, "\n");
    for (int x = 2; x < subject->order; x++){
      if (divisor_list[i] == subject->values[x]){
	subject->values[x] = subject->values[1];
	subject->values[1] = divisor_list[i];
        break;
      }
    }
    TESTY:permute_test(subject, 2, results_file);
  }
  free(divisor_list);
}

    
