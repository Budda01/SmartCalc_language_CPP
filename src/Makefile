.PHONY: all clean test gcov_report clang

GCC = gcc -Wall -Werror -Wextra -std=c11

OS := $(shell uname -s)
TARGET= adelinan_s21_SmartCalc

ifeq ($(OS), Linux)
	LIB = -lcheck -lrt -lpthread -lsubunit -lm
	LEAK = valgrind --tool=memcheck --leak-check=yes
	OPEN = xdg-open
endif

ifeq ($(OS), Darwin)
	LIB = -lcheck
	OPEN = open
endif

all: test clean install

install:
	@echo INSTALLATION IN PROGRESS...
	@mkdir -p build
	@cd front/adelinan_s21_SmartCalc && qmake && sudo make install && mv $(TARGET) ../../build/$(TARGET) && make clean && rm -rf Makefile
	@cd ../..
	cp -R build/$(TARGET) ~/Desktop
	

uninstall:
	@rm -rf build
	@rm -rf ~/Desktop/$(TARGET)
	
test: clean
	@$(GCC) tests/*.c calculator/*.c $(LIB) -o s21_test
	@./s21_test

gcov_report : clean
	@$(GCC) calculator/*.c tests/*.c --coverage $(LIB) -o s21_test
	@./s21_test
	@mkdir ./report 
	@mv *.g* ./report
	@lcov -c -q -d ./report -o ./report/coverage.info
	@genhtml -q ./report/coverage.info -o ./report
	@$(OPEN) report/index.html

style: clean
	clang-format -style=Google -n s21_SmartCalc.h
	clang-format -style=Google -n tests/*.h tests/*.c
	clang-format -style=Google -n calculator/*.c
	clang-format -style=Google -n front/adelinan_s21_SmartCalc/*.cpp front/adelinan_s21_SmartCalc/*.h
clean :
	@rm -rf *.o *.a s21_calc s21_test *.gcda *.gcno coverage.info ./report tmp

leaks: test
	@$(LEAK) ./s21_test

