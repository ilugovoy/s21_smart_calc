/**
 * @file expression_test.c
 * @brief Тестирование математических выражений
 *
 * Этот набор тестов проверяет корректность работы функции
 * process_and_calculate, которая обрабатывает и вычисляет значение
 * математического выражения в заданной точке. Тесты проверяют различные
 * математические выражения и сравнивают полученные результаты с ожидаемыми
 * значениями.
 *
 * Если значение x в тестах не используется, то пишем 0:
 * ck_assert_int_eq(process_and_calculate(sin(30), 0, &res), OK);
 * @note Для каждого теста проверяется как обработка и вычисление выражения, так
 * и корректность полученных результатов.
 */

#include "../test.h"

/**
 * @note
 *
 * "1+x" - это входная строка, представляющая математическое выражение.
 * 1 - это значение будет подставлено вместо переменной "x" в выражении "1+x".
 * &res - это указатель, по которому сохраняется результат вычисления, т.е.
 * переменная calculated_value. OK - это ожидаемый результат, который
 * соответствует успешному выполнению.
 */
START_TEST(calc_multy_test) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("1+x", 1, &res), OK);
  ck_assert_double_eq(res, 1.0 + 1.0);
  ck_assert_int_eq(process_and_calculate("1+1 - 12 * (5^3) ", 0, &res), OK);
  ck_assert_double_eq(res, -1498.0);
  ck_assert_int_eq(process_and_calculate("1.1 + 1.1", 0, &res), OK);
  ck_assert_double_eq(res, 1.1 + 1.1);
  ck_assert_int_eq(process_and_calculate("-1.1 + 1.1", 0, &res), OK);
  ck_assert_double_eq(res, -1.1 + 1.1);
  ck_assert_int_eq(process_and_calculate("6 / 3", 0, &res), OK);
  ck_assert_double_eq(res, 2);
  ck_assert_int_eq(process_and_calculate("5.7 % 3.0", 0, &res), OK);
  ck_assert_double_eq(res, 2.7);
  ck_assert_int_eq(process_and_calculate("5.7 % 3.0 | 2.3 + 6.9", 0, &res), OK);
  ck_assert_int_eq(process_and_calculate("2 + 3 * 3", 0, &res), OK);
  ck_assert_double_eq(res, 11);
  ck_assert_int_eq(process_and_calculate("(2 + 3) * 3", 0, &res), OK);
  ck_assert_double_eq(res, 15);
}
END_TEST

// значения в радианах!
START_TEST(calc_test_sin) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("sin(30)", 0, &res), OK);
  ck_assert_double_eq_tol(res, -0.988032, 1e-05);
}
END_TEST

START_TEST(calc_test_cos) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("cos(60)", 0, &res), OK);
  ck_assert_double_eq_tol(res, -0.952413, 1e-05);
}
END_TEST

START_TEST(calc_test_tan) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("tan(10)", 0, &res), OK);
  ck_assert_double_eq_tol(res, 0.648361, 1e-05);
}
END_TEST

START_TEST(calc_test_sqrt) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("sqrt(9)", 0, &res), OK);
  ck_assert_double_eq(res, 3);
}
END_TEST

START_TEST(calc_test_log) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("log(60)", 0, &res), OK);
  ck_assert_double_eq_tol(res, 1.77815, 1e-05);
}
END_TEST

START_TEST(calc_test_ln) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("ln(10)", 0, &res), OK);
  ck_assert_double_eq_tol(res, 2.30259, 1e-05);
}
END_TEST

START_TEST(calc_test_acos) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("acos(0.5)", 0, &res), OK);
  ck_assert_double_eq_tol(res, 1.0472, 1e-05);
}
END_TEST

START_TEST(calc_test_asin) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("asin(1)", 0, &res), OK);
  ck_assert_double_eq_tol(res, 1.5708, 1e-05);
}
END_TEST

START_TEST(calc_test_atan) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("atan(1)", 0, &res), OK);
  ck_assert_double_eq_tol(res, 0.785398, 1e-05);
}
END_TEST

START_TEST(calc_test_exp) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("1.23e-4+1", 0, &res), OK);
  ck_assert_int_eq(process_and_calculate("1.23E+4 + 1", 0, &res), OK);
  ck_assert_int_eq(process_and_calculate("1.23e+4+ 1", 0, &res), OK);
  ck_assert_int_eq(process_and_calculate("1.23E-4 +1", 0, &res), OK);
  ck_assert_int_eq(process_and_calculate("1.23e4 + 1", 0, &res), OK);
  ck_assert_double_eq(res, 1 + 0.000123);
  ck_assert_int_eq(process_and_calculate("1.23E4 + 1", 0, &res), OK);
  ck_assert_double_eq(res, 1 + 12300);
}
END_TEST

START_TEST(calc_test_parse_error) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("sin(23_10)", 0, &res), PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate("1+1)", 0, &res), PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate("1+1)", 0, &res), PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate(")1+1 - 12 * (5^3) ", 0, &res),
                   PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate(")1+2(", 0, &res), PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate("+)", 0, &res), PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate("1+1)(1+1", 0, &res), PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate(")2", 0, &res), PARSE_ERROR);
  ck_assert_int_eq(process_and_calculate("(12))+(12", 0, &res), PARSE_ERROR);
}
END_TEST

START_TEST(calc_test_calculation_error) {
  double res = 0;
  ck_assert_int_eq(process_and_calculate("()", 0, &res), CALCULATION_ERROR);
}
END_TEST

START_TEST(test_num_push_with_error) {
  num_Stack stack;
  stack.size = 256;
  int error_code = 0, i = 0;

  process_and_push_number("123|", &i, &error_code, &stack);
  ck_assert_int_eq(error_code, CALCULATION_ERROR);
}
END_TEST

Suite *expression_calculation_test_suite(void) {
  Suite *suite = suite_create("calc_test");
  TCase *test_case = tcase_create("calc_test");

  if (suite != NULL && test_case != NULL) {
    tcase_add_test(test_case, calc_multy_test);

    tcase_add_test(test_case, calc_test_sin);
    tcase_add_test(test_case, calc_test_cos);
    tcase_add_test(test_case, calc_test_tan);
    tcase_add_test(test_case, calc_test_sqrt);
    tcase_add_test(test_case, calc_test_log);
    tcase_add_test(test_case, calc_test_ln);
    tcase_add_test(test_case, calc_test_acos);
    tcase_add_test(test_case, calc_test_asin);
    tcase_add_test(test_case, calc_test_atan);
    tcase_add_test(test_case, calc_test_exp);

    tcase_add_test(test_case, calc_test_parse_error);
    tcase_add_test(test_case, test_num_push_with_error);
    tcase_add_test(test_case, calc_test_calculation_error);

    suite_add_tcase(suite, test_case);
  }

  return suite;
}
