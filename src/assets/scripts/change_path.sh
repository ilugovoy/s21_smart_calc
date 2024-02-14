#!/bin/bash

# Установка пути по умолчанию
APP_DEST_PATH="calculator"

# Выводим сообщение о дефолтном пути
read -p "Дефолтный путь для установки программы src/calculator. Хотите изменить папку установки? (y/n): " answer

# Проверка ответа пользователя
if [ "$answer" = "y" ]; then
    read -p "Введите путь для установки программы: " custom_path
    if [ -n "$custom_path" ]; then
        APP_DEST_PATH="$custom_path"
    fi
elif [ "$answer" = "n" ]; then
    echo "Используется папка установки по умолчанию: $APP_DEST_PATH"
fi

# Выводим значение переменной APP_DEST_PATH
echo $APP_DEST_PATH
