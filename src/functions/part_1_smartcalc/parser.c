/*!
 * @file parser.c
 * @brief Функции для парсинга и преобразования данных в польскую нотацию
 *
 * Этот файл содержит реализацию функций для обработки входной строки и
 * преобразования ее в польскую нотацию.
 */

#include "../headers/part_1.h"

/**
 * @brief Преобразует входную строку в польскую нотацию.
 *
 * Обрабатывает входную строку, заменяет математические функции и операторы на
 * их односимвольные представления, отслеживает количество открытых и закрытых
 * скобок и устанавливает успешность обработки. Затем проходит по входной строке
 * и выполняет операции в зависимости от типа символа (тригонометрическая
 * функция, скобка, оператор, пробел или число), включая обработку стека.
 *
 * @param[in] string Входная строка, которая будет обработана.
 * @param[out] arr Массив, в котором хранятся преобразованные данные в польской
 * нотации.
 * @return OK(0) - успешно, PARSE_ERROR(1) - ошибка.
 *
 * Функция включает в себя следующие вспомогательные функции:
 * - process_and_convert_math_operations: Обрабатывает входную строку, заменяет
 * математические функции и операторы на их односимвольные представления и
 * отслеживает количество открытых и закрытых скобок для определения успешности
 * обработки.
 * - process_input_string: Обрабатывает входную строку и заполняет стек и массив
 * обработанными данными в зависимости от типа символа в строке.
 * - is_trigonometric_function: Проверяет, является ли текущая подстрока,
 * начиная с указанного индекса, тригонометрической функцией.
 * - extract_from_stack: Извлекает элементы из стека до появления открывающей
 * скобки и помещает их в массив.
 * - process_operators: Обрабатывает операции и их приоритеты в стеке на основе
 * текущего символа и предоставленной строки.
 * - process_numbers: Обрабатывает числа во входной строке и разделяет их
 * символом '|' в массиве.
 * - и pop: Операции со стеком для помещения элементов в стек и извлечения
 * элементов из стека.
 * - is_operator: Проверяет, является ли символ оператором.
 * - extract_and_store_from_stack: Извлекает элементы из стека и сохраняет их в
 * массиве до тех пор, пока стек не опустеет.
 */
int parser(char* string, char* arr) {
  Stack stack;
  stack.size = 0;
  int return_value = OK;

  process_and_convert_math_operations(string, &return_value);
  process_input_string(string, &stack, arr, &return_value);

  destroy_stack(&stack);
  return return_value;
}

/**
 * @brief Преобразование записи математических операторов и функций в строке в
 * односимвольный вид и обработка скобок.
 *
 * Функция проходит по входной строке, заменяет математические функции и
 * операторы на их односимвольные представления, отслеживает количество открытых
 * и закрытых скобок, и определяет успешность обработки.
 *
 * @param[in,out] string Входная строка, подлежащая обработке.
 * @param[out] return_value Указатель на переменную, в которую будет записан код
 * ошибки (если возникнет). Возвращаемые значения:
 *  - OK - успешное выполнение
 *  - PARSE_ERROR - ошибка при разборе математического выражения
 *
 * @note Функции, используемые в процессе обработки:
 *  - assign_sin_cos_tan_log(): заменяет обозначения sin, cos, tan, log на
 * односимвольные представления s, c, t, l
 *  - assign_asin_acos_atan(): заменяет обозначения asin, acos, atan на
 * односимвольные представления s, c, t
 *  - assign_sqrt_ctg_ln(): заменяет обозначения sqrt, ctg, ln на односимвольные
 * представления q, g, n
 *  - process_unary_syms(): кодирует унарный минус в ~ и удаляет унарный плюс
 * как незначимый
 */
void process_and_convert_math_operations(char* string, int* return_value) {
  int b_count = 0;
  for (size_t i = 0; i < strlen(string) - 1; i++) {
    if (string[i] == '(')
      b_count++;
    else if (string[i] == ')')
      b_count--;
    assign_sin_cos_tan_log(string, i);  ///< для sin->s, cos->c, tan->t, log->l
    assign_asin_acos_atan(string, i);  ///< для asin->s, acos->c, atan->t
    assign_sqrt_ctg_ln(string, i);     ///< для sqrt->q, ctg->g, ln->n
    process_unary_syms(string, i);  ///< кодировка унарного минуса в ~ и
                                    ///< удаление унарного плюса как незначимого
    if (string[i] == '_' || b_count > 1 || b_count < 0)
      *return_value = PARSE_ERROR;  ///< возврат ошибки
  }
}

