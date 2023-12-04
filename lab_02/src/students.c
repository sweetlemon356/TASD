#include "students.h"

int read_line(char *tmp)
{
    char tmp_string[MAX_STRING];
    if (fgets(tmp_string, MAX_STRING + 1, stdin) == NULL)
        return STRING_READING_ERROR;
    tmp_string[strcspn(tmp_string, "\n")] = '\0';
    if (strlen(tmp_string) >= MAX_STRING)
        return STRING_TOO_LONG;
    if (!strlen(tmp_string))
        return EMPTY_STRING;
    strncpy(tmp, tmp_string, MAX_STRING);
    return SUCCESS;
}

int read_sex(sex_enum *tmp)
{
    char tmp_string[MAX_STRING];
    if (fgets(tmp_string, MAX_STRING + 1, stdin) == NULL)
        return STRING_READING_ERROR;
    tmp_string[strcspn(tmp_string, "\n")] = '\0';
    if (strlen(tmp_string) >= MAX_STRING)
        return STRING_TOO_LONG;
    if (!strlen(tmp_string))
        return EMPTY_STRING;
    if (strcmp(tmp_string, "male") == 0)
        *tmp = male;
    else if (strcmp(tmp_string, "female") == 0)
        *tmp = female;
    else
        return INCORRECT_ENUM;
    return SUCCESS;
}

void collect_buffer_garbage()
{
    char tmp_string[MAX_STRING];
    fgets(tmp_string, MAX_STRING + 1, stdin);
}

int read_fields(student_t *student)
{

    int rc = 0;
    printf("Enter surname:\n");
    if ((rc = read_line(student->surname)))
        return rc;
    printf("Enter name:\n");
    if ((rc = read_line(student->name)))
        return rc;
    printf("Enter sex(male/female):\n");
    if ((rc = read_sex(&student->sex)))
        return rc;
    printf("Enter age:\n");
    if (scanf("%d", &student->age) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();

    printf("Enter group num:\n");
    if (scanf("%d", &student->group_num) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();

    printf("Enter average exam score:\n");
    if (scanf("%lf", &student->avg_exam_score) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();

    if (student->avg_exam_score > 5.0 || student->avg_exam_score < 2.0)
        return INCORRECT_INPUT;

    //read date
    printf("Enter year of admission:\n");
    if (scanf("%d", &student->admission_date.year) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();

    if (student->admission_date.year > 2023 || student->admission_date.year < 2000)
        return INCORRECT_INPUT;

    printf("Enter month of amission:\n");
    if (scanf("%d", &student->admission_date.month) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();

    if (student->admission_date.month > 12 || student->admission_date.month < 1)
        return INCORRECT_INPUT;

    printf("Enter day of admission:\n");
    if (scanf("%d", &student->admission_date.day) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();

    if (student->admission_date.day < 1 || student->admission_date.day  > 31)
        return INCORRECT_INPUT;

    printf("Enter type of housing (flat - 0, dormitory - 1, rented flat - 2):\n");
    int tmp;
    if (scanf("%d", &tmp) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();
    switch (tmp)
    {
        case 0:
            student->housing_en = flat;
            printf("Enter street:\n");
            if ((rc = read_line(student->house_info.flat_info.street)))
                return rc;

            printf("Enter house number:\n");
            if (scanf("%d", &student->house_info.flat_info.house_num) != 1)
                return INCORRECT_INPUT;
            collect_buffer_garbage();
            printf("Enter flat number:\n");
            if (scanf("%d", &student->house_info.flat_info.flat_num) != 1)
                return INCORRECT_INPUT;
            collect_buffer_garbage();
            break;
        case 1:
            student->housing_en = dormitory;
            printf("Enter dormitory number:\n");
            if (scanf("%d", &student->house_info.dormitory_info.dorm_num) != 1)
                return INCORRECT_INPUT;
            collect_buffer_garbage();
            printf("Enter room number:\n");
            if (scanf("%d", &student->house_info.dormitory_info.room_num) != 1)
                return INCORRECT_INPUT;
            collect_buffer_garbage();
            break;
        case 2:
            student->housing_en = rented;
            printf("Enter street:\n");
            if ((rc = read_line(student->house_info.rented_info.street)))
                return rc;

            printf("Enter house number:\n");
            if (scanf("%d", &student->house_info.rented_info.house_num) != 1)
                return INCORRECT_INPUT;
            collect_buffer_garbage();
            printf("Enter flat number:\n");
            if (scanf("%d", &student->house_info.rented_info.flat_num) != 1)
                return INCORRECT_INPUT;
            collect_buffer_garbage();
            printf("Enter price:\n");
            if (scanf("%d", &student->house_info.rented_info.price) != 1)
                return INCORRECT_INPUT;
            collect_buffer_garbage();
            break;

        default:
            return INCORRECT_INPUT;
    }
    return SUCCESS;
}


int add_student(student_t students[ARRAY_LEN], size_t *students_counter)
{
    student_t tmp;
    int rc = 0;
    if (*students_counter > ARRAY_LEN)
    {
        printf("The maximum number of students reached - %zu.\n", *students_counter);
        return 0;
    }
    if ((rc = read_fields(&tmp)))
        return rc;
    students[*students_counter] = tmp;
    ++*students_counter;
    printf("Student successfully added to the table. His number - %zu\n", *students_counter);
    return 0;
}

int searchprint_condition(student_t students[ARRAY_LEN], size_t students_counter)
{
    printf("Enter year of admission:\n");
    int year;
    size_t counter = 0;
    if (scanf("%d", &year) != 1)
        return INCORRECT_INPUT;

    printf("+---------+----------------------------------------+---------+-----+---------+------------+------------+----------------------------------------+\n"
           "|    #    |       surname name                     | group   | sex |avg score| date of adm|  house type| Adress                                 |\n"
           "+---------+----------------------------------------+---------+-----+---------+------------+------------+----------------------------------------+\n");

    for (size_t i = 0; i < students_counter; i++)
    {
        if (students[i].housing_en == rented && students[i].admission_date.year == year)
            print_student(students[i], ++counter);
    }
    printf("+---------+----------------------------------------+---------+-----+---------+----------+----------+----------------------------------------+\n");

    return SUCCESS;
}

