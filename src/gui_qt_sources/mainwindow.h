/**
 * @file mainwindow.h
 * @brief Заголовочный файл, описывающий класс главного окна приложения
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qcustomplot.h>  ///< Подключение модуля для построения графиков
#include <stdio.h>
#include <stdlib.h>

#include <QFrame>  ///< Подключение модуля для создания рамок
#include <QLabel>  ///< Подключение модуля для создания текстовых полей
#include <QLineEdit>  ///< Подключение модуля однострочного поля ввода
#include <QMainWindow>  ///< Подключение модуля главного окна
#include <QSettings>  ///< Подключение модуля для работы с настройками приложения
#include <QString>  ///< Подключение модуля для работы с строками
#include <QTabWidget>  ///< Подключение модуля виджета в виде вкладок
#include <QVector>  ///< Подключение модуля для работы с векторами
#include <QWidget>  ///< Подключение модуля базового класса для всех объектов интерфейса
#include <iostream>

/**
 * @brief Внешний блок для подключения функций на языке C
 */
extern "C" {
#include "../functions/headers/part_1.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Класс, описывающий главное окно приложения
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса MainWindow
   * @param parent Указатель на родительский объект
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Деструктор класса MainWindow
   */
  ~MainWindow();

 private slots:
  /// обработчики операндов
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_0_clicked();
  void on_pushButton_point_clicked();

  /// обработчики операторов
  void on_pushButton_x_clicked();
  void on_pushButton_div_clicked();
  void on_pushButton_minus_clicked();
  void on_pushButton_mul_clicked();
  void on_pushButton_plus_clicked();
  void on_pushButton_e_clicked();

  /// обработчики функций
  void on_pushButton_pow_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_atan_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_ln_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_sqrt_clicked();
  void on_pushButton_tan_clicked();

  /// обработчики ввода, очистки
  void on_pushButton_OK_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_C_clicked();

  /// обработчики кнопок переключения дополнительных инструментов
  void on_pushButton_graph_clicked();

  /// обработчики скобок
  void on_pushButton_brackets_left_clicked();
  void on_pushButton_brackets_right_clicked();

  /// обработчики спинбоксов
  void on_spinBox_valueChanged(int arg1);

  /// обработчики кредитного калькулятора
  void on_pushButton_credit_calculate_clicked();
  void on_doubleSpinBox_credit_sum_valueChanged(double arg1);
  void on_spinBox_credit_months_valueChanged(int arg1);
  void on_doubleSpinBox_credit_interest_rate_valueChanged(double arg1);
  void on_checkBox_diff_type_pressed();
  void on_checkBox_fix_type_pressed();

  /// обработчики депозитного калькулятора
  void on_doubleSpinBox_deposit_sum_valueChanged(double arg1);
  void on_spinBox_deposit_months_valueChanged(int arg1);
  void on_doubleSpinBox_deposit_interest_rate_valueChanged(double arg1);
  void on_doubleSpinBox_tax_rate_valueChanged(double arg1);
  void on_pushButton_deposit_calculate_clicked();

 private:
  Ui::MainWindow *ui;  ///< Указатель на объект пользовательского интерфейса

  int x_flag = 1;               ///< Флаг операции
  int xrange_flag = 0;          ///< Флаг диапазона
  int xrange = 1;               ///< Диапазон
  double xconst = 0;            ///< Константа x
  double h = 2 * xrange / 50;   ///< Шаг
  double xBegin = -1 * xrange;  ///< Начальное значение x
  double xEnd = xrange;         ///< Конечное значение x
  QVector<double> x, y;         ///< Векторы значений x и y

  const char *str = NULL;    ///< Указатель на строку
  const char *x_str = NULL;  ///< Указатель на строку x
  double x_point = 0;        ///< Значение x
  double res = 0;            ///< Результат

  CreditParameters
      credit_calc;  ///< Структура для работы с кредитным калькулятором

  double SpinBox_credit_sum_value = 0;
  double spinBox_credit_months_value = 0;
  double SpinBox_credit_interest_rate_value = 10;
  int checkBox_type_of_credit = 0;

  DepositParameters
      deposit_calc;  ///< Структура для работы с кредитным калькулятором

  double SpinBox_deposit_sum = 0;
  double spinBox_deposit_months = 0;
  double SpinBox_deposit_interest_rate = 10;
  double SpinBox_deposit_tax_rate = 10;
};

#endif  // MAINWINDOW_H
