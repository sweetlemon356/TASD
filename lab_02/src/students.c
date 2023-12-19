#include "students.h"


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

int print_table(student_t students[ARRAY_LEN], size_t students_counter)
{
    //         8          40                                     9         5       9         12          12             40
    puts("+---------+----------------------------------------+---------+-----+---------+------------+------------+----------------------------------------+\n"
         "|    #    |       Фамилия Имя                      | группа  | пол | оценка  | дата пост  |тип жилища  | Адресс                                 |\n"
         "+---------+----------------------------------------+---------+-----+---------+------------+------------+----------------------------------------+");
    for (size_t i = 0; i < students_counter; i++)
    {
        char sex = (students[i].sex == male) ? 'm' : 'f';
        char date[11];
        sprintf(date, "%d.%d.%d", students[i].admission_date.day, students[i].admission_date.month, students[i].admission_date.year);

        char housing_string[12];
        char adress[40];
        switch (students[i].housing_en)
        {
            case flat:
                sprintf(housing_string, "квартира");
                sprintf(adress, "%s %d %d", students[i].house_info.flat_info.street, students[i].house_info.flat_info.house_num, students[i].house_info.flat_info.flat_num);
                break;
            case dormitory:
                sprintf(housing_string, "общежите");
                sprintf(adress, "№%d комната %d", students[i].house_info.dormitory_info.dorm_num, students[i].house_info.dormitory_info.room_num);
                break;
            case rented:
                sprintf(housing_string, "съемное");
                sprintf(adress, "%s %d %d", students[i].house_info.rented_info.street, students[i].house_info.rented_info.house_num, students[i].house_info.rented_info.flat_num);
                break;
        }
        
        //          i      name     gr   sex   scr  date   ht   adr
        printf("|%-9zu|%-20s %-19s|%-9d|%-5s|%-9lf|%-12s|%-12s|%-40s|\n",
                i,
                students[i].surname,
                students[i].name,
                students[i].group_num,
                sex,
                students[i].avg_exam_score,
                date,
                housing_string,
                adress);
    }
    puts("+---------+----------------------------------------+---------+-----+---------+------------+------------+----------------------------------------+");
    return SUCCESS;
}

int dbg_print_table(student_t students[ARRAY_LEN], size_t students_counter)
{
    for (size_t i = 0; i < students_counter; i++)
        printf("%s %s\n", students[i].surname, students[i].name);
    return SUCCESS;
}

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

int lshift_arr(int id, student_t arr[ARRAY_LEN], size_t student_counter)
{
    for (int i = id; i < (int)student_counter - 1; i++)
        arr[i] = arr[i + 1];
    return 0;
}

int delete_student(student_t students[ARRAY_LEN], size_t *students_counter)
{
    if (*students_counter == 0)
    {
        printf("Table is empty.\n");
        return SUCCESS;
    }
    print_table(students, *students_counter);
    printf("Enter id of element you want to delete\n");
    int id = -1;
    if (scanf("%d", &id) != 1)
        return INCORRECT_INPUT;
    collect_buffer_garbage();
    if (id <= 0 && id > (int)*students_counter)
        return INCORRECT_INPUT;
    lshift_arr(id - 1, students, *students_counter);
    --*students_counter;
    printf("Deleted successfully\n");
    return SUCCESS;
}

int table_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    if (student_counter == 0)
    {
        printf("Table is empty.\n");
        return SUCCESS;
    }
    if (student_counter == 1)
    {
        printf("Only one element in the table");
        return SUCCESS;
    }
    printf("Table before sorting:\n");
    dbg_print_table(students, student_counter);
    for (size_t i = 0; i < student_counter - 1; i++)
        for (size_t j = student_counter - 1; j > i; j--)
            if (strcmp(students[j - i].surname, students[j].surname) > 0)
            {
                student_t tmp = students[j - i];
                students[j - 1] = students[j];
                students[j] = tmp;
            }
    printf("Table after sorting:\n");
    dbg_print_table(students, student_counter);
    return SUCCESS;
}

