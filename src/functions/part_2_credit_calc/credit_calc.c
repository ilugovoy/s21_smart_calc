/*!
 * @file credit_calc.c
 * @brief Содержит функции кредитного калькулятора
 *
 */

#include "../headers/credit.h"

/**
 * Рассчитать ежемесячный платеж, общую выплату и переплату для заданного типа
 кредита.
 *
 * @param credit_sum   общая сумма кредита
 * @param interest_rate   годовая процентная ставка
 * @param months   срок кредита в месяцах
 * @param type   тип кредита (1 - аннуитетный, 2 - дифференцированный)
 * @param[out] monthly_payment   ежемесячный платеж
 * @param[out] monthly_payment_min   минимальный ежемесячный платеж для типа 2
 * @param[out] total_payment   общая выплата
 * @param[out] overpayment   переплата по кредиту
 * @return OK - успешное выполнение, CREDIT_TYPE_ERROR - неверный тип кредита
 *
 * @note
 * Для аннуитетного кредита:
 * Ежемесячный платеж рассчитывается по формуле: PMT = (P * r * (1 + r)^n) / ((1
 + r)^n - 1) Где:
 * PMT - ежемесячный платеж
 * P - общая сумма кредита
 * r - месячная процентная ставка
 * n - количество месяцев на погашение кредита
 * Общая выплата рассчитывается как произведение ежемесячного платежа на
 количество месяцев, т.е. (TotalPayment = PMT * n)
 * Переплата по кредиту вычисляется как разница между общей выплатой и общей
 суммой кредита: (Overpayment = TotalPayment - P)
 * Для дифференцированного кредита:
 * Ежемесячный платеж для дифференцированного кредита рассчитывается как сумма
 ежемесячного погашения основной суммы и начисленного процента за этот месяц.
 * С увеличением срока кредита начисленный процент уменьшается, что влияет на
 изменение размера ежемесячного платежа.
 * Минимальный ежемесячный платеж для дифференцированного кредита сохраняется в
 поле "monthly_payment_min".
 * В этом типе кредита он определяется как размер последнего ежемесячного
 платежа.
 * Так как сумма начисленного процента уменьшается с каждым месяцем, общая сумма
 ежемесячного платежа уменьшается.
 * После расчетов общей выплаты и переплаты, значение "monthly_payment"
 устанавливается как сумма ежемесячного платежа,
 * учитывающая выплату основной суммы и начисленного процента за первый месяц.

 */
int calculate_payments(CreditParameters* credit_calc) {
  int return_code = CREDIT_TYPE_ERROR;
  double monthly_interest = credit_calc->interest_rate / 100 /
                            12;  ///< Расчет месячной процентной ставки
  if (credit_calc->type == 1) {
    credit_calc->monthly_payment =
        (credit_calc->credit_sum * monthly_interest) /
        (1 - pow(1 + monthly_interest,
                 -credit_calc->months));  ///< Расчет ежемесячного платежа для
                                          ///< аннуитетного кредита
    credit_calc->total_payment =
        credit_calc->monthly_payment *
        credit_calc->months;  ///< Общая выплата для аннуитетного кредита
    credit_calc->overpayment =
        credit_calc->total_payment -
        credit_calc->credit_sum;  ///< Переплата для аннуитетного кредита
    return_code = OK;
  } else if (credit_calc->type == 2) {
    double monthly_principal_payment =
        credit_calc->credit_sum /
        credit_calc->months;  // Расчет ежемесячного погашения основной суммы
    credit_calc->total_payment = 0;  // Обнуление общей выплаты
    credit_calc->overpayment = 0;  // Обнуление переплаты

    double monthly_payment = 0;
    for (int i = 1; i <= credit_calc->months; ++i) {
      double monthly_interest_payment = 0;
      monthly_interest_payment =
          (credit_calc->credit_sum - (i - 1) * monthly_principal_payment) *
          monthly_interest;  // Расчет ежемесячного начисленного процента
      monthly_payment =
          monthly_principal_payment +
          monthly_interest_payment;  // Расчет общего ежемесячного платежа

      credit_calc->monthly_payment =
          monthly_payment;  // Установка значения ежемесячного платежа, тут
                            // сохранится минимальный платёж
      credit_calc->total_payment +=
          monthly_payment;  // Накопление общей выплаты
      credit_calc->overpayment +=
          monthly_interest_payment;  // Накопление переплаты
    }
    credit_calc->monthly_payment_min = monthly_payment;
    credit_calc->monthly_payment =
        credit_calc->credit_sum / credit_calc->months +
        credit_calc->credit_sum * monthly_interest;
    return_code = OK;
  }
  return return_code;
}

// Очистка значений структуры
void init_or_clear_credit_parameters(CreditParameters* credit_calc) {
  credit_calc->credit_sum = 0.0;
  credit_calc->interest_rate = 0.0;
  credit_calc->months = 0;
  credit_calc->type = 0;
  credit_calc->monthly_payment = 0.0;
  credit_calc->monthly_payment_min = 0.0;
  credit_calc->total_payment = 0.0;
  credit_calc->overpayment = 0.0;
}
