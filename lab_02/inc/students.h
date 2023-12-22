#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include "consts.h"
#include "utils.h"
#include <time.h>
#include <sys/time.h>



//to do : move to consts to separate .h file

typedef enum {flat, dormitory, rented} housing_enum;
typedef enum {male, female} sex_enum;

typedef struct
{
    char street[MAX_STRING];
    int house_num;
    int flat_num;
} flat_t;

typedef struct
{
    int dorm_num;
    int room_num;
} dormitory_t;

typedef struct
{
    char street[MAX_STRING];
    int house_num;
    int flat_num;
    int price;
} rented_t;

typedef union
{
    flat_t flat_info;
    dormitory_t dormitory_info;
    rented_t rented_info;
} housing_t;

typedef struct
{
    int year;
    int month;
    int day;
} date_t;

typedef struct
{
    housing_enum housing_en;
    char surname[MAX_STRING];
    char name[MAX_STRING];
    sex_enum sex;
    int group_num;
    int age;
    double avg_exam_score;
    housing_t house_info;
    date_t admission_date;
} student_t;

/*
typedef struct
{
    тип жительства
    фамилия
    имя
    тип пола
    номер группы
    возраст
    средний балл за сессию
    структура информация о классе
    {

    }
    дата поступления;
} student_t;
*/

typedef struct
{
    int id;
    char surname[MAX_STRING];
} keys_t;


int check_int(char *tmp);
int read_command(int *command);
int read_table(student_t students[ARRAY_LEN], size_t *students_counter, size_t end);
int print_table(student_t students[ARRAY_LEN], size_t students_counter);
int dbg_print_table(student_t students[ARRAY_LEN], size_t students_counter);
int read_line(char *tmp);
int read_sex(sex_enum *tmp);
int read_fields(student_t *student);
int add_student(student_t students[ARRAY_LEN], size_t *students_counter);
void collect_buffer_garbage();
int searchprint_condition(student_t students[ARRAY_LEN], size_t counter);
void print_student(student_t student, size_t counter);
int lshift_arr(int id, student_t arr[ARRAY_LEN], size_t students_counter);
int delete_student(student_t students[ARRAY_LEN], size_t *students_counter);
int table_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter);
int key_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter);
int table_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter);
int keys_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter);
unsigned long long cur_ms_gettimeofday();
int measure_table_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter);
int measure_keys_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter);
int measure_table_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter);
int measure_keys_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter);
int print_efficiency_table();

#endif