#ifndef __STUDENTS_H__
#define __STUDENTS_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "consts.h"
//#include "utils.h"


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

int read_line(char *tmp);
int read_sex(sex_enum *tmp);
int read_fields(student_t *student);
int add_student(student_t students[ARRAY_LEN], size_t *students_counter);
void collect_buffer_garbage();
int searchprint_condition(student_t students[ARRAY_LEN], size_t counter);

#endif