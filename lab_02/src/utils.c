#include "utils.h"

int read_table(student_t students[ARRAY_LEN], size_t *students_counter)
{
    FILE *f;
    f = fopen("students_table.txt", "r");
    if (f == NULL)
    {
        puts("FILE OPENING ERROR");
        return FILE_ERROR;
    }

    char arr[MAX_LINE];
    student_t tmp;
    while (fgets(arr, MAX_LINE, f) != NULL)
    {
        //printf("%s\n", arr);
        if (arr[0] == '0') {
            if (sscanf(arr, "%d %s %s %d %d %d %lf %s %d %d %d %d %d",
                       &tmp.housing_en,
                       tmp.surname,
                       tmp.name,
                       &tmp.sex,
                       &tmp.group_num,
                       &tmp.age,
                       &tmp.avg_exam_score,
                       tmp.house_info.flat_info.street,
                       &tmp.house_info.flat_info.house_num,
                       &tmp.house_info.flat_info.flat_num,
                       &tmp.admission_date.year,
                       &tmp.admission_date.month,
                       &tmp.admission_date.day) != 13) {
                puts("LINE READING ERROR");
                return FILE_READING_ERROR;
            }
        } else if (arr[0] == '1') {
            if (sscanf(arr, "%d %s %s %d %d %d %lf %d %d %d %d %d",
                       &tmp.housing_en,
                       tmp.surname,
                       tmp.name,
                       &tmp.sex,
                       &tmp.group_num,
                       &tmp.age,
                       &tmp.avg_exam_score,
                       &tmp.house_info.dormitory_info.dorm_num,
                       &tmp.house_info.dormitory_info.room_num,
                       &tmp.admission_date.year,
                       &tmp.admission_date.month,
                       &tmp.admission_date.day) != 12) {
                puts("LINE READING ERROR");
                return FILE_READING_ERROR;
            }
        } else if (arr[0] == '2') {
            if (sscanf(arr, "%d %s %s %d %d %d %lf %s %d %d %d %d %d %d",
                       &tmp.housing_en,
                       tmp.surname,
                       tmp.name,
                       &tmp.sex,
                       &tmp.group_num,
                       &tmp.age,
                       &tmp.avg_exam_score,
                       tmp.house_info.rented_info.street,
                       &tmp.house_info.rented_info.house_num,
                       &tmp.house_info.rented_info.flat_num,
                       &tmp.house_info.rented_info.price,
                       &tmp.admission_date.year,
                       &tmp.admission_date.month,
                       &tmp.admission_date.day) != 14) {
                puts("LINE READING ERROR");
                return FILE_READING_ERROR;
            }
        }
        students[*students_counter] = tmp;
        ++*students_counter;
    }
    return 0;
}

void print_table(student_t students[ARRAY_LEN], size_t students_counter)
{
    //         8          40                                     9         5       9         12          12             40
    puts("+---------+----------------------------------------+---------+-----+---------+------------+------------+----------------------------------------+\n"
         "|    #    |       surname name                     | group   | sex |avg score| date of adm|  house type| Adress                                 |\n"
         "+---------+----------------------------------------+---------+-----+---------+------------+------------+----------------------------------------+\n");
    for (size_t i = 0; i < students_counter; i++)
    {
        char sex = (students[i].sex == male) ? 'm' : 'f';
        char date[10];
        sprintf(date, "%d.%d.%d", students[i].admission_date.day, students[i].admission_date.month, students[i].admission_date.year);
        char adress[40];
        char housing_string[12];
        switch (students[i].housing_en)
        {
            case flat:
                sprintf(housing_string, "flat");
                break;
            case dormitory:
                sprintf(housing_string, "dormitory");
                break;
            case rented:
                sprintf(housing_string, "rented");
                break;
        }

        sprintf(adress, "%s %d %d", students[i].house_info.flat_info.street, students[i].house_info.flat_info.house_num, students[i].house_info.flat_info.flat_num);
        printf("|%-8zu|%-20s %-19s|%-9d|%-5d|%-9lf|%-12s|%-12s|%-40s|", i, students[i].surname, students[i].name,
               students[i].group_num, sex, students[i].avg_exam_score, date, housing_string, adress);
    }
    puts("+---------+----------------------------------------+---------+-----+---------+----------+----------+----------------------------------------+\n");
}

void dbg_print_table(student_t students[ARRAY_LEN], size_t students_counter)
{
    for (size_t i = 0; i < students_counter; i++)
        printf("%s %s\n", students[i].surname, students[i].name);
}

void print_student(student_t student, size_t counter)
{
    char sex = (student.sex == male) ? 'm' : 'f';
    char date[10];
    sprintf(date, "%d.%d.%d", student.admission_date.day, student.admission_date.month, student.admission_date.year);
    char adress[40];
    char housing_string[12];
    switch (student.housing_en)
    {
        case flat:
            sprintf(housing_string, "flat");
            break;
        case dormitory:
            sprintf(housing_string, "dormitory");
            break;
        case rented:
            sprintf(housing_string, "rented");
            break;
    }

    sprintf(adress, "%s %d %d", student.house_info.flat_info.street, student.house_info.flat_info.house_num, student.house_info.flat_info.flat_num);
    printf("|%-8zu|%-20s %-19s|%-9d|%-5d|%-9lf|%-12s|%-12s|%-40s|", counter, student.surname, student.name,
           student.group_num, sex, student.avg_exam_score, date, housing_string, adress);

}