int key_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    if (student_counter == 0)
    {
        printf("Table is empty.\n");
        return SUCCESS;
    }
    if (student_counter == 1)
    {
        printf("Only one element in the table");
        return SUCCESS;
    }
    printf("Table before sorting:\n");
    dbg_print_table(students, student_counter);
    keys_t keys[ARRAY_LEN];
    for (size_t i = 0; i < student_counter - 1; i++)
    {
        keys[i].id = i;
        strncpy(keys[i].surname, students[i].surname, MAX_STRING);
    }
    for (size_t i = 0; i < student_counter - 1; i++)
        for (size_t j = student_counter - 1; j > i; j--)
            if (strcmp(keys[j - 1].surname, keys[j].surname) > 0)
            {
                keys_t tmp = keys[j - 1];
                keys[j - 1] = keys[j];
                keys[j] = tmp;
            }
    printf("After sorting");
    for (size_t i = 0; i < student_counter; i++)
        print_student(students[keys[i].id], i + 1);
    return SUCCESS;
}

int table_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    if (student_counter == 0)
    {
        printf("Table is empty.\n");
        return SUCCESS;
    }
    if (student_counter == 1)
    {
        printf("Only one element in the table");
        return SUCCESS;
    }
    printf("Table before sorting:\n");
    dbg_print_table(students, student_counter);
    for (int i = 1; i < (int)student_counter; i++)
    {
        student_t key = students[i];
        int low, mid, high;
        low = 0;
        high = i;
        while (low < high)
        {
            mid = low + (high - low) / 2;
            if (strcmp(key.surname, students[mid].surname) < 0)
                high = mid;
            else
                low = mid + 1;
        }
        for (int j = i; j > low; j--)
            students[j] = students[j - 1];
        students[low] = key;
    }
    printf("Table after sorting:\n");
    dbg_print_table(students, student_counter);
    return SUCCESS;
}

int keys_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    if (student_counter == 0)
    {
        printf("Table is empty.\n");
        return SUCCESS;
    }
    if (student_counter == 1)
    {
        printf("Only one element in the table");
        return SUCCESS;
    }
    printf("Table before sorting:\n");
    dbg_print_table(students, student_counter);
    keys_t keys[ARRAY_LEN];
    for (size_t i = 0; i < student_counter; i++)
    {
        keys[i].id = i;
        strncpy(keys[i].surname, students[i].surname, MAX_STRING);
    }
    for (int i = 1; i < (int)student_counter; i++)
    {
        keys_t key  = keys[i];
        int low, high, mid;
        low = 0;
        high = i;
        while (low < high)
        {
            mid = low + (high - low) / 2;
            if (strcmp(key.surname, keys[mid].surname) < 0)
                high = mid;
            else
                low = mid + 1;
        }
    }
    for (size_t i = 0; i < student_counter; i++)
        print_student(students[keys[i].id], i + 1);
    return SUCCESS;
}

unsigned long long cur_ms_gettimeofday()
{
    struct timeval timeval;
    gettimeofday(&timeval, NULL);
    return (timeval.tv_sec * 1000000 + timeval.tv_usec);
}

