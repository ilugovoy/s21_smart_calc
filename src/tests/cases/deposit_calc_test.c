/**
 * @file deposit_calc_test.c
 * @brief Тестирование кредитного калькулятора
 *
 * @note Для каждого теста проверяется как обработка и вычисление выражения, так
 * и корректность полученных результатов.
 */

#include "../test.h"

// deposit_calc->deposit_sum = 0;       		///< сумма вклада
// deposit_calc->deposit_months = 0;       		///< срок размещения в
// месяцах
// deposit_calc->deposit_interest_rate = 0;		///< годовая процентная
// ставка deposit_calc->tax_rate = 0;					///<
// налоговая ставка

// deposit_calc->accrued_interest = 0;       	///< начисленные проценты
// deposit_calc->tax_amount = 0;       			///< сумма налога
// deposit_calc->final_deposit_sum = 0;       	///< сумма на вкладе к концу
// срока

START_TEST(deposit_calc_multy_test) {
  DepositParameters deposit_calc;
  init_or_clear_deposit_parameters(&deposit_calc);

  deposit_calc.deposit_sum = 1000000.0;
  deposit_calc.deposit_months = 12;
  deposit_calc.deposit_interest_rate = 10.0;
  deposit_calc.tax_rate = 5.0;

  calculate_deposit(&deposit_calc);
  ck_assert_double_eq_tol(deposit_calc.accrued_interest, 100000, 1e-01);
  ck_assert_double_eq_tol(deposit_calc.tax_amount, 5000, 1e-01);
  ck_assert_double_eq_tol(deposit_calc.final_deposit_sum, 1095000, 1e-01);
}
END_TEST

Suite *deposit_calculation_test_suite(void) {
  Suite *suite = suite_create("deposit_calc_test");
  TCase *test_case = tcase_create("deposit_calc_test");

  if (suite != NULL && test_case != NULL) {
    tcase_add_test(test_case, deposit_calc_multy_test);

    suite_add_tcase(suite, test_case);
  }

  return suite;
}
