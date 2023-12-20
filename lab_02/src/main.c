#include <stdio.h>
#include "students.h"
#include <windows.h>



int main()
{
    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);
    student_t students[ARRAY_LEN];
    size_t students_counter = 0;
    char tmp[MAX_STRING];
    int flag = 1;
    int command = 0;
    while (flag)
    {
        printf("Меню команд, выберите пункт, который вас интересует.\n");
        printf("1: Заполнить таблицу рандомными 50-ю элементами.\n");
        printf("2: Вывести таблицу.\n");
        printf("3: Добавить элемент в таблицу.\n");
        printf("4: Отсортировать таблицу методом пузырька.(сортировка самой таблицы)\n");
        printf("5: Отсортировать таблицу методом пузырька.(сортировка с вспомогательной таблицей)\n");
        printf("6: Отсортировать таблицу методом вставок бин. поиском(сортировка самой таблицы)\n");
        printf("7: Отсортировать таблицу методом вставок бин. поиском(сортировка с вспомогательной таблицей)\n");
        printf("8: Удалить элемент из таблицы.\n");
        printf("9: Вывести список всех студентов живущих в общежитие, поступивших в указанный год\n");
        printf("10: Вывести таблицы сравнения эффективности сортировок.\n");
        printf("0: Выход.\n");
        printf(">");
        if (read_command(tmp, &command))
        {
            printf("Ошибка при вводе, попробуйте еще раз.\n");
        }
        else
        {
            switch (command)
            {
                case 1:
                    if (read_table(students, &students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 2:
                    print_student(students[0], students_counter);
                    if (print_table(students, students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 3:
                    if (add_student(students, &students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 4:
                    if (table_bubble_sort(students, students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 5:
                    if (key_bubble_sort(students, students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 6:
                    if (table_insertion_sort(students, students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 7:
                    if (keys_insertion_sort(students, students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 8:
                    if (delete_student(students, &students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 9:
                    if (searchprint_condition(students, students_counter))
                        printf("При работе возникла ошибка, проверьте вводимые данные и попробуйте снова.\n");
                    break;
                case 10:
                    print_efficiency_table();
                    break;
                case 0:
                    flag = 0;
                    break;
                default:
                    printf("Ошибка при вводе, попробуйте еще раз.\n");
                    break;
            }
        }
    }
    return 0;
}