/**
 * @brief Обработка входной строки и заполнение стека.
 *
 * Функция проходит по входной строке и выполняет операции в зависимости от типа
 * сивола (тригонометрическая функция, скобка, оператор, пробел или число),
 * включая обработка стека.
 *
 * @param[in] string Входная строка, подлежающая обработке.
 * @param[in,out] stack Стек, используемый для обработки данных.
 * @param[in,out] arr Массив для хранения обработанных данных.
 * @param[in,out] next_available_index Индекс для следующего доступного элемента
 * массива.
 * @param[out] return_value Указатель на переменную, в которую будет записан код
 * ошибки (если возникнет). Возвращаемые:
 *  - 0 - успешное выполнение
 *  - 1 - ошибка при обработке входной строки
 *
 * @note Функции, используемые в процессе обработки:
 *  - is_trigonometric_function(): проверяет, является ли символ
 * тригонометрической функцией
 *  - push(): помещает элемент в стек
 *  - extract_from_stack(): извлекает элемент из стека и записывает его в массив
 *  - pop(): извлекает верхний элемент стека
 *  - is_operator(): проверяет, является ли символ оператором
 *  - process_operators(): обрабатывает операторы и обновляет массив и стек
 *  - process_numbers(): обрабатывает числа и записывает их в массив
 *  - extract_and_store_from_stack(): извлекает все элементы из стека и
 * записывает в массив
 */
void process_input_string(char* string, Stack* stack, char* arr,
                          int* return_value) {
  int next_available_index = 0;
  for (size_t i = 0; i < strlen(string); i++) {
    if (is_trigonometric_function(string, i) || string[i] == '(') {
      if (push(stack, &string[i]) != 0) *return_value = PARSE_ERROR;
    } else if (string[i] == ')') {
      extract_from_stack(stack, arr, &next_available_index, return_value);
      if (pop(stack) == 'R') *return_value = PARSE_ERROR;
    } else if (is_operator(string, i)) {
      if (stack->size > 0)
        process_operators(stack, string, arr, &next_available_index,
                          return_value, i);
      if (push(stack, &string[i]) != 0) *return_value = PARSE_ERROR;
    } else if (string[i] == ' ') {
      continue;
    } else {
      process_numbers(string, arr, &next_available_index, i);
    }
    if (*return_value == PARSE_ERROR) break;
  }
  extract_and_store_from_stack(stack, arr, &next_available_index);
}

/**
 * @brief Проверяет, является ли подстрока, начиная с заданного индекса,
 * оператором.
 *
 * @param[in] string Входная строка, в которой проверяется наличие оператора.
 * @param[in] i Текущий индекс во входной строке.
 * @return true, если символ является оператором, в противном случае false.
 */
bool is_operator(const char* string, size_t i) {
  return (string[i] == '+' || string[i] == '-' || string[i] == '/' ||
          string[i] == '*' || string[i] == '^' || string[i] == '%' ||
          string[i] == '~');
}

/**
 * @brief Извлекает элементы из стека до появления открывающей скобки и помещает
 * их в массив.
 *
 * @param[in] stack Указатель на стек, из которого извлекаются элементы.
 * @param[out] arr Массив, в который помещаются элементы.
 * @param[in,out] next_available_index Индекс следующей доступной позиции в
 * массиве.
 */
void extract_from_stack(Stack* stack, char* arr, int* next_available_index,
                        int* return_value) {
  int k = stack->size;
  while (stack->data[k - 1] != '(') {
    arr[*next_available_index] = pop(stack);
    if (arr[*next_available_index] ==
        'R') {  ///< записывается R в случае ошибки в pop
      *return_value = PARSE_ERROR;
      break;
    }
    (*next_available_index)++;
    k--;
  }
}

/**
 * @brief Отвечает за обработку операций и их приоритетов в стеке.
 *
 * @param[in,out] stack Указатель на стек, содержащий операторы.
 * @param[in] string Входная обрабатываемая строка.
 * @param[out] arr Массив, куда помещаются обработанные операторы.
 * @param[in,out] next_available_index Индекс следующей доступной позиции в
 * массиве.
 * @param[in,out] return_value Индикатор любой ошибки, возникшей во время
 * обработки.
 * @param[in] i Текущая позиция во входной строке.
 */
void process_operators(Stack* stack, char* string, char* arr,
                       int* next_available_index, int* return_value, size_t i) {
  while (stack->size > 0 && calculate_priority(&stack->data[stack->size - 1]) >=
                                calculate_priority(&string[i])) {
    if (stack->data[stack->size - 1] != '(') {
      arr[*next_available_index] = pop(stack);
      if (arr[*next_available_index] == 'R') *return_value = PARSE_ERROR;
      (*next_available_index)++;
    }
  }
}

