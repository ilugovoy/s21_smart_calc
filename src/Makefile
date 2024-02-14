# #------------> Опции компилятора
FLAGS_MACOS = -L $(shell brew --prefix)/lib -lcheck
SLFLAGS = -lcheck -lsubunit 
MACOS_FLAG = 0
LEAK_TEST_TOOL = valgrind

# флаги специальных библиотек для сборки на макос
ifeq ($(shell uname), Darwin)
SLFLAGS = $(FLAGS_MACOS)
LEAK_TEST_TOOL = leak
endif

CC=gcc # компилятор
LFLAGS=-g # для сборки с отладочной информацией
LIBFLAGS=-lm # для линковки c математической либой
# LIBFLAGS = -lpthread -pthread -lrt -lm
CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic # для обработки ошибок
GCOVFLAGS=--coverage -fprofile-arcs -ftest-coverage # для анализа покрытия

# указывает флаги для сборки на маке с камнем M1
ifeq ($(shell uname -m), arm64)
CFLAGS := $(filter-out -pedantic,$(CFLAGS))
CFLAGS += -arch arm64
endif

# указывает флаги для сборки на маке с камнем M2
ifeq ($(shell uname -m), arm64e)
CFLAGS := $(filter-out -pedantic,$(CFLAGS))
endif

# #------------> Адреса, пути и цели для сборки программы
BUILD_SOURCES=$(shell find functions -maxdepth 2 -name '*.c') # Папки для сборки библиотеки
TEST_SOURCES=$(shell find tests -maxdepth 2 -name '*.c') # Папки для тестирования библиотечных функций
DIST_SOURCES=../src # Ресурсы для сборки дистрибутива
INSTALL_DIR=calculator# Папка с программой


all: clean rebuild

rebuild: basic_build
# rebuild: full_check_build

basic_build: check install open_app test gcov_report dvi open_report # стандартный набор целей для GNU-программ: all, clean, install, test, gcov_report, dvi, uninstall, dist
full_check_build: style check dist install open_app test gcov_report dvi open_report cpp leak_test # для сборки с проверкой зависимотей и тестами на стиль, утечки и cppcheck 
# uninstall clean

# #---> основные цели
s21_calc_v1.a: 
	$(CC) -c  $(CFLAGS) $(LFLAGS) $(BUILD_SOURCES)
	ar rc s21_calc_v1.a *.o

install: s21_calc_v1.a
	mkdir -p $(INSTALL_DIR)
	cd $(INSTALL_DIR) && qmake ../../src/gui_qt_sources/s21_smart_calc.pro && make
# make open_app

open_app:
	$(INSTALL_DIR)/s21_smart_calc

dist:
	@rm -rf s21_calc_v1.tar
	@cd .. && mkdir -p dist
	@cd .. && cp -r src dist && cp README.md dist
	@cd .. && mv dist src 
	@tar -zcf s21_calc_v1.tar dist 
	@rm -rf dist
	@echo "Архив с дистрибутивом программы создан в папке src/s21_calc_v1.tar"
# tar -xzf s21_calc_v1.tar - распакует содержимое архива в текущую папку

uninstall:
	rm -rf $(INSTALL_DIR)

dvi:
	@doxygen dvi_sources/Doxyfile > /dev/null 2>&1
# @open dvi_sources/dvi_report/index.html
# @google-chrome dvi_sources/dvi_report/index.html > /dev/null 2>&1


# #---> тестирование и отчёт о покрытии
test:
	$(CC) $(CFLAGS) $(LFLAGS) $(TEST_SOURCES) $(BUILD_SOURCES) s21_calc_v1.a $(SLFLAGS) $(LIBFLAGS) -o test -g
	@./test

gcov_report:
	$(CC) $(CFLAGS) $(LFLAGS) $(TEST_SOURCES) $(BUILD_SOURCES) s21_calc_v1.a $(SLFLAGS) $(LIBFLAGS) -o s21_gcov $(GCOVFLAGS)
	@./s21_gcov
	@lcov -t "gcov_report" -o s21_gcov_report.info -c -d .
	@lcov -r s21_gcov_report.info '*/tests/*' -o s21_gcov_report.info
	@genhtml -o s21_report s21_gcov_report.info
# @google-chrome s21_report/index.html 2> /dev/null
# @open s21_report/index.html

open_report:
# @google-chrome s21_report/index.html > /dev/null 2>&1
# @google-chrome dvi_sources/dvi_report/index.html > /dev/null 2>&1 
	@open dvi_sources/dvi_report/index.html > /dev/null 2>&1
	@open s21_report/index.html > /dev/null 2>&1


# #---> очистка
clean: clean_obj clean_s21_report clean_dvi_report
	rm -rf *.so *.out report *.info *.txt *.cmake test *.gch *.pdf s21_gcov *.gcno *.gcda  
	rm -rf  *.html *.css 
# *.tar

clean_obj:    
	rm -f *.a
	rm -f *.o

clean_s21_report:
	rm -rf report s21_report

clean_dvi_report:
	rm -rf dvi_sources/dvi_report


# #---> дополнительные проверки
leak_test:
	@make $(LEAK_TEST_TOOL)

valgrind:
	@valgrind  --leak-check=full --track-origins=yes ./test

leak:
	@CK_FORK=no leaks --atExit -- ./test 

cpp:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(TEST_SOURCES)*.c *.h $(BUILD_SOURCES)*.c *.h
	@cppcheck --enable=all --suppress=missingIncludeSystem --check-config gui_qt_sources *.cpp *.h

style:
	@cd assets/scripts && bash ./style_test.sh || (echo "Style tests failed")

check:    
	@cd assets/scripts && bash ./install_brew.sh || (echo "install_brew.sh failed")
	@cd assets/scripts && bash ./check_dependencies.sh || (echo "check_dependencies.sh failed")


# #--->  исключения для аналогичных имён файлов 
.PHONY: make clean cppcheck style memcheck test gcov_report open_report cpp valgrind tar dist dvi install uninstall build rebuild leak
