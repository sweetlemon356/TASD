#include <stdio.h>
#include "students.h"


int main()
{
    student_t students[ARRAY_LEN];
    size_t students_counter = 0;
    int rc;
    rc = read_table(students, &students_counter);
    if (rc != 0)
        return rc;

    //rc = add_student(students, &students_counter);

    dbg_print_table(students, students_counter);
    //rc = searchprint_condition(students, students_counter);

    print_table(students, students_counter);
    delete_student(students, &students_counter);
    print_table(students, students_counter);
    return SUCCESS;
}
