/**
 * \file main.cpp
 * \brief Основной файл приложения, который инициализирует приложение Qt и создает главное окно.
 *
 * В этом файле определен основной код приложения, который инициализирует приложение Qt и создает главное окно приложения.
 *
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
	
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
