#include "my_stack.h"

my_arrd_t GLOB = { NULL, 0 };

void my_free(void *p)
{
    GLOB.count++;
    GLOB.a = realloc(GLOB.a, sizeof(char *) * GLOB.count);
    GLOB.a[GLOB.count - 1] = p;
    free(p);
}

int arr_push(stack_arr *stack, char value)
{
    if (stack->count >= STACK_MAX_SIZE)
        return STACK_OVER_ERROR;
    stack->data[stack->count] = value;
    stack->count++;
    return 0;
}

char arr_pop(stack_arr *stack)
{
    if (stack->count == 0) {
        return 0;
    }
    stack->count--;
    return stack->data[stack->count];
}

char arr_peek(stack_arr *stack)
{
    if (stack->count == 0) {
        return 0;
    }
    return stack->data[stack->count - 1];
}

void print_stack_arr(stack_arr stack)
{
    for (size_t i = 0; i < stack.count; i++)
    {
        printf("%c\t", stack.data[i]);
    }
    printf("\n");
}

void clear_stack_arr(stack_arr *stack)
{
    stack->count = 0;
}

int is_empty(stack_arr *stack)
{
    if (stack->count == 0)
        return 1;
    return 0;
}

// списанная не работающая
int get_line(string line, size_t *llen)
{
    char tmp_s[MAX_STRING + 1];
    if (fgets(tmp_s, MAX_STRING + 1, stdin) == NULL)
        return STRING_READ_ERROR;
    tmp_s[strcspn(tmp_s, "\n")] = '\0';
    if (strlen(tmp_s) >= MAX_STRING)
        return STRING_TOO_BIG;
    if (!strlen(tmp_s))
        return STRING_TOO_SMALL;
    strncpy(line, tmp_s, MAX_STRING + 1);
    *llen = strlen(line);
    return 0;
}

int check_arr(stack_arr arr)
{
    if (arr.count == 0)
        printf("стэк пустой\n");
    else {
        for (size_t i = 0; i < arr.count; i++) {
            printf("элемент %d, value='%c'\n", i + 1, arr.data[i]);
        }
    }
    return 0;
}

int check_palindrome_arr(string line, size_t llen, stack_arr *stack)
{
    clear_stack_arr(stack);

    size_t Flag = 0;
    if (llen % 2 == 1)
        Flag = 1;
    size_t tmp = llen / 2;

    for (size_t i = 0; i < tmp; i++)
    {
        if (arr_push(stack, line[i]) == STACK_OVER_ERROR) {
            printf("Стэк достиг максимального размера - 50\n");
            return STACK_OVER_ERROR;
        }
    }
    for (size_t i = tmp + Flag; i < llen; i++)
    {
        if (line[i] == arr_peek(stack)) {
            if (!arr_pop(stack)) {
                printf("Стэк пуст\n");
                return STACK_DELETE_ERROR;
            }
        }
        else {
            printf("не палиндром\n");
            return 0;
        }
    }
    printf("палндром\n");
    return 1;
}

int stlist_push(stack_list_t **head, char data)
{
    node_t *tmp = (node_t*) malloc(sizeof(node_t));
    if (!tmp)
        return NODE_ALLOC_ERROR;
    tmp->value = data;
    if ((*head)->count == 0)
    {
        tmp->next = NULL;
        (*head)->head = (node_t *) tmp;
    }
    else
    {
        tmp->next = (struct node_t *) (*head)->head;
        (*head)->head = tmp;
    }
    (*head)->count++;
    return 0;
}

char stlist_pop(stack_list_t **head)
{
    if ((*head)->count == 0)
        return LIST_IS_NULL;
    char value = (*head)->head->value;
    node_t * del = (*head)->head;
    (*head)->head = (node_t *) (*head)->head->next;
    (*head)->count--;
    my_free(del);
    return value;
}

char st_list_peek(stack_list_t **head)
{
    if ((*head)->count == 0)
        return LIST_IS_NULL;
    char value = (*head)->head->value;
    return value;
}

int check_stlist(stack_list_t *head)
{
    if ((head)->count == 0)
        printf("стэк пустой\n");
    else {
        size_t i = 0;
        node_t *tmp = (head)->head;
        while (tmp != NULL) {
            printf("элемент %d, value='%c', addr=%p\n", i + 1, tmp->value, tmp);
            i++;
            tmp = (node_t *) tmp->next;
        }
    }
    printf("Удаленные адреса\n");
    for (size_t i = 0; i < GLOB.count; i++)
        printf("%d %p\n", i, GLOB.a[i]);
    return 0;
}

int initialize_stlist(stack_list_t **head, char value)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    if (!node)
        return NODE_ALLOC_ERROR;
    node->value = value;
    node->next = NULL;
    (*head)->head = node;
    return 0;
}

int is_empty_stlist(stack_list_t **head)
{
    if ((*head)->count == 0)
        return 1;
    return 0;
}

int clear_stlist(stack_list_t *stack)
{
    if ((stack)->count == 0)
        return LIST_IS_NULL;
    node_t *tmp = (stack)->head;
    node_t *cur;
    while (tmp != NULL)
    {
        cur = tmp;
        tmp = (node_t *) tmp->next;
        my_free(cur);
    }
    (stack)->head = NULL;
    (stack)->count = 0;
    return 0;
}

int check_palindrome_stlist(string line, size_t llen, stack_list_t *head)
{

    clear_stlist(head);

    size_t Flag = 0;
    if (llen % 2 == 1)
        Flag = 1;
    size_t tmp = llen / 2;

    for (size_t i = 0; i < tmp; i++)
    {

        stlist_push(&head, line[i]);
    }
    for (size_t i = tmp + Flag; i < llen; i++)
    {
        if (line[i] == st_list_peek(&head))
            stlist_pop(&head);
        else {
            printf("не палиндром\n");
            return 0;
        }
    }
    printf("палндром\n");
    return 1;
}

