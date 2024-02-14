/**
 * @file test.c
 * @brief Тестирование математических выражений
 *
 * Этот набор тестов проверяет корректность работы функции
 * process_and_calculate, которая обрабатывает и вычисляет значение
 * математического выражения в заданной точке. Тесты проверяют различные
 * математические выражения и сравнивают полученные результаты с ожидаемыми
 * значениями.
 *
 * Если значение x в тестах не используется, то его значение должно быть 0:
 * ck_assert_int_eq(process_and_calculate(sin(30), 0, &res), OK);
 *
 * @note Для каждого теста проверяется как обработка и вычисление выражения, так
 * и корректность полученных результатов.
 */

#include "test.h"

int main(void) {
  size_t tests_failed = 0;

  Suite *stack_test = stack_test_suite();
  Suite *math_functions_test = expression_calculation_test_suite();
  Suite *credit_test = credit_calculation_test_suite();
  Suite *deposit_test = deposit_calculation_test_suite();

  SRunner *sr;

  sr = srunner_create(stack_test);
  srunner_add_suite(sr, math_functions_test);
  srunner_add_suite(sr, credit_test);
  srunner_add_suite(sr, deposit_test);

  srunner_run_all(sr, CK_VERBOSE);
  tests_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (tests_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
