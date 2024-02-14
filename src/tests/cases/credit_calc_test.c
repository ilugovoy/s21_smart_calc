/**
 * @file credit_calc_test.c
 * @brief Тестирование кредитного калькулятора
 *
 * @note Для каждого теста проверяется как обработка и вычисление выражения, так
 * и корректность полученных результатов.
 */

#include "../test.h"

START_TEST(credit_calc_multy_test) {
  CreditParameters credit_calc;
  init_or_clear_credit_parameters(&credit_calc);
  credit_calc.credit_sum = 1000000.0;
  credit_calc.interest_rate = 10.0;
  credit_calc.months = 12;

  // Тестирование аннуитетного кредита
  credit_calc.type = 1;
  calculate_payments(&credit_calc);
  ck_assert_double_eq_tol(credit_calc.monthly_payment, 87915.9, 1e-01);
  ck_assert_double_eq_tol(credit_calc.total_payment, 1054990.65, 1e-01);
  ck_assert_double_eq_tol(credit_calc.overpayment, 54990.65, 1e-01);

  // Тестирование дифференцированного кредита
  credit_calc.type = 2;
  calculate_payments(&credit_calc);
  ck_assert_double_eq_tol(credit_calc.monthly_payment, 91666.67, 1e-01);
}
END_TEST

Suite *credit_calculation_test_suite(void) {
  Suite *suite = suite_create("credit_calc_test");
  TCase *test_case = tcase_create("credit_calc_test");

  if (suite != NULL && test_case != NULL) {
    tcase_add_test(test_case, credit_calc_multy_test);

    suite_add_tcase(suite, test_case);
  }

  return suite;
}
