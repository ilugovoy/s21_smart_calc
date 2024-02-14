/*!
 * @file stack_core.c
 * @brief Содержит реализацию основных функций для работы со стеком
 *
 * Этот файл содержит реализацию основных функций для работы со стеком, таких
 * как добавление элемента в стек, извлечение элемента из стека, а также функции
 * для работы со стеком чисел.
 */

#include "../headers/part_1.h"

/*!
 * @brief Добавляет элемент в стек
 *
 * Данная функция добавляет элемент в стек и возвращает целочисленное значение,
 * обозначающее успешность операции.
 * @param stack Указатель на структуру стека
 * @param symbol Строка, представляющая добавляемый элемент
 * @return Целое число, обозначающее успешность операции (0 - успешно, 1 - стек
 * переполнен)
 */
int push(Stack* stack, const char* symbol) {
  int return_value = 0;
  if (stack->size >= STACK_MAX_SIZE) {
    return_value = 1;
  } else {
    stack->data[stack->size] = *symbol;
    stack->size++;
  }
  return return_value;
}

/*!
 * @brief Извлекает элемент из стека
 *
 * Данная функция извлекает элемент из стека и возвращает извлечённый элемент.
 * @param stack Указатель на структуру стека
 * @return Извлечённый элемент стека
 */
char pop(Stack* stack) {
  char tmp = 'R';  // заглушка для передачи ошибки в pop
  if (stack->size <= 0) {
  } else {
    stack->size--;
    tmp = stack->data[stack->size];
    stack->data[stack->size] = 0;
  }
  return tmp;
}

/*!
 * @brief Заполняет стек числами
 *
 * Данная функция добавляет число в стек чисел и возвращает целочисленное
 * значение, обозначающее успешность операции.
 * @param stack Указатель на структуру стека чисел
 * @param num Число, которое необходимо добавить в стек
 * @return Целое число, обозначающее успешность операции (0 - успешно, 1 - стек
 * переполнен)
 */
int num_push(num_Stack* stack, double num) {
  int return_value = 0;
  if (stack->size >= STACK_MAX_SIZE) {
    return_value = 1;
  } else {
    stack->data[stack->size] = num;
    stack->size++;
  }
  return return_value;
}

/*!
 * @brief Извлекает число из стека чисел
 *
 * Данная функция извлекает число из стека чисел и возвращает извлеченное число.
 * @param stack Указатель на структуру стека чисел
 * @return Извлеченное число из стека
 */
double num_pop(num_Stack* stack) {
  double tmp = 0;
  if (stack->size <= 0) {
    tmp = INCORRECT_VALUE;
  } else {
    stack->size--;
    tmp = stack->data[stack->size];
    stack->data[stack->size] = 0;
  }
  return tmp;
}

// Функция для уничтожения стека (очистка и освобождение памяти, выделенной под
// стек)
void destroy_num_stack(num_Stack* stack) {
  for (int i = 0; i < STACK_MAX_SIZE; i++) {
    stack->data[i] = 0;  // Устанавливаем все элементы массива в 0
  }
  stack->size = 0;
}

// Функция для уничтожения стека (очистка и освобождение памяти, выделенной под
// стек)
void destroy_stack(Stack* stack) {
  for (int i = 0; i < STACK_MAX_SIZE; i++) {
    stack->data[i] = '$';  // Устанавливаем все элементы массива в $
  }
  stack->size = 0;
}