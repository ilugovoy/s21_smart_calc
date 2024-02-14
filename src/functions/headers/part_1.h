/*!
 * @file part_1.h
 * @brief Хэдэр для основных функций калькулятора.
 *
 * Содержит функции для парсинга математических выражений, обработки операций и
 * функций, а также вычисления значений. Предоставляет возможность обработки
 * математических выражений, включая тригонометрические функции, операции и
 * переменные.
 */

#ifndef CALC_H
#define CALC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "credit.h"
#include "deposit.h"
#include "stack.h"

#define INCORRECT_VALUE \
  (0.0000000001)  ///< невозможное значение для проверки ошибки

/// возвращаемые значения
enum {
  OK,                 ///< всё вери гуд
  PARSE_ERROR,        ///< ошибка парсинга
  CALCULATION_ERROR,  ///< ошибка вычисления
  CREDIT_TYPE_ERROR   ///< неверный тип кредита
};

/// основные функции
int parser(char* string, char* arr);  // для парсинга входной строки
double calculate(char* string, double x);  // для вычисления результата
int process_and_calculate(
    const char* input_str, double input_value,
    double* calculated_value);  // для вычисления выражения

/// вспомогательные функции: parser
bool is_num(char num);  ///< функция проверки является ли символ числом
void delete_brackets(char* str, size_t i);  ///< удаление скобок
void assign_sin_cos_tan_log(char* string,
                            size_t i);  ///< кодировка для sin, cos, tan, log
void assign_asin_acos_atan(char* string,
                           size_t i);  ///< кодировка для asin, acos, atan, log
void assign_sqrt_ctg_ln(char* string,
                        size_t i);  ///< кодировка для sqrt, ctg, atan, log
void process_unary_syms(char* string,
                        size_t i);  ///< обработка одиночных символов
bool is_trigonometric_function(
    const char* string,
    size_t i);  ///< проверяет, является ли подстрока, функцией
bool is_operator(const char* string,
                 size_t i);  ///< проверяет, является ли подстрока, начиная с
                             ///< заданного индекса, оператором
void extract_from_stack(
    Stack* stack, char* arr, int* next_available_index,
    int* return_value);  ///< извлекает элементы из стека до открывающей скобки
                         ///< и помещает их в arr
void process_operators(Stack* stack, char* string, char* arr,
                       int* next_available_index, int* return_value,
                       size_t i);  ///< обрабатывает приоритеты операций в стеке
void process_numbers(char* string, char* arr, int* next_available_index,
                     size_t i);  ///< отвечает за обработку чисел во входной
                                 ///< строке и их разделение символом "|"
void process_input_string(
    char* string, Stack* stack, char* arr,
    int* return_value);  ///< обработка входной строки и заполнение стека.
void process_and_convert_math_operations(
    char* string, int* return_value);  ///< преобразование записи операторов и
                                       ///< функций в односимвольный вид
void extract_and_store_from_stack(
    Stack* stack, char* arr,
    int* next_available_index);  ///< извлекает элементы из стека и сохраняет их
                                 ///< в массиве до тех пор, пока стек не пустой

/// вспомогательные функции: calculate
void analyze_and_convert_numbers(
    const char* string, int* j, int* k, int* m,
    int* flag);  ///< осуществляет подсчет количества цифр и десятичных знаков
void process_and_push_number(
    const char* string, int* i, int* error_code,
    num_Stack* stack);  ///< преобразовывает числовые значения для записи в стек
void execute_arithmetic_operation(
    char* string, num_Stack* stack, double* input_1, double* input_2,
    const int* i, int* error_code);  ///< выполняет операцию и обновляет стек
bool is_math_function(const char* string,
                      int i);  ///< проверяет аргумент на математическую функцию
void process_exponent(const char* string, int* i, bool* flag_iskluchenie,
                      double* tmp);  ///< обрабатывает экспоненту
void process_math_function(
    char* string, int i, num_Stack* stack, double* input_1,
    int* error_code);  ///< обрабатывает математическую функцию

#endif
