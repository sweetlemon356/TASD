#include <stdio.h>
#include "my_stack.h"
#include <windows.h>
/*
Проверить является ли число палиндромом
*/

int main(void)
{

    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);

    stack_list_t *stack = malloc(sizeof(stack_list_t));
    (stack)->head = NULL;
    (stack)->count = 0;
    stack_arr arr;
    arr.count = 0;
    int rc = 0;
    int flag = 1;
    string tmp;
    string line;
    size_t llen = 0;
    char symb;
    int command = 0;
    while (flag)
    {
        printf("Меню команд, выберите пункт, который вас интересует.\n");
        printf("1: Проверить является ли число палиндромом(реализается через массив).\n");
        printf("2: Проверить является ли число палиндромом(реалиизается через список).\n");
        printf("3: Вывести информацию о стеке(массив).\n");
        printf("4: Вывести информацию о стеке(список).\n");
        printf("5: Сравнение реализаций.\n");
        printf("6: Добавить элемент(массив).\n");
        printf("7: Вывсти верхний элемент(массив).\n");
        printf("8: Удалить верхний элемент(массив).\n");
        printf("9: Добавить элемент(массив).\n");
        printf("10: Вывсти верхний элемент(массив).\n");
        printf("11: Удалить верхний элемент(массив).\n");
        printf("0: Выход.\n");
        printf(">");
        if (read_command(tmp, &command))
        {
            printf("Ошибка при вводе, попробуйте ещё раз.\n");
        }
        else
        {
            switch (command)
            {
                case 0:
                    ;
                    return 0;
                    break;
                case 1:
                    llen = 0;
                    get_line(line, &llen);
                    check_palindrome_arr(line, llen, &arr);
                    break;
                case 2:
                    llen = 0;
                    get_line(line, &llen);
                    check_palindrome_stlist(line, llen, stack);
                    break;
                case 3:
                    check_arr(arr);
                    break;
                case 4:
                    check_stlist(stack);
                    break;
                case 5:
                    print_efficiency_table();
                    break;
                case 6:
                    printf("Введите символ:\n");
                    //collect_buffer_garbage();
                    if (scanf("%c", &symb) != 1)
                    {
                        collect_buffer_garbage();
                        printf("Ошибка при вводе\n");
                        break;
                    }
                    collect_buffer_garbage();
                    if (arr_push(&arr, symb) == STACK_OVER_ERROR)
                        printf("Стэк уже заполнен\n");
                    else
                        printf("элемент %c успешно добавлен\n", symb);
                    break;
                case 7:
                    if (!arr_peek(&arr))
                        printf("Стэк пуст\n");
                    else
                        printf("%c\n", arr_peek(&arr));
                    break;
                case 8:

                    if (!arr_peek(&arr))
                        printf("стэк пуст\n");
                    else
                        printf("%c\n", arr_pop(&arr));
                    break;
                case 9:
                    printf("Введите символ:\n");
                    if (scanf("%c", &symb) != 1)
                    {
                        collect_buffer_garbage();
                        printf("Ошибка при вводе\n");
                        break;
                    }
                    collect_buffer_garbage();
                    if (stlist_push(&stack, symb) == STACK_OVER_ERROR)
                        printf("Стэк уже заполнен\n");
                    else
                        printf("элемент %c успешно добавлен\n", symb);
                    break;
                case 10:
                    if (!st_list_peek(&stack))
                        printf("Стэк пуст\n");
                    else
                        printf("%c\n", st_list_peek(&stack));
                    break;
                case 11:
                    if (!st_list_peek(&stack))
                        printf("стэк пуст\n");
                    else
                        printf("%c]\n", stlist_pop(&stack));
                    break;
            }
        }
    }

}