int read_line(char *tmp)
{
    char tmp_s[MAX_STRING + 1];
    if (fgets(tmp_s, MAX_STRING + 1, stdin) == NULL)
        return STRING_READ_ERROR;
    tmp_s[strcspn(tmp_s, "\n")] = '\0';
    if (strlen(tmp_s) >= MAX_STRING)
        return STRING_TOO_BIG;
    if (!strlen(tmp_s))
        return STRING_TOO_SMALL;
    strncpy(tmp, tmp_s, MAX_STRING);
    return 0;
}

int check_int(char *tmp)
{
    int i = 0;
    while (tmp[i] != '\0')
    {
        if (!isdigit(tmp[i]))
            return 1;
        i++;
    }
    return 0;
}

int read_command(char *tmp, int *command) {
    if (read_line(tmp))
        return READ_ERROR;
    if (check_int(tmp))
        return READ_ERROR;
    if (sscanf(tmp, "%d", command) != 1)
        return READ_ERROR;
    if (*command < 0 || *command > 12)
        return READ_ERROR;
    return 0;
}

void collect_buffer_garbage()
{
    char tmp_string[2];
    fgets(tmp_string, 2, stdin);
}

unsigned long long cur_ms_gettimeofday()
{
    struct timeval timeval;
    gettimeofday(&timeval, NULL);

    return (timeval.tv_sec * 1000000 + timeval.tv_usec);
}

void choose_line(size_t i, string line)
{
    switch (i)
    {
        case 40:
            strncpy(line, "bcdefghijklmnopqrstuutsrqponmlkjihgfedcb", MAX_STRING + 1);

            break;
        case 30:
            strncpy(line, "ghijklmnopqrstuutsrqponmlkjihg", MAX_STRING + 1);
            break;
        case 20:
            strncpy(line, "lmnopqrstuutsrqponml", MAX_STRING + 1);

            break;
        case 10:
            strncpy(line, "qrstuutsrq", MAX_STRING + 1);

            break;

    }
}

int measure_check_palindrome_stlist(string line, size_t llen, stack_list_t *head)
{

    clear_stlist(head);

    size_t Flag = 0;
    if (llen % 2 == 1)
        Flag = 1;
    size_t tmp = llen / 2;

    for (size_t i = 0; i < tmp; i++)
    {

        stlist_push(&head, line[i]);
    }
    for (size_t i = tmp + Flag; i < llen; i++)
    {
        if (line[i] == st_list_peek(&head))
            stlist_pop(&head);
        else {
            //printf("не палиндром\n");
            return 0;
        }
    }
    //printf("палндром\n");
    return 1;
}

int measure_check_palindrome_arr(string line, size_t llen, stack_arr *stack)
{
    clear_stack_arr(stack);

    size_t Flag = 0;
    if (llen % 2 == 1)
        Flag = 1;
    size_t tmp = llen / 2;

    for (size_t i = 0; i < tmp; i++)
    {
        if (arr_push(stack, line[i]) == STACK_OVER_ERROR) {
            printf("Стэк достиг максимального размера - 50\n");
            return STACK_OVER_ERROR;
        }
    }
    for (size_t i = tmp + Flag; i < llen; i++)
    {
        if (line[i] == arr_peek(stack)) {
            if (!arr_pop(stack)) {
                //printf("Стэк пуст\n");
                return STACK_DELETE_ERROR;
            }
        }
        else {
            //printf("не палиндром\n");
            return 0;
        }
    }
    //printf("палндром\n");
    return 1;
}


void print_efficiency_table()
{
    stack_list_t *stack = malloc(sizeof(stack_list_t));
    (stack)->head = NULL;
    (stack)->count = 0;
    stack_arr arr;
    arr.count = 0;
    string line;
    size_t llen;
    unsigned long long t1 = 0, t2 = 0;
    printf("Таблица сравнения эффективности обработки стеков по времени(микросекунды):\n");
    printf("┌────┬──────────────────────────┬──────────────────────────────┐\n");
    printf("│#   │  Стек на основе массива  │      Стек на основе списка   │\n");
    for (size_t i = 10; i <= 40; i+=10)
    {
        t1 = 0;
        t2 = 0;
        choose_line(i, line);
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            tmp = cur_ms_gettimeofday();
            measure_check_palindrome_arr(line, i, &arr);
            tmp = cur_ms_gettimeofday() - tmp;
            t1 += tmp;
        }
        t1 /= 100;
        for (size_t j = 0; j < 100; j++)
        {
            unsigned long long tmp;
            tmp = cur_ms_gettimeofday();
            measure_check_palindrome_stlist(line, i, stack);
            tmp = cur_ms_gettimeofday() - tmp;
            t2 += tmp;
            free(GLOB.a);
            GLOB.a = NULL;
            GLOB.count = 0;
        }
        t2 /= 100;
        printf("│%4zu│%26llu│%30llu│\n", i, t1, t2);
    }
    printf("└────┴──────────────────────────┴──────────────────────────────┘\n");

    printf("Таблица сравнения эффективности обработки стеков по памяти(байты):\n");
    printf("┌────┬──────────────────────────┬──────────────────────────────┐\n");
    printf("│#   │  Стек на основе массива  │      Стек на основе списка   │\n");
    for (size_t i = 10; i <= 40; i+=10)
    {
        t1 = sizeof(size_t) + i * sizeof(char);
        t2 = sizeof(size_t) + i * (sizeof(node_t *) + sizeof(char));
        printf("│%4zu│%26llu│%30llu│\n", i, t1, t2);
    }
    printf("└────┴──────────────────────────┴──────────────────────────────┘\n");
}