/**
 * @file mainwindow.cpp
 * @brief Реализация класса MainWindow
 */
 
#include "mainwindow.h" ///< хэдэр для сборки интерфейса
#include "ui_mainwindow.h" ///< генерируется автоматически при компиляции файла интерфейса mainwindow.ui

/**
 * @brief Конструктор класса MainWindow
 * @param parent Указатель на родительский объект
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->widget->addGraph(); ///< Создание графического элемента
	ui->widget->setBackground(QBrush(QColor(83, 83, 83))); ///< установка цвета фона
	// ui->widget->setBackground(QBrush(QColor(130, 130, 130))); // установка цвета фона

    /// Инициализация параметров графика
    ui->widget->xAxis->setRange(-1*xrange, xrange);
    ui->widget->yAxis->setRange(-1*xrange, xrange);
    ui->widget->replot();
}

/**
 * @brief Деструктор класса MainWindow
 */
MainWindow::~MainWindow() {
    delete ui;
}


/**
 * @brief Обработчики нажатия кнопок
 */

void MainWindow::on_pushButton_0_clicked() {
    ui->lineEdit->insert("0");
}

void MainWindow::on_pushButton_1_clicked() {
    ui->lineEdit->insert("1");
}

void MainWindow::on_pushButton_2_clicked() {
    ui->lineEdit->insert("2");
}

void MainWindow::on_pushButton_3_clicked() {
    ui->lineEdit->insert("3");
}

void MainWindow::on_pushButton_4_clicked() {
    ui->lineEdit->insert("4");
}

void MainWindow::on_pushButton_5_clicked() {
    ui->lineEdit->insert("5");
}

void MainWindow::on_pushButton_6_clicked() {
    ui->lineEdit->insert("6");
}

void MainWindow::on_pushButton_7_clicked() {
    ui->lineEdit->insert("7");
}

void MainWindow::on_pushButton_8_clicked() {
    ui->lineEdit->insert("8");
}

void MainWindow::on_pushButton_9_clicked() {
    ui->lineEdit->insert("9");
}

void MainWindow::on_pushButton_e_clicked() {
    ui->lineEdit->insert("e");
}



/// Обработчик нажатия кнопки ОК
void MainWindow::on_pushButton_OK_clicked() {
    /// Получение текста из поля ввода и преобразование в строку
    std::string text = ui->lineEdit->text().toUtf8().constData();
    str = text.c_str(); /// Преобразование строки в формат const char*

    /// Вывод значения переменной x_flag в стандартный поток вывода
    std::cout << x_flag << std::endl;

    /// Проверка наличия точки в конце строки или пустоты
    if (str[strlen(str)-1] == '.' || strlen(str) == 0) {
        return; /// Возврат, если условие выполняется
    }

    x_point = xconst; /// Присвоение переменной x_point значения xconst
    /// Вызов функции process_and_calculate с передачей строки, x_point и указателя на res
    if (process_and_calculate(str, x_point, &res) == 0) {
        std::string output_str; /// Объявление переменной для хранения результирующей строки
        /// Проверка на близость результата к целому числу
        if (std::abs(res - static_cast<int>(res)) < 1.0/1000000) {
            output_str = std::to_string(static_cast<int>(res)); /// Преобразование целого числа в строку
        } 
        else {
            output_str = std::to_string(res); /// Преобразование числа с плавающей точкой в строку
            output_str.erase(output_str.find_last_not_of('0') + 1, std::string::npos); /// Удаление незначимых нулей в конце числа
            if (output_str.back() == '.') { /// Если число заканчивается на десятичную точку, удаляем её
                output_str.pop_back();
            }
        }
        ui->lineEdit->setText(output_str.c_str()); /// Установка текста в поле ввода
    } 
    else {
        ui->lineEdit->setText("ERROR"); /// Установка текста "ERROR" в поле ввода
    }
}



