#!/bin/bash

COMMAND=""
OS_TYPE=""
tool_check="check"
tool_lcov="lcov"
tool_gcov="gcov"

# Определение типа операционной системы
case "$(uname)" in
  "Darwin")
    echo "ОС: MacOS"
    OS_TYPE="MacOS"
    COMMAND="brew install"
    ;;
  "Linux")
    echo "ОС: Linux"
    OS_TYPE="Linux"
    COMMAND="sudo apt install -y"  # -y для автоматического подтверждения установки без запросов
    ;;
  *)
    echo "Операционная система не поддерживается."
    exit 1
    ;;
esac

# Проверяем clang-format
if ! command -v clang-format &> /dev/null; then
  echo "Утилита clang-format не установлена."
  read -p "Хотите установить утилиту clang-format? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt update
      $COMMAND clang-format
      echo "Утилита clang-format установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      $COMMAND clang-format
      echo "Утилита clang-format установлена."
    fi
  else
    echo "Утилита clang-format не будет установлена."
  fi
else
  echo "Утилита clang-format уже установлена."
fi

# Проверяем check на MacOS
if [ "$OS_TYPE" == "MacOS" ]; then
  if pkg-config --modversion check &> /dev/null; then
    echo "Утилита $tool_check уже установлена."
  else
    echo "Утилита $tool_check не установлена."
    read -p "Хотите установить утилиту $tool_check? [y/n] " response
    if [ "$response" == "y" ]; then
      $COMMAND $tool_check
      echo "Утилита $tool_check установлена."
    else
      echo "Утилита $tool_check не будет установлена."
    fi
  fi
fi

# Проверяем check на Linux
if [ "$OS_TYPE" == "Linux" ]; then
  if dpkg -s check &> /dev/null; then
    echo "Утилита $tool_check уже установлена."
  else
    echo "Утилита $tool_check не установлена."
    read -p "Хотите установить утилиту $tool_check? [y/n] " response
    if [ "$response" == "y" ]; then
      sudo apt-get update
      $COMMAND $tool_check
      echo "Утилита $tool_check установлена."
    else
      echo "Утилита $tool_check не будет установлена."
    fi
  fi
fi

# Проверяем lcov
if ! command -v $tool_lcov &> /dev/null; then
  echo "Утилита $tool_lcov не установлена."
  read -p "Хотите установить утилиту $tool_lcov? [y/n] " response
  if [ "$response" == "y" ]; then
    # Команды для установки утилиты
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt-get update
    fi
      $COMMAND $tool_lcov
      echo "Утилита $tool_lcov установлена."
  else
    echo "Утилита $tool_lcov не будет установлена."
  fi
else
  echo "Утилита $tool_lcov уже установлена."
fi

# Проверяем gcov
if ! command -v $tool_gcov &> /dev/null; then
  echo "Утилита $tool_gcov не установлена."
  read -p "Хотите установить утилиту $tool_gcov? [y/n] " response
  if [ "$response" == "y" ]; then
    # Команды для установки утилиты
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt-get update
    fi
	if [ "$OS_TYPE" == "MacOS" ]; then
      xcode-select --install
    fi
	  $COMMAND $tool_gcov
      echo "Утилита $tool_gcov установлена."
  else
    echo "Утилита $tool_gcov не будет установлена."
  fi
else
  echo "Утилита $tool_gcov уже установлена."
fi

# Проверяем cppcheck
if ! command -v cppcheck &> /dev/null; then
  echo "Утилита cppcheck не установлена."
  read -p "Хотите установить утилиту cppcheck? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt-get update
      sudo apt-get install -y cppcheck
      echo "Утилита cppcheck установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install cppcheck
      echo "Утилита cppcheck установлена."
    fi
  else
    echo "Утилита cppcheck не будет установлена."
  fi
else
  echo "Утилита cppcheck уже установлена."
fi




# Проверяем tar
if ! command -v tar &> /dev/null; then
  echo "Утилита tar не установлена."
  read -p "Хотите установить утилиту tar? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt update
      sudo apt install -y tar
      echo "Утилита tar установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install tar
      echo "Утилита tar установлена."
    fi
  else
    echo "Утилита tar не будет установлена."
  fi
else
  echo "Утилита tar уже установлена."
fi