int measure_table_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    for (size_t i = 0; i < student_counter - 1; i++)
        for (size_t j = student_counter - 1; j > i; j--)
            if (strcmp(students[j - i].surname, students[j].surname) > 0)
            {
                student_t tmp = students[j - i];
                students[j - 1] = students[j];
                students[j] = tmp;
            }
    return SUCCESS;
}
int measure_keys_bubble_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    keys_t keys[ARRAY_LEN];
    for (size_t i = 0; i < student_counter - 1; i++)
    {
        keys[i].id = i;
        strncpy(keys[i].surname, students[i].surname, MAX_STRING);
    }
    for (size_t i = 0; i < student_counter - 1; i++)
        for (size_t j = student_counter - 1; j > i; j--)
            if (strcmp(keys[j - 1].surname, keys[j].surname) > 0)
            {
                keys_t tmp = keys[j - 1];
                keys[j - 1] = keys[j];
                keys[j] = tmp;
            }
    return SUCCESS;
}
int measure_table_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    for (int i = 1; i < (int)student_counter; i++)
    {
        student_t key = students[i];
        int low, mid, high;
        low = 0;
        high = i;
        while (low < high)
        {
            mid = low + (high - low) / 2;
            if (strcmp(key.surname, students[mid].surname) < 0)
                high = mid;
            else
                low = mid + 1;
        }
        for (int j = i; j > low; j--)
            students[j] = students[j - 1];
        students[low] = key;
    }
    return SUCCESS;
}
int measure_keys_insertion_sort(student_t students[ARRAY_LEN], size_t student_counter)
{
    keys_t keys[ARRAY_LEN];
    for (size_t i = 0; i < student_counter; i++)
    {
        keys[i].id = i;
        strncpy(keys[i].surname, students[i].surname, MAX_STRING);
    }
    for (int i = 1; i < (int)student_counter; i++)
    {
        keys_t key  = keys[i];
        int low, high, mid;
        low = 0;
        high = i;
        while (low < high)
        {
            mid = low + (high - low) / 2;
            if (strcmp(key.surname, keys[mid].surname) < 0)
                high = mid;
            else
                low = mid + 1;
        }
    }
    return SUCCESS;
}

int print_efficiency_table()
{
    student_t students[ARRAY_LEN];
    size_t students_counter = 0;
    unsigned long long t1, t2, t3, t4;
    t1 = 0;
    t2 = 0;
    t3 = 0;
    t4 = 0;
    printf("Таблица сравнения эффектвностей.");
    for (size_t i = 10; i <= 100; i += 10)
    {
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_table_bubble_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t1 += tmp;
        }
        t1 /= 100;
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_keys_bubble_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t2 += tmp;
        }
        t2 /= 100;
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_table_insertion_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t3 += tmp;
        }
        t3 /= 100;
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_keys_insertion_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t4 += tmp;
        }
        t4 /= 100;
        printf("|%3zu|%30llu|%30llu|%30llu|%30llu|\n", i, t1, t2, t3, t4);
    }

    printf("таблица сравненя эффективностии в процентном соотношении:\n");
    printf("│ # │ Занимаемый %% массива ключей  │ %% роста скорости с ключами(п)│ %% роста скорости с ключами(в)│\n");
    for (size_t i = 10; i <= 100; i += 10)
    {
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_table_bubble_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t1 += tmp;
        }
        t1 /= 100;
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_keys_bubble_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t2 += tmp;
        }
        t2 /= 100;
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_table_insertion_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t3 += tmp;
        }
        t3 /= 100;
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            read_table(students, &students_counter);
            tmp = cur_ms_gettimeofday();
            measure_keys_insertion_sort(students, students_counter);
            tmp = cur_ms_gettimeofday() - tmp;
            t4 += tmp;
        }
        t4 /= 100;
        printf("│%3zu│%30d│%30d│%30d│\n", i, (int)(i * sizeof(keys_t) / (i * sizeof(student_t) / 100.0)), (int)((t1*1.0)/t2 * 100), (int)((t3*1.0)/t4 * 100));
    }
    printf("Таблица сравнения эффективности сортировок по памяти(байты):\n");
    for (size_t i = 10; i <= 100; i+=10)
    {
        t1 = i * sizeof(student_t);
        t2 = i * sizeof(student_t) + i * sizeof(keys_t);
        t3 = i * sizeof(student_t);
        t4 = i * sizeof(student_t) + i * sizeof(keys_t);
        printf("│%3zu│%30llu│%30llu│%30llu│%30llu│\n", i, t1, t2, t3, t4);
    }
    return SUCCESS;
}


int check_int(char *tmp)
{
    int i = 0;
    while (tmp[i] != '\0') {
        if (!isdigit(tmp[i]))
            return 1;
        i++;
    }
    return 0;
}


int read_command(char *tmp, int *command)
{
    if (read_line(tmp))
        return INCORRECT_INPUT;
    if (check_int(tmp))
        return INCORRECT_INPUT;
    if (sscanf(tmp, "%d", command) != 1)
        return INCORRECT_INPUT;
    if (*command < 0 || *command > 10)
        return INCORRECT_INPUT;
    return 0;
}