/// Обработчик нажатия кнопки "Построить график"
void MainWindow::on_pushButton_graph_clicked() {

    int err = 0;
    std::string text=ui->lineEdit->text().toUtf8().constData();
    str = text.c_str();

    if (str[strlen(str)-1] == '.' || strlen(str) == 0) {
        return;
    }

    xrange = ui->accuracySpinBox->value();

    x.clear();
    y.clear();
	ui->widget->clearGraphs();
    std::cout << xrange << std::endl;
    ui->widget->xAxis->setRange(-1*xrange, xrange);
    ui->widget->yAxis->setRange(-1*xrange, xrange);
    ui->widget->addGraph(0);

    ui->widget->graph(0)->setPen(QColor(255, 0, 0, 255));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));


    h = 0.0004 * xrange;
    xBegin = -1 * xrange;
    xEnd = xrange;

    // Цикл по значениям x_point
    for (x_point = xBegin; x_point < xEnd;) {
        // Вызов функции process_and_calculate с передачей строки, x_point и указателя на res
        if (process_and_calculate(str, x_point, &res)==0) {
            x.push_back(x_point); /// Добавление значения x_point в вектор x
            y.push_back(res); /// Добавление значения res в вектор y
            x_point = x_point + h; /// Увеличение значения x_point на шаг h
        } 
		else {
            ui->lineEdit->setText("ERROR"); // Установка текста "ERROR" в поле ввода
            err = 1;
            break;
        }
     }
    if (err==0) {
        ui->widget->graph(0)->addData(x,y); /// Добавление данных в график
        ui->widget->replot(); /// Перерисовка графика
    } 
	else {
        ui->lineEdit->setText("ERROR"); /// Установка текста "ERROR" в поле ввода
    }
}



/// Обработчики нажатия кнопок для ввода символов и функций

void MainWindow::on_pushButton_x_clicked() {
    ui->lineEdit->insert("x");
}

void MainWindow::on_pushButton_brackets_left_clicked() {
    ui->lineEdit->insert("(");
}

void MainWindow::on_pushButton_brackets_right_clicked() {
    ui->lineEdit->insert(")");
}

void MainWindow::on_pushButton_div_clicked() {
    if (!(ui->lineEdit->text().endsWith('/')) && (xrange_flag==0))
    ui->lineEdit->insert("/");
}

void MainWindow::on_pushButton_minus_clicked() {
    if (!(ui->lineEdit->text().endsWith('-')) && (xrange_flag==0))
    ui->lineEdit->insert("-");
}

void MainWindow::on_pushButton_mul_clicked() {
    if (!(ui->lineEdit->text().endsWith('*')) && (xrange_flag==0))
    ui->lineEdit->insert("*");
}

void MainWindow::on_pushButton_plus_clicked() {
    if (!(ui->lineEdit->text().endsWith('+')) && (xrange_flag==0))
    ui->lineEdit->insert("+");
}

void MainWindow::on_pushButton_point_clicked() {
    if (!(ui->lineEdit->text().endsWith('.')))
    ui->lineEdit->insert(".");
}

void MainWindow::on_pushButton_pow_clicked() {
    if (!(ui->lineEdit->text().endsWith('^')) && (xrange_flag==0))
    ui->lineEdit->insert("^");
}

void MainWindow::on_pushButton_mod_clicked() {
    if (!(ui->lineEdit->text().endsWith('%')) && (xrange_flag==0))
    ui->lineEdit->insert("%");
}

void MainWindow::on_pushButton_acos_clicked() {
    if (!(ui->lineEdit->text().endsWith("n(")) && !(ui->lineEdit->text().endsWith("s(")) && (xrange_flag==0))
    ui->lineEdit->insert("acos(");
}

void MainWindow::on_pushButton_asin_clicked() {
    if (!(ui->lineEdit->text().endsWith("n(")) && !(ui->lineEdit->text().endsWith("s(")) && (xrange_flag==0))
    ui->lineEdit->insert("asin(");
}

void MainWindow::on_pushButton_atan_clicked() {
    if (!(ui->lineEdit->text().endsWith("n(")) && !(ui->lineEdit->text().endsWith("s(")) && (xrange_flag==0))
    ui->lineEdit->insert("atan(");
}