# Проверяем Qt
if ! command -v qmake &> /dev/null || \
   ! dpkg -l | grep -i 'qtbase5-dev' &> /dev/null || \
   ! dpkg -l | grep -i 'qt6-base-dev' &> /dev/null || \
   ! dpkg -l | grep -i 'qtcreator' &> /dev/null || \
   ! dpkg -l | grep -i 'qtchooser' &> /dev/null || \
   ! dpkg -l | grep -i 'qt5-qmake' &> /dev/null || \
   ! dpkg -l | grep -i 'qtbase5-dev-tools' &> /dev/null || \
   ! dpkg -l | grep -i 'libqt5charts5' &> /dev/null || \
   ! dpkg -l | grep -i 'libqt5charts5-dev' &> /dev/null; then
  echo "Фреймворк Qt не установлен."
  read -p "Хотите установить Qt и нужные модули? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt update
      sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools libqt5charts5 libqt5charts5-dev qt6-base-dev qtcreator
      echo "Необходимые модули Qt установлены."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install qt
	  brew install --cask qt-creator
      echo "Необходимые модули Qt установлены."
    fi
  else
    echo "Необходимые модули Qt не будут установлены."
  fi
else
  echo "Необходимые модули Qt уже установлены."
fi

# # Проверяем установку GTK+ версии 3 на Linux 
# if [ "$OS_TYPE" == "Linux" ]; then
#   if dpkg -s libgtk-3-dev &> /dev/null; then
#     echo "Фреймворк GTK+ версии 3 уже установлен."
#   else
#     echo "Фреймворк GTK+ версии 3 не установлен."
#     read -p "Хотите установить фреймворк GTK+ версии 3? [y/n] " response
#     if [ "$response" == "y" ]; then
#       sudo apt-get update
#       $COMMAND libgtk-3-dev
#       echo "Фреймворк GTK+ версии 3 установлен."
#     else
#       echo "Фреймворк GTK+ версии 3 не будет установлен."
#     fi
#   fi

#   # Проверяем установку GTK+ версии 4 на Linux
#   if dpkg -s libgtk-4-dev &> /dev/null; then
#     echo "Фреймворк GTK+ версии 4 уже установлен."
#   else
#     echo "Фреймворк GTK+ версии 4 не установлен."
#     read -p "Хотите установить фреймворк GTK+ версии 4? [y/n] " response
#     if [ "$response" == "y" ]; then
#       sudo apt-get update
#       $COMMAND libgtk-4-dev
#       echo "Фреймворк GTK+ версии 4 установлен."
#     else
#       echo "Фреймворк GTK+ версии 4 не будет установлен."
#     fi
#   fi
# fi

# # Проверяем установку GTK+ на MacOS
# if [ "$OS_TYPE" == "MacOS" ]; then
#   if brew list gtk+ &> /dev/null; then
#     echo "Фреймворк GTK+ уже установлен."
#   else
#     echo "Фреймворк GTK+ не установлен."
#     read -p "Хотите установить фреймворк GTK+? [y/n] " response
#     if [ "$response" == "y" ]; then
#       brew install gtk+
#       echo "Фреймворк GTK+ установлен."
#     else
#       echo "Фреймворк GTK+ не будет установлен."
#     fi
#   fi
# fi

# Проверяем Doxygen
if ! command -v doxygen &> /dev/null; then
  echo "Утилита Doxygen не установлена."
  read -p "Хотите установить утилиту Doxygen? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt-get update
      $COMMAND doxygen
      echo "Утилита Doxygen установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install doxygen
      echo "Утилита Doxygen установлена."
    fi
  else
    echo "Утилита Doxygen не будет установлена."
  fi
else
  echo "Утилита Doxygen уже установлена."
fi

# Проверяем установку Graphviz
if ! command -v dot &> /dev/null; then
  echo "Утилита Graphviz (dot) не установлена."
  read -p "Хотите установить утилиту Graphviz? [y/n] " response
  if [ "$response" == "y" ]; then
    if [ "$OS_TYPE" == "Linux" ]; then
      sudo apt-get update
      $COMMAND graphviz
      echo "Утилита Graphviz установлена."
    fi
    if [ "$OS_TYPE" == "MacOS" ]; then
      brew install graphviz
      echo "Утилита Graphviz установлена."
    fi
  else
    echo "Утилита Graphviz не будет установлена."
  fi
else
  echo "Утилита Graphviz уже установлена."
fi

# когда буду обновлять хелпер, сделать репку под мейк чек 