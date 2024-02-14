/*!
 * @file calculate.c
 * @brief Функции для вычисления результата
 *
 */

#include "../headers/part_1.h"

// 0 - OK
// 2 - CALCULATION_ERROR

/**
 * @brief Выполняет вычисление выражения, заданного строкой, используя указанное
 * значение переменной x
 *
 * Принимает строку, представляющую математическое выражение, а также значение
 * переменной x. Обрабатывает каждый символ в строке, выполняя операции и
 * вычисляя значения с использованием стека данных. В результате получается
 * вычисленное значение выражения. В ходе выполнения также отслеживаются ошибки
 * и код ошибки устанавливается при необходимости.
 *
 * @param string Строка, представляющая математическое выражение
 * @param x Значение переменной x, используемое в выражении
 * @return double Вычисленное значение выражения
 *
 * @note Функции, используемые в процессе вычисления:
 *  - process_and_push_number(): преобразует символы в числовое значение и
 * записывает их в стек
 *  - execute_arithmetic_operation(): выполняет арифметическую операцию,
 * используя значения из стека
 *  - process_math_function(): извлекает значение из стека, выполняет
 * соответствующую математическую операцию и обновляет стек с результатом
 *  - num_push(): помещает значение в стек
 *  - num_pop(): извлекает значение из стека
 *
 * @note Ошибки отслеживаются и кодируются следующим образом:
 *  - INCORRECT_VALUE: значение, выходящее за пределы допустимых значений
 *  - CALCULATION_ERROR: ошибка при выполнении вычислений
 */
double calculate(char* string, double x) {
  /// Инициализация стека данных
  num_Stack stack;
  stack.size = 0;

  // Переменные для отслеживания ошибок и хранения результата вычислений
  int error_code = OK;  ///< для отслеживания и возврата ошибки
  double result = 0;  ///< возвращаемое значение с результатом вычисления
  double input_1 = 0, input_2 = 0;  ///< операнды

  // Цикл обработки каждого символа в строке
  for (int i = 0; (string[i] != '\0'); i++) {
    // Если текущий символ - цифра или число
    if (is_num(string[i]) || string[i] == 'e' || string[i] == 'E') {
      // преобразование символов в числовое значение и запись стек
      process_and_push_number(string, &i, &error_code, &stack);
    }
    // Если текущий символ - разделитель '|', продолжаем обработку следующего
    // символа
    else if (string[i] == 'x') {
      if (num_push(&stack, x) != 0) error_code = CALCULATION_ERROR;
      i++;
    } else if (string[i] == '|') {
      continue;
    }
    // Если текущий символ - оператор арифметической операции
    else if (string[i] == '+' || string[i] == '-' || string[i] == '/' ||
             string[i] == '*' || string[i] == '%' || string[i] == '^') {
      execute_arithmetic_operation(string, &stack, &input_1, &input_2, &i,
                                   &error_code);
    }
    // Если текущий символ - символ математической функции
    else if (is_math_function(string, i)) {
      process_math_function(string, i, &stack, &input_1, &error_code);
    }
    if (error_code == 1) break;  // Проверка на наличие ошибок
  }
  if (error_code == 1)
    result = INCORRECT_VALUE;  // если были обнаружены ошибки, то результатом
                               // становится невозможное в контексте программы
                               // значение
  else
    result = num_pop(&stack);  // иначе - верхний элемент стека

  destroy_num_stack(&stack);
  return result;  // Возвращаем результат вычислений
}

/**
 * \brief Анализирует строку и преобразует цифровые символы в их численные
 * значения.
 *
 * Функция проходит по строке и преобразует цифровые символы в их численные
 * значения, учитывая наличие десятичной точки. Осуществляет подсчет количества
 * цифр и десятичных знаков.
 *
 * \param string Входная строка, которую необходимо проанализировать.
 * \param j Указатель на индекс в строке, начиная с которого нужно обработать
 * символы. \param k Указатель на переменную, в которую будет записано
 * количество цифровых символов. \param m Указатель на переменную, в которую
 * будет записано количество десятичных знаков. \param flag Указатель на флаг,
 * указывающий наличие десятичной точки в числе.
 */
void analyze_and_convert_numbers(const char* string, int* j, int* k, int* m,
                                 int* flag) {
  while (string[*j] != '|') {
    if (string[*j] == '.') {
      *flag = 1;
      (*j)++;
    }
    if (*flag) {
      (*j)++;
      (*m)--;
    } else {
      (*j)++;
      (*k)++;
    }
  }
  *flag = 0;
  *m = -1;
}

