/**
 * @file stack_test.c
 * @brief Тестирование функций стека
 *
 * Этот набор тестов проверяет корректность работы функций push, num_push и
 * num_pop из стека. Тесты проверяют различные математические выражения и
 * сравнивают полученные результаты с ожидаемыми значениями.
 *
 * @note Для каждого теста проверяется как обработка и вычисление выражения, так
 * и корректность полученных результатов.
 */

#include "../test.h"

// Тесты для проверки переполнения при добавлении элемента в стек
START_TEST(push_overflow_test) {
  Stack test_stack;  // создаем тестовый символьный стек
  test_stack.size =
      256;  // устанавливаем начальный размер стека в 256 для теста переполнения

  char operand = ')';
  int result =
      push(&test_stack, &operand);  // пытаемся добавить элемент в полный стек
  ck_assert_int_eq(result, 1);  // ожидаем возврат ошибки
}
END_TEST

START_TEST(num_push_overflow_test) {
  num_Stack test_stack;  // создаем тестовый числовой стек
  test_stack.size =
      256;  // устанавливаем начальный размер стека в 256 для теста переполнения

  double num = 21.21;
  int result =
      num_push(&test_stack, num);  // пытаемся добавить элемент в полный стек
  ck_assert_int_eq(result, 1);  // ожидаем возврат ошибки
}
END_TEST

// Извлечение из пустого стека
START_TEST(num_pop_empty_stack_test) {
  num_Stack test_stack;  // Создаем тестовый стек
  test_stack.size =
      0;  // Устанавливаем размер стека 0 для теста с пустым стеком

  // Извлекаем число из пустого стека
  double result = num_pop(&test_stack);
  ck_assert_double_eq(
      result,
      0.0000000001);  // Ожидаем, что будет возвращено значение 0.0000000001
}
END_TEST

Suite *stack_test_suite(void) {
  Suite *suite = suite_create("stack_test");
  TCase *test_case = tcase_create("stack_test");

  if (suite != NULL && test_case != NULL) {
    tcase_add_test(test_case, push_overflow_test);
    tcase_add_test(test_case, num_push_overflow_test);
    tcase_add_test(test_case, num_pop_empty_stack_test);

    suite_add_tcase(suite, test_case);
  }

  return suite;
}
