/*
Testing Latin Squares Main File
Single Square, Testing to Level 2

v0.3.0
Kat Cannon-MacMartin
Marlboro College
*/

#include <stdlib.h>
#include <stdio.h>

#include "single_lvl2_source.h"

int main(int argc, char *argv[]){

  if (argc < 2){
    printf("ERROR - No argument passed. Please pass an argument when you run this program.\n");
    return 1;
  }

  int start_point = 2;
  if (argc == 3){
    start_point = atoi(argv[2]);
  }

  int max_order = atoi(argv[1]);

  FILE *result_file = fopen("result_file.txt", "w");
  
  for (int subject_order = start_point; subject_order <= max_order; subject_order++){
    fprintf(result_file, "-----Order: %i-----\n", subject_order);
    
    first_line subject1 = generate_line(subject_order);
    first_line subject2 = generate_line(subject_order);
  
    test_all_iterations(subject1, subject2, result_file);

    free_line(subject1);
    free_line(subject2);

    fprintf(result_file, "\n");
  }

  return 0;
}

    