/**
 * @brief Обрабатывает экспоненциальное представление чисел во входной строке.
 *
 * Функция анализирует переданную строку и обрабатывает экспоненциальное
 * представление чисел, если оно присутствует. В случае нахождения символов 'e'
 * или 'E' функция выполняет конверсию чисел в экспоненциальной записи в их
 * численные значения и сохраняет результат в переменную tmp.
 *
 * @param string Указатель на входную строку, которую необходимо
 * проанализировать.
 * @param i Указатель на индекс, с которого начинается анализ строки.
 * @param flag_iskluchenie Указатель на булеву переменную, указывающую, что
 * экспоненциальное представление найдено.
 * @param tmp Указатель на переменную, в которую будет сохранено полученное
 * числовое значение из экспоненциальной записи.
 */
void process_exponent(const char* string, int* i, bool* flag_iskluchenie,
                      double* tmp) {
  for (size_t l = 0; l < strlen(string); l++) {
    if (string[*i] == 'e' || string[*i] == 'E') {
      *flag_iskluchenie = true;
      bool flag_exponent = true;
      int metka = *i;
      if (string[metka + 1] == '-' || string[metka + 1] == '+') {
        if (string[metka + 1] == '+') flag_exponent = false;
        (*i)++;
      }
      if (string[metka] == 'E') flag_exponent = false;
      // Конверсия чисел из экспоненциальной записи в численное значение
      double base = atof(string);  // Преобразовывает строку во входном формате
                                   // в численное значение
      (*i)++;  // Переход к следующему символу после 'e'
      double exponent = atof(&string[*i]);  // Преобразовывает строку после 'e'
                                            // в численное значение
      if (!flag_exponent) {
        *tmp = base *
               pow(10, exponent);  // Вычисление значения из экспоненциальной
                                   // формы в обычное численное значение
        break;
      } else {
        *tmp = base /
               pow(10, exponent);  // Вычисление значения из экспоненциальной
                                   // формы в обычное численное значение
        break;
      }
    }
  }
}

/**
 * \brief Преобразует цифровые символы из строки в их численные значения и
 * записывает их в стек.
 *
 * Функция преобразует цифровые символы из строки в их численные значения и
 * записывает их в стек для дальнейшего использования в вычислениях.
 *
 * \param string Входная строка с цифровыми символами.
 * \param i Индекс входной строки, начиная с которого нужно обработать символы.
 * \param error_code флаг ошибки.
 * \param stack Структура стека, в который будет записано полученное числовое
 * значение.
 */
void process_and_push_number(const char* string, int* i, int* error_code,
                             num_Stack* stack) {
  int j = *i;  ///< Индекс для обработки символов внутри функции
  int k = -1;  ///< Количество цифровых символов до десятичной точки
  int m = 0;  ///< Количество цифровых символов после десятичной точки
  int flag = 0;  ///< Флаг, указывающий наличие десятичной точки в числе
  analyze_and_convert_numbers(
      string, &j, &k, &m, &flag);  // Функция для анализа и преобразования чисел
  double tmp = 0;  ///< Временная переменная для накопления числовых значений
  bool flag_iskluchenie = false;
  process_exponent(string, i, &flag_iskluchenie, &tmp);
  if (flag_iskluchenie != true) {
    // Цикл для извлечения числовых значений из строки и накопления их в
    // переменной tmp
    while (string[*i] != '|') {
      if (string[*i] == '.') {
        flag = 1;
        j++;
        (*i)++;
      }
      if (flag) {
        tmp += (string[*i] - '0') * pow(10, m);
        (*i)++;
        m--;
      } else {
        tmp += (string[*i] - '0') * pow(10, k);
        k--;
        (*i)++;
      }
    }
  }
  // Добавление полученного числового значения в стек
  if (num_push(stack, tmp) != 0) {
    *error_code =
        CALCULATION_ERROR;  ///< Установка кода ошибки при возникновении
                            ///< проблемы с добавлением в стек
  }
}

/**
 * @brief Выполняет арифметическую операцию и обновляет стек с результатом
 *
 * Принимает арифметическую операцию, закодированную в строке ввода, извлекает
 * два верхних элемента из стека, выполняет соответствующую арифметическую
 * операцию, а затем обновляет стек результатом. Также производится проверка
 * деления на очень малое число и соответствующее обновление кода ошибки.
 *
 * @param string Строка, содержащая символы арифметической операции
 * @param stack Указатель на структуру данных стека
 * @param input_1 Указатель на первое входное значение
 * @param input_2 Указатель на второе входное значение
 * @param i Указатель на индекс для доступа к символу арифметической операции во
 * входной строке
 * @param error_code Указатель на переменную кода ошибки
 *
 * @note Эта функция предполагает, что стек и входные значения правильно
 * инициализированы.
 */