void MainWindow::on_pushButton_cos_clicked() {
    if (!(ui->lineEdit->text().endsWith("n(")) && !(ui->lineEdit->text().endsWith("s(")) && (xrange_flag==0))
    ui->lineEdit->insert("cos(");
}

void MainWindow::on_pushButton_ln_clicked() {
    ui->lineEdit->insert("ln(");
}

void MainWindow::on_pushButton_log_clicked() {
    ui->lineEdit->insert("log(");
}

void MainWindow::on_pushButton_sin_clicked() {
    if (!(ui->lineEdit->text().endsWith("n(")) && !(ui->lineEdit->text().endsWith("s(")) && (xrange_flag==0))
    ui->lineEdit->insert("sin(");
}

void MainWindow::on_pushButton_sqrt_clicked() {
    if (!(ui->lineEdit->text().endsWith('t')) && (xrange_flag==0))
    ui->lineEdit->insert("sqrt(");
}

void MainWindow::on_pushButton_tan_clicked() {
    if (!(ui->lineEdit->text().endsWith("n(")) && !(ui->lineEdit->text().endsWith("s(")) && (xrange_flag==0))
    ui->lineEdit->insert("tan(");
}


/// Обработчик нажатия кнопки "Очистить"
void MainWindow::on_pushButton_AC_clicked() {
    ui->lineEdit->setText(0);
    x_flag = 0;
}

/// Обработчик нажатия кнопки "Удалить"
void MainWindow::on_pushButton_C_clicked() {
    QString currentText = ui->lineEdit->text();  // Получаем текущий текст из поля ввода
    if (currentText.length() > 0) {  // Проверяем, есть ли в поле ввода текст
        currentText.chop(1);  // Удаляем последний символ из строки
        ui->lineEdit->setText(currentText);  // Устанавливаем измененный текст в поле ввода
    }
    x_flag = 0;  // Устанавливаем флаг x_flag в начальное состояние
}


/// Обработчик изменения значения в даблспинбоксе
void MainWindow::on_spinBox_valueChanged(int arg1) {
    xconst = arg1;
}


// ------------------------------------------------------------------------------- КРЕДИТНЫЙ КАЛЬКУЛЯТОР
//typedef struct {

//    double credit_sum;           ///< сумма кредита
//    double interest_rate;        ///< годовая процентная ставка
//    int months;                  ///< срок кредита в месяцах
//    int type;                    ///< тип кредита: 1 - аннуитетный, 2 - дифференцированный

//    double monthly_payment;      ///< ежемесячный платеж
//    double total_payment;        ///< общая выплата
//    double overpayment;          ///< переплата по кредиту

//} CreditParameters;

/// Обработчик изменения значения в даблспинбоксе сумма кредита
void MainWindow::on_doubleSpinBox_credit_sum_valueChanged(double arg1) {
    SpinBox_credit_sum_value = arg1;
}

/// Обработчик изменения значения в даблспинбоксе срок кредита
void MainWindow::on_spinBox_credit_months_valueChanged(int arg1) {
    spinBox_credit_months_value = arg1;
}

/// Обработчик изменения значения в даблспинбоксе процентная ставка
void MainWindow::on_doubleSpinBox_credit_interest_rate_valueChanged(double arg1) {
    SpinBox_credit_interest_rate_value = arg1;
}

///// Обработчик изменения значения в чекбоксе фиксированный тип кредита
void MainWindow::on_checkBox_fix_type_pressed() {
    checkBox_type_of_credit = 1;
}

///// Обработчик изменения значения в чекбоксе убывающий тип платежа кредита
void MainWindow::on_checkBox_diff_type_pressed() {
    checkBox_type_of_credit = 2;
}



