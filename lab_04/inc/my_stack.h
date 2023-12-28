#ifndef MY_STACK_H
#define MY_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#define STACK_MAX_SIZE 50
#define MAX_SIZE 1000
#define LEN 100
#define TNAME_LEN 100
#define MAX_STRING 50


typedef enum
{
    NODE_ALLOC_ERROR = 1,
    LIST_IS_NULL,
    READ_ERROR,
    STRING_TOO_SMALL,
    STRING_READ_ERROR,
    STRING_TOO_BIG,
    STACK_OVER_ERROR,
    STACK_DELETE_ERROR
} errors_enum;

typedef struct {
    char **a;
    size_t count;
} my_arrd_t;

typedef struct {
    char data[STACK_MAX_SIZE];
    size_t count;
} stack_arr;

typedef struct node
{
    char value;
    struct node_t *next;
} node_t;

typedef struct {
    node_t *head;
    size_t count;
} stack_list_t;

typedef char string[MAX_STRING + 1];

int arr_push(stack_arr *stack, char value);
char arr_pop(stack_arr *stack);
char arr_peek(stack_arr *stack);
void print_stack_arr(stack_arr stack);
void clear_stack_arr(stack_arr *stack);
int get_line(string line, size_t *llen);
int check_palindrome_arr(string line, size_t llen, stack_arr *stack);
int initialize_stlist(stack_list_t **head, char value);
int check_stlist(stack_list_t *head);
char st_list_peek(stack_list_t **head);
char stlist_pop(stack_list_t **head);
int stlist_push(stack_list_t **head, char data);
int is_empty_stlist(stack_list_t **head);
int clear_stlist(stack_list_t *head);
int check_palindrome_stlist(string line, size_t llen, stack_list_t *head);
int read_command(char *tmp, int *command);
int check_int(char *tmp);
int read_line(char *tmp);
void collect_buffer_garbage();
int check_arr(stack_arr arr);
unsigned long long cur_ms_gettimeofday();
void choose_line(size_t i, string line);
void print_efficiency_table();
int measure_check_palindrome_stlist(string line, size_t llen, stack_list_t *head);
int measure_check_palindrome_arr(string line, size_t llen, stack_arr *stack);

#endif
