/*!
 * @file common.c
 * @brief Вспомогательные функции, использующиеся в разных файлах
 *
 */

#include "../headers/part_1.h"

/**
 * @brief Проверяет, является ли символ числовым.
 *
 * @param[in] num Проверяемый символ.
 * @return true, если символ является числовым или десятичной точкой, в
 * противном случае false.
 */
bool is_num(char num) {
  bool return_value = false;
  if ((num >= '0' && num <= '9') || num == '.') {
    return_value = true;
  }
  return return_value;
}

/**
 * @brief Проверяет, является ли подстрока, начиная с указанного индекса, одной
 * из тригонометрических функций.
 *
 * Эта функция проверяет, является ли подстрока, начиная с указанного индекса,
 * одной из тригонометрических функций (например, sin, cos, tan, и т.д.).
 *
 * @param[in] string Входная строка, в которой производится проверка.
 * @param[in] i Начальный индекс для проверки подстроки.
 * @return true, если символ является началом одной из тригонометрических
 * функций, в противном случае false.
 */
bool is_trigonometric_function(const char* string, size_t i) {
  return string[i] == 's' || string[i] == 'c' || string[i] == 'q' ||
         string[i] == 'i' || string[i] == 'o' || string[i] == 'n' ||
         string[i] == 't' || string[i] == 'g' || string[i] == 'l' ||
         string[i] == 'z';
}
