CC = g++ -std=c++17 -Wall -Werror -Wextra -lstdc++ 
LIBS = -lgtest -pthread
GCOV = --coverage
TARGET = adelinan_s21_SmartCalc

all: clean uninstall install

install: 
	@mkdir -p build
	cd View && qmake && make && make clean
	mv View/$(TARGET) iew/$(TARGET).app  
	mv view/$(TARGET).app ../build/

open:
	cd ~/apps && ./s21_calc_kidneyha.app

uninstall:
	@rm -rf ~/apps/$(TARGET).app ../build

dvi: 
	@xdg-open README.md

dist: install
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app

tests: clean
	@$(CC) $(SRC) -o test.out $(LIBS) 
	@./test.out

gcov_report: clean
	@$(CC) $(GCOV) $(SRC) -o test.out $(LIBS) 
	@./test.out
	@lcov -t "test" -o test.info -c -d . 
	@genhtml -o report test.info 
	@open ./report/index.html
	@make clean_test

style:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n ./*/*.cc ./*/*.h
	@rm -rf .clang-format

clean: clean_test
	cd View/ && rm -rf *.o *.a s21_calc s21_test *.gcda *.gcno coverage.info ./report tmp
	rm -rf build/

clean_test:
	@rm -rf *.gcda *.gcno test.out test *.info
