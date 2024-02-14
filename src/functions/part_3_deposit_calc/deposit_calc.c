/*!
 * @file deposit_calc.c
 * @brief Содержит функции депозитного калькулятора
 *
 */

#include "../headers/deposit.h"

/**
 * Вычисление процентов и итоговой суммы депозита.
 * @param deposit_calc Структура с параметрами депозита
 * @return Код ошибки (0 - успешно, 1 - ошибка типа депозита)
 */
int calculate_deposit(DepositParameters* deposit_calc) {
  int return_code = CREDIT_TYPE_ERROR;
  if (deposit_calc->deposit_sum != 0 && deposit_calc->deposit_months != 0 &&
      deposit_calc->deposit_interest_rate != 0 && deposit_calc->tax_rate != 0) {
    double year_interest_rate_sum =
        deposit_calc->deposit_sum * (deposit_calc->deposit_interest_rate /
                                     100);  // суммна итого по гдовой ставке
    double month_interest_rate_sum =
        year_interest_rate_sum / 12;  // сколько начисляется в месяц

    deposit_calc->accrued_interest =
        month_interest_rate_sum * deposit_calc->deposit_months;
    deposit_calc->tax_amount =
        deposit_calc->accrued_interest * (deposit_calc->tax_rate / 100);
    deposit_calc->final_deposit_sum = deposit_calc->deposit_sum +
                                      deposit_calc->accrued_interest -
                                      deposit_calc->tax_amount;
    return_code = OK;
  }
  return return_code;
}

/**
 * Инициализация или очистка параметров депозита в структуре.
 * @param deposit_calc Структура для параметров депозита
 */
void init_or_clear_deposit_parameters(DepositParameters* deposit_calc) {
  deposit_calc->deposit_sum = 0;  ///< сумма вклада
  deposit_calc->deposit_months = 0;  ///< срок размещения в месяцах
  deposit_calc->deposit_interest_rate = 0;  ///< годовая процентная ставка
  deposit_calc->tax_rate = 0;  ///< налоговая ставка

  deposit_calc->accrued_interest = 0;  ///< начисленные проценты
  deposit_calc->tax_amount = 0;        ///< сумма налога
  deposit_calc->final_deposit_sum = 0;  ///< сумма на вкладе к концу срока
}
