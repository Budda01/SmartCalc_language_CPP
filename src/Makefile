.PHONY: all clean tests gcov_report style install uninstall dvi dist

CC = g++ -std=c++17 -Wall -Werror -Wextra -lstdc++ 
LIBS = -lgtest -pthread
GCOV = --coverage
TARGET = adelinan_s21_SmartCalc
INSTALL_DIR = ~/Desktop
SRC = ./Model/calculation.cc ./Model/parsing.cc ./Model/credit_calc.cc
DIST_DIR = ./dist
UNAME_S := $(shell uname -s)


ifeq ($(UNAME_S),Linux)
    OPEN_CMD = xdg-open
else ifeq ($(UNAME_S),Darwin)
    OPEN_CMD = open
endif

all: clean uninstall install

install:
	@echo INSTALLATION IN PROGRESS...
	@mkdir -p build
	@cd View && qmake && sudo make install && mv $(TARGET) ../build/$(TARGET) && make clean && rm -rf Makefile
	@cd ../..
	@cp -R build/$(TARGET) $(INSTALL_DIR)
	@echo INSTALLATION SUCCESSFUL

uninstall:
	@rm -rf build
	@rm -rf $(INSTALL_DIR)/$(TARGET)

tests: clean
	$(CC) ./tests/test.cc $(SRC) -o test.out $(LIBS)
	@./test.out

style:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n ./*/*.cc ./*/*.h
	@rm -rf .clang-format

clean: clean_test
	@rm -rf $(DIST_DIR)
	@rm -rf *.o ./*.a report tmp $(TARGET)

clean_test:
	@rm -rf *.gcda *.gcno test.out test *.info

dvi:
	@$(OPEN_CMD) README.md

dist: install
	@mkdir -p $(DIST_DIR)
	@cp -R build/$(TARGET) $(DIST_DIR)
	@cd $(DIST_DIR) && tar cvzf $(TARGET).tgz $(TARGET)
	@rm -rf $(DIST_DIR)/$(TARGET)

gcov_report: clean 
	$(CC) $(GCOV) tests/test.cc $(SRC) -o test.out $(LIBS)
	@./test.out
	@lcov -t "test" -o test.info -c -d . --include "$(PWD)/Model/calculation.cc" --include "$(PWD)/Model/credit_calc.cc" --include "$(PWD)/Model/parsing.cc"
	@genhtml -o report test.info
	@$(OPEN_CMD) ./report/index.html
	@make clean_test

