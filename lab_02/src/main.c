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
    printf("Hello, World!\n");
    print_table(students, students_counter);
    return 0;
}