void execute_arithmetic_operation(char* string, num_Stack* stack,
                                  double* input_1, double* input_2,
                                  const int* i, int* error_code) {
  *input_2 = num_pop(stack);  ///< Берем из стека первое число
  *input_1 = num_pop(stack);  ///< Берем из стека второе число
  if ((*input_1 == INCORRECT_VALUE) || (*input_2 == INCORRECT_VALUE))
    *error_code = CALCULATION_ERROR;

  // Выполнение соответствующей математической функции и обновление стека с
  // результатом
  switch (string[*i]) {
    case '+':
      if (num_push(stack, *input_1 + *input_2) != 0)
        *error_code = CALCULATION_ERROR;
      break;
    case '-':
      if (num_push(stack, *input_1 - *input_2) != 0)
        *error_code = CALCULATION_ERROR;
      break;
    case '*':
      if (num_push(stack, *input_1 * *input_2) != 0)
        *error_code = CALCULATION_ERROR;
      break;
    case '/':
      if (num_push(stack, *input_1 / *input_2) != 0)
        *error_code = CALCULATION_ERROR;
      break;
    case '%':
      if (num_push(stack, fmod(*input_1, *input_2)) != 0)
        *error_code = CALCULATION_ERROR;
      break;
    case '^':
      if (num_push(stack, pow(*input_1, *input_2)) != 0)
        *error_code = CALCULATION_ERROR;
      break;
  }
}

/**
 * @brief Проверяет, является ли символ математической функцией
 *
 * Эта функция проверяет, представляет ли указанный символ математическую
 * функцию, возвращая true, если символ соответствует одной из известных
 * математических функций, и false в противном случае.
 *
 * @param string Входная строка, в которой производится поиск математических
 * функций
 * @param i Индекс символа во входной строке, который нужно проверить
 *
 * @return true, если символ представляет собой математическую функцию; в
 * противном случае возвращается false
 */
bool is_math_function(const char* string, int i) {
  return string[i] == 's' || string[i] == 'q' || string[i] == 'l' ||
         string[i] == 'c' || string[i] == 'g' || string[i] == 't' ||
         string[i] == 'i' || string[i] == 'o' || string[i] == 'z' ||
         string[i] == 'n' || string[i] == '~';
}

/**
 * @brief Выполняет математическую функцию и обновляет стек с результатом
 *
 * Эта функция извлекает значение из стека, проверяет его на ошибки
 * затем выполняет соответствующую математическую функцию
 * и обновляет стек с полученным результатом.
 * В случае возникновения ошибки, код ошибки также обновляется.
 *
 * @param string Входная строка, содержащая символы математических функций
 * @param i Индекс символа во входной строке, представляющий требуемую
 * математическую функцию
 * @param stack Указатель на структуру данных стека
 * @param input_1 Указатель на переменную для хранения извлеченного значения из
 * стека
 * @param error_code Указатель на переменную кода ошибки
 *
 */
void process_math_function(char* string, int i, num_Stack* stack,
                           double* input_1, int* error_code) {
  *input_1 = num_pop(stack);
  if (*input_1 == INCORRECT_VALUE) *error_code = CALCULATION_ERROR;
  // Выполнение соответствующей математической функции и обновление стека с
  // результатом
  //// double angle_radians = input_1 * RAD_TO_DEG; // переводим значение из
  ///радиан в градусы
  switch (string[i]) {
    case 's':
      if (num_push(stack, sin(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case 'c':
      if (num_push(stack, cos(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case 'q':
      if (num_push(stack, sqrt(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case 'l':
      if (num_push(stack, log10(*input_1)) != 0)
        *error_code = CALCULATION_ERROR;
      break;
    case 't':
      if (num_push(stack, tan(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case 'g':
      if (num_push(stack, cos(*input_1) / sin(*input_1)) != 0)
        *error_code = CALCULATION_ERROR;
      break;
    case 'i':
      if (num_push(stack, asin(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case 'o':
      if (num_push(stack, acos(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case 'n':
      if (num_push(stack, log(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case 'z':
      if (num_push(stack, atan(*input_1)) != 0) *error_code = CALCULATION_ERROR;
      break;
    case '~':
      if (num_push(stack, *input_1 * -1) != 0) *error_code = CALCULATION_ERROR;
      break;
  }
}
