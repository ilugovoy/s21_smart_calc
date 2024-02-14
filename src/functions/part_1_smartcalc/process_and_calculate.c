/*!
 * @file process_and_calculate.c
 * @brief Функции обработки результатов парсера и вычисления результата
 *
 * Этот файл содержит реализацию функции для получения внешних данных,
 * последовательного вызова функций, их обработки и возвращения результата
 */

#include "../headers/part_1.h"

/**
 * @brief Обрабатывает и вычисляет значение выражения в заданной точке.
 *
 * Эта функция обрабатывает входную строку для преобразования в польскую
 * нотацию, после чего вычисляет значение выражения в указанной точке. В случае
 * успешной обработки и вычисления, результат сохраняется в переменной, на
 * которую указывает calculated_value.
 *
 * @param[in] input_str Входная строка, представляющая математическое выражение.
 * @param[in] input_value Значение, в котором требуется вычислить выражение.
 * @param[out] calculated_value Указатель, по которому сохраняется результат
 * вычисления.
 * @return int Значение, показывающее успешность обработки и вычисления:
 *              - OK(0): успешно,
 *              - PARSE_ERROR(1): ошибка парсинга,
 *              - CALCULATION_ERROR(2): ошибка вычисления
 *
 * @note Функции, используемые в процессе обработки и вычисления:
 *  - parser(): преобразует входную строку в польскую нотацию для последующего
 * вычисления
 *  - calculate(): выполняет вычисление выражения, используя значение переменной
 * input_value
 *
 * @note Ошибки отслеживаются и кодируются следующим образом:
 *  - INCORRECT_VALUE: значение, выходящее за пределы допустимых значений
 *  - PARSE_ERROR: ошибка парсинга входной строки
 *  - CALCULATION_ERROR: ошибка при выполнении вычислений
 */
int process_and_calculate(const char* input_str, double input_value,
                          double* calculated_value) {
  char str[MAX_STR_LEN] = {'\0'};
  strncpy(str, input_str, MAX_STR_LEN - 1);

  char arr[MAX_STR_LEN] = {'\0'};

  int return_value = OK;
  if (parser(str, arr) != 0) {
    return_value = PARSE_ERROR;
  }

  if (return_value != PARSE_ERROR) {
    *calculated_value = calculate(arr, input_value);
  }

  if (*calculated_value == INCORRECT_VALUE) {
    return_value = CALCULATION_ERROR;
  }

  return return_value;
}
