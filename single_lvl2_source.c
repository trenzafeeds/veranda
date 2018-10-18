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
#define MAXDIVISORS 10

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

int find_level_add(int first, int second, int order){
  int val = abs(second - first);
  if (val <= ((float) order / 2)){
    return val;
  }
  else{
    return (order - val);
  }
}

int test_line(first_line target, FILE *result_file, int *single_inc_level, int *double_inc_level){
  //int single_inc_level[target->order - 1];
  //int double_inc_level[target->order - 2];
  int add_holder;
  int cntr = 0;
  float half_compare = ((float) target->order / 2);
  wipe_lists(single_inc_level, double_inc_level, target->order);
  //fprintf(result_file, "\nTHIS IS THE LINE ");
  /*for (int y = 0; y < target->order - 1; y++){
    fprintf(result_file, "%i ", single_inc_level[y]);
    }*/
  //fprintf(result_file, "\nFIRST LEVEL TEST \n");
  for (int x = 1; x < target->order; x++){
    add_holder = find_level_add(target->values[x-1], target->values[x], target->order);
    //fprintf(result_file, "First: %i Second: %i NEW ADD: %i \n", target->values[x-1], target->values[x], add_holder);
    for (int i = 0; i < target->order - 1; i++){
      if(add_holder == single_inc_level[i]){
	if (add_holder == half_compare){
	  //printf("HALF FAIL\n");
	  return 0;
	}
	cntr++;
        //fprintf(result_file, "CNTR: %i \n", cntr);
	if (cntr > 1){
	  return 0;
	}
      }
    }
    cntr = 0;
    single_inc_level[x-1] = add_holder;
  }
  cntr = 0;
  add_holder = 0;
  //fprintf(result_file, "\nSECOND LEVEL TEST \n");
  wipe_lists(single_inc_level, double_inc_level, target->order);
  for(int x = 2; x < target->order; x++){
    add_holder = find_level_add(target->values[x-2], target->values[x], target->order);
    //fprintf(result_file, "First: %i Second: %i NEW ADD: %i \n", target->values[x-2], target->values[x], add_holder);
    for (int i = 0; i < target->order - 2; i++){
      if(add_holder == double_inc_level[i]){
	if (add_holder == half_compare){
	  // printf("HALF FAIL\n");
	  return 0;
	}
        cntr++;
	//fprintf(result_file, "CNTR: %i \n", cntr);
	if (cntr > 1){
	  return 0;
	}
      }
    }
    cntr = 0;
    double_inc_level[x-2] = add_holder;
  }
  return 1;
}
	

void permute_test(first_line target, int start, FILE *result_file, int *single_inc_level, int *double_inc_level){
  if (target->order == start){
    
    if (test_line(target, result_file, single_inc_level, double_inc_level) == 1){
      //fprintf(result_file, "TEST PASS\n");
      print_line(target, result_file);
    }
    
    
    //print_line(target, result_file);
    return;
  }

  int j = start;
  for (j = start; j < target->order; j++){
    int holder = target->values[start];
    target->values[start] = target->values[j];
    target->values[j] = holder;
    permute_test(target, start + 1, result_file, single_inc_level, double_inc_level);
    holder = target->values[j];
    target->values[j] = target->values[start];
    target->values[start] = holder;
  }
  return;
}

void test_all_iterations(first_line subject, FILE *results_file){

  int *divisor_list = malloc(sizeof(int) * MAXDIVISORS);
  int *single_inc_level = malloc(sizeof(int) * (subject->order - 1));
  int *double_inc_level = malloc(sizeof(int) * (subject->order - 2));

  generate_divisors(subject->order, divisor_list);

  //printf("TESTING\n");

  /* ----TESTING PRINT----
  fprintf(results_file, "\nDIVISOR LIST: ");
  for (int t = 0; t < 9; t++){
    fprintf(results_file, "%i ", divisor_list[t]);
  }
  fprintf(results_file, "\n\n");*/
  

  for (int i = 0; i < MAXDIVISORS; i++){

    if (divisor_list[i] == subject->values[1]){
      goto TESTY;
    }
    
    if (divisor_list[i] == 0){
      break;
    }
    
    fprintf(results_file, "\n");
    for (int x = 2; x <= subject->order; x++){
      if (divisor_list[i] == subject->values[x]){
	subject->values[x] = subject->values[1];
	subject->values[1] = divisor_list[i];
        break;
      }
    }
  TESTY:permute_test(subject, 2, results_file, single_inc_level, double_inc_level);
  }
  free(divisor_list);
}

    
