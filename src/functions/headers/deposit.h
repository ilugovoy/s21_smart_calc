/*!
 * @file deposit.h
 * @brief Содержит объявления функций и структур депозитного калькулятора
 *
 */

#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "part_1.h"

/**
 *
 * @struct DepositParameters
 * @brief Структура, описывающая параметры депозита
 * Структура содержит информацию о сумме депозита, сроке в месяцах, процентной
 * ставке, налоговой ставке, начисленных процентах, сумме налога и окончательной
 * сумме депозита.
 */
typedef struct {
  double deposit_sum;  ///< сумма вклада
  int deposit_months;  ///< срок срок размещения в месяцах
  double deposit_interest_rate;  ///< годовая процентная ставка
  double tax_rate;               ///< налоговая ставка

  double accrued_interest;  ///< начисленные проценты
  double tax_amount;        ///< сумма налога
  double final_deposit_sum;  ///< сумма на вкладе к концу срока

} DepositParameters;

int calculate_deposit(
    DepositParameters*
        deposit_calc);  ///< считает начисленные проценты, сумму налога и сумму
                        ///< на вкладе к концу срока
void init_or_clear_deposit_parameters(
    DepositParameters*
        deposit_calc);  // очистка и инициализация полей структуры

#endif