/**
 * @brief Отвечает за обработку чисел во входной строке и их разделение символом
 * "|".
 *
 * @param[in] string Входная обрабатываемая строка.
 * @param[out] arr Массив, в который помещаются обработанные числа.
 * @param[in,out] next_available_index Индекс следующей доступной позиции в
 * массиве.
 * @param[in] i Текущая позиция во входной строке.
 */
void process_numbers(char* string, char* arr, int* next_available_index,
                     size_t i) {
  if (is_num(string[i + 1]) || string[i + 1] == '.') {
    arr[*next_available_index] = string[i];
    (*next_available_index)++;
  } else {
    arr[*next_available_index] = string[i];
    (*next_available_index)++;
    arr[*next_available_index] = '|';
    (*next_available_index)++;
  }
}

/**
 * @brief Извлекает элементы из стека и сохраняет их в массиве до тех пор, пока
 * стек не опустеет.
 *
 * Если при извлечении происходит ошибка, в массив записывается символ 'R'.
 *
 * @param[in,out] stack Стек, из которого извлекаются элементы.
 * @param[out] arr Массив, в который сохраняются извлеченные элементы.
 * @param[in,out] next_available_index Индекс в массиве, указывающий на
 * следующую доступную позицию.
 */
void extract_and_store_from_stack(Stack* stack, char* arr,
                                  int* next_available_index) {
  for (int i = stack->size - 1; i >= 0; i--) {
    arr[*next_available_index] = pop(stack);
    if (arr[*next_available_index] == 'R') {
      break;
    }
    (*next_available_index)++;
  }
}

/**
 * @brief Удаляет лишние символы перед открывающей скобкой.
 *
 * @param[in,out] str Входная строка, в которой производится удаление.
 * @param[in] i Индекс открывающей скобки.
 */
void delete_brackets(char* str, size_t i) {
  size_t j = i + 1;
  // Удаление символов до открытой скобки
  while (str[j] != '(') {
    str[j] = ' ';
    j++;
  }
}

/**
 * @brief Заменяет символы sin->s, cos->c, tan->t, log->l.
 *
 * @param[in,out] string Входная строка, в которой производятся замены.
 * @param[in] i Текущий индекс во входной строке.
 */
void assign_sin_cos_tan_log(char* string, size_t i) {
  if ((string[i] == 's' && string[i + 1] == 'i') ||
      (string[i] == 'c' && string[i + 1] == 'o') ||
      (string[i] == 'l' && string[i + 1] == 'o') || (string[i] == 't')) {
    delete_brackets(string, i);
  }
}

/**
 * @brief Заменяет символы asin->s, acos->c, atan->t.
 *
 * @param[in,out] string Входная строка, в которой производятся замены.
 * @param[in] i Текущий индекс во входной строке.
 */
void assign_asin_acos_atan(char* string, size_t i) {
  ///< asin->s
  if (string[i] == 'a' && string[i + 1] == 's') {
    string[i] = 'i';
    delete_brackets(string, i);
  }
  ///<  acos->o
  if (string[i] == 'a' && string[i + 1] == 'c') {
    string[i] = 'o';
    delete_brackets(string, i);
  }
  ///<  atan->z
  if (string[i] == 'a' && string[i + 1] == 't') {
    string[i] = 'z';
    delete_brackets(string, i);
  }
}

/**
 * @brief Заменяет символы sqrt->q, ctg->g, ln->n.
 *
 * @param[in,out] string Входная строка, в которой производятся замены.
 * @param[in] i Текущий индекс во входной строке.
 */
void assign_sqrt_ctg_ln(char* string, size_t i) {
  ///<  sqrt->q
  if (string[i] == 's' && string[i + 1] == 'q') {
    string[i] = 'q';
    delete_brackets(string, i);
  }
  ///<  ctg->g
  if (string[i] == 'c' && string[i + 1] == 't') {
    string[i] = 'g';
    delete_brackets(string, i);
  }
  ///<  ln->n
  if (string[i] == 'l' && string[i + 1] == 'n') {
    string[i] = 'n';
    delete_brackets(string, i);
  }
}

/**
 * @brief Обрабатывает унарные символы во входной строке.
 *
 * @param[in,out] string Входная строка, в котокой исходит обработка унарных
 * символов.
 * @param[in] i Текущий индекс во входной строке.
 */
void process_unary_syms(char* string, size_t i) {
  ///< кодировка унарного минуса в ~
  if (string[i] == '-' && (string[i - 1] == '(' || i == 0)) {
    string[i] = '~';
  }
  ///< удаление унарного плюса как незначимого
  if (string[i] == '+' && (string[i - 1] == '(' || i == 0)) {
    string[i] = ' ';
  }
}
