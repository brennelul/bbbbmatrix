FLAGS := -Wall -Werror -Wextra -std=c++17 -pedantic
GCOV_FLAGS := -fprofile-arcs -ftest-coverage 
CLANG_FLAGS := --style=Google --verbose
LIBCHECK := -lgtest -pthread
CPPFILES := library/matrix_oop.cpp tests/tests.cpp 
HPPFILES := library/header/matrix_oop.hpp
REPORT_DIR := /report/index.html


ifeq ($(shell uname -r | grep WSL -o), WSL)
	HTML_OPEN = @echo -e '\n'HTML report is here --\> $(shell pwd)$(REPORT_DIR)
else ifeq ($(shell uname -s), Linux)
	HTML_OPEN = @xdg-open .$(REPORT_DIR)
else
	HTML_OPEN = @open .$(REPORT_DIR)
	MACOS_GCOV_FLAGS = --ignore-errors inconsistent
endif

all: matrix_oop.a

check:
ifeq ("", $(shell which g++))
	$(error "Please install g++")
endif
test: style_check check matrix_oop.a
	g++ $(FLAGS) tests/tests.cpp matrix_oop.a -o test.out $(LIBCHECK)
	./test.out
gcov_report: check
ifeq ("", "$(shell which lcov)")
	$(error "Please install lcov")
endif
	@rm -rf report
	g++ $(FLAGS) $(GCOV_FLAGS) $(CPPFILES) -o gcov_report.out $(LIBCHECK) $(MACOS_GCOV_FLAGS)
	./gcov_report.out
	lcov -t matrix_oop -o matrix_oop.info -c -d . -q --no-external 
	genhtml -o report matrix_oop.info -q
	@rm -f *.info *.gcda *gcno gcov_report.out
	@rm -f *.o
	$(HTML_OPEN)
matrix_oop.a: check
	g++ $(FLAGS) $(LIBCHECK) -c -o matrix_oop.o library/matrix_oop.cpp 
	ar rcs matrix_oop.a matrix_oop.o
	@rm -f *.o
clean:
	rm -f *.a *.o *.info *.gcda *.gcno *.out
	rm -rf report
rebuild: clean all

style_check:
	clang-format -n $(CLANG_FLAGS) $(CPPFILES)
style_fix:
	clang-format -i $(CLANG_FLAGS) $(CPPFILES) $(HPPFILES)
cpplint:
	cpplint $(CPPFILES) $(HPPFILES)

valgrind: clean test
	valgrind --tool=memcheck --leak-check=yes ./test.out
