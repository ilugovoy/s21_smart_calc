/**
 * @file test.h
 * @brief Заголовочный файл модуля тестирования
 *
 */

#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "../functions/headers/part_1.h"

/**
 * Создает Suite для тестирования стека
 * @return указатель на Suite тестов для стека
 */
Suite *stack_test_suite(void);

/**
 * Создает Suite для тестирования вычисления математических выражений
 * @return указатель на Suite тестов для вычисления математических выражений
 */
Suite *expression_calculation_test_suite(void);

/**
 * Создает Suite для тестирования кредитного калькулятора
 * @return указатель на Suite
 */
Suite *credit_calculation_test_suite(void);

/**
 * Создает Suite для тестирования депозитного калькулятора
 * @return указатель на Suite
 */
Suite *deposit_calculation_test_suite(void);

#endif