/*!
 * @file stack.h
 * @brief Содержит объявления функций и структур для работы со стеками
 *
 *  Структуры для хранения данных и управления стеками операторов и чисел.
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define STACK_MAX_SIZE 256  ///< максимальный размер стека
#define MAX_STR_LEN 256  ///< максимальная длина строки

///< структура стека функций и операторов
typedef struct Stack {
  int size;
  char data[STACK_MAX_SIZE];
} Stack;

///< структура стека чисел
typedef struct num_Stack {
  int size;
  double data[STACK_MAX_SIZE];
} num_Stack;

// вспомогательные функции: стек
char pop(Stack* stack);  // для вытаскивания операторов из стека
int calculate_priority(const char* ch);  // для определения приоритета в стеке
double num_pop(num_Stack* stack);  // для вытаскивания чисел из стека
int push(Stack* stack, const char* symbol);  // для заполнения стека операторов
int num_push(num_Stack* stack, double num);  // для заполнения стека чисел
void destroy_num_stack(num_Stack* stack);
void destroy_stack(Stack* stack);

#endif
