#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <string.h>
#include "consts.h"
#include "students.h"



int read_table(student_t students[ARRAY_LEN], size_t *students_counter);
void print_table(student_t students[ARRAY_LEN], size_t students_counter);
void dbg_print_table(student_t students[ARRAY_LEN], size_t students_counter);
void print_student(student_t student, size_t counter);

#endif