/// Обработчики нажатия кнопки посчитать кредит
void MainWindow::on_pushButton_credit_calculate_clicked() {

    // инициализирую выходные значения
    credit_calc.monthly_payment = 0.0;
    credit_calc.monthly_payment_min = 0.0;
    credit_calc.total_payment = 0.0;
    credit_calc.overpayment = 0.0;

    // заполняю значения структуры
    credit_calc.credit_sum = SpinBox_credit_sum_value;
    credit_calc.months = spinBox_credit_months_value;
    credit_calc.interest_rate = SpinBox_credit_interest_rate_value;
    credit_calc.type = checkBox_type_of_credit;

    calculate_payments(&credit_calc); // провожу вычисления

    QLocale locale(QLocale::Russian); // позволяет отображать числа с учетом разрядности

    QString text; // переменная для хранения результата ежемесячной выплаты
    if(credit_calc.monthly_payment_min == 0) text = locale.toString(credit_calc.monthly_payment, 'f', 2);
    else text = locale.toString(credit_calc.monthly_payment, 'f', 2) + " - " + locale.toString(credit_calc.monthly_payment_min);

    // вывожу результат
    // 'f' указывает на формат числа с плавающей запятой, а 0 указывает на количество отображаемых десятичных знаков
    ui->label_monthly_payment_res->setText(text);
    ui->label_overpayment_res->setText(locale.toString(credit_calc.overpayment, 'f', 2));
    ui->label_total_payment_res->setText(locale.toString(credit_calc.total_payment, 'f', 2));

    init_or_clear_credit_parameters(&credit_calc);

}


// ------------------------------------------------------------------------------- ДЕПОЗИТНЫЙ КАЛЬКУЛЯТОР

//double SpinBox_deposit_sum = 0;
//double spinBox_deposit_months = 0;
//double SpinBox_deposit_interest_rate = 10;
//double SpinBox_deposit_tax_rate = 10;


void MainWindow::on_doubleSpinBox_deposit_sum_valueChanged(double arg1) {
    SpinBox_deposit_sum = arg1;
}


void MainWindow::on_spinBox_deposit_months_valueChanged(int arg1) {
    spinBox_deposit_months = arg1;
}


void MainWindow::on_doubleSpinBox_deposit_interest_rate_valueChanged(double arg1) {
    SpinBox_deposit_interest_rate = arg1;
}



void MainWindow::on_doubleSpinBox_tax_rate_valueChanged(double arg1) {
    SpinBox_deposit_tax_rate = arg1;
}


/// Обработчики нажатия кнопки посчитать депозит
void MainWindow::on_pushButton_deposit_calculate_clicked() {

    //  deposit_calc->deposit_sum = 0;       		///< сумма вклада
    //	deposit_calc->deposit_months = 0;       	///< срок размещения в месяцах
    //  deposit_calc->deposit_interest_rate = 0;	///< годовая процентная ставка
    //	deposit_calc->tax_rate = 0;					///< налоговая ставка

    //	deposit_calc->accrued_interest = 0;       	///< начисленные проценты
    //	deposit_calc->tax_amount = 0;       		///< сумма налога
    //	deposit_calc->final_deposit_sum = 0;       	///< сумма на вкладе к концу срока

    // инициализирую выходные значения
    deposit_calc.accrued_interest = 0;
    deposit_calc.tax_amount = 0;
    deposit_calc.final_deposit_sum = 0;

    // заполняю значения структуры
    deposit_calc.deposit_sum = SpinBox_deposit_sum;
    deposit_calc.deposit_months = spinBox_deposit_months;
    deposit_calc.deposit_interest_rate = SpinBox_deposit_interest_rate;
    deposit_calc.tax_rate = SpinBox_deposit_tax_rate;

    calculate_deposit(&deposit_calc); // провожу вычисления

    QLocale locale(QLocale::Russian); // позволяет отображать числа с учетом разрядности
    // вывожу результат
    // 'f' указывает на формат числа с плавающей запятой, а 0 указывает на количество отображаемых десятичных знаков
    ui->label_accrued_interest_res->setText(locale.toString(deposit_calc.accrued_interest, 'f', 2));
    ui->label_tax_amount_res->setText(locale.toString(deposit_calc.tax_amount, 'f', 2));
    ui->label_final_deposit_sum_res->setText(locale.toString(deposit_calc.final_deposit_sum, 'f', 2));

    init_or_clear_deposit_parameters(&deposit_calc);
}

