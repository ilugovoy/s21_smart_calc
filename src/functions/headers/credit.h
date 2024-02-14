/*!
 * @file credit.h
 * @brief Содержит объявления функций и структур кредитного калькулятора
 *
 */

#ifndef CREDIT_H
#define CREDIT_H

#include "part_1.h"

typedef struct {
  double credit_sum;     ///< сумма кредита
  double interest_rate;  ///< годовая процентная ставка
  int months;            ///< срок кредита в месяцах
  int type;  ///< тип кредита: 1 - аннуитетный, 2 - дифференцированный
  double monthly_payment;  ///< ежемесячный платеж
  double monthly_payment_min;  ///< ежемесячный платеж для типа 2
  double total_payment;  ///< общая выплата
  double overpayment;    ///< переплата по кредиту
} CreditParameters;

int calculate_payments(
    CreditParameters* credit_calc);  ///< считает ежемесячный платёж, переплату
                                     ///< и общую сумму выплат
void init_or_clear_credit_parameters(
    CreditParameters* credit_calc);  // очистка и инициализация полей структуры

#endif
