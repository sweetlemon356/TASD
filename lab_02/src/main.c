#include <stdio.h>
#include "students.h"
#include "utils.h"

int main()
{
    student_t students[ARRAY_LEN];
    size_t students_counter = 0;
    int rc;
    rc = read_table(students, &students_counter);
    if (rc != 0)
        return rc;

    rc = add_student(students, &students_counter);
    if (rc != 0)
        return rc;
    dbg_print_table(students, students_counter);
    rc = searchprint_condition(students, students_counter);
    if (rc != 0)
        return rc;
    return SUCCESS;
}
