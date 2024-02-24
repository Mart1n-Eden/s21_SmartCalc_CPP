CXX := g++
CXX_FLAGS := -Wall -w -Wextra -std=c++17
GCOVFLAGS := -L. --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
 TEST_FLAGS := $(shell pkg-config --libs gtest)
else
 TEST_FLAGS := -lgtest
endif

LIB_SRC_MOD := $(wildcard Model/*.cc)
LIB_SRC_CON := $(wildcard Controller/*.cc)
LIB_SRC_VIE := $(wildcard View/*.cpp)
LIB_HDR_MOD := $(wildcard Model/*.h)
LIB_HDR_CON := $(wildcard Controller/*.h)
LIB_HDR_VIE := $(wildcard View/*.h)zz

ifeq ($(OS), Linux)
 MEM_CHECK := valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$(TESTS_BIN)
else
 MEM_CHECK := CK_FORK=no leaks --atExit -- ./$(TESTS_BIN)
endif

all: tests

tests: clean
	$(CXX) $(CXX_FLAGS) test.cc $(LIB_SRC_CON) $(LIB_SRC_MOD) -o test $(TEST_FLAGS)
	./test

install: uninstall
	mkdir build
	cd View/; cmake .; make;
	cp -R View/calc.app build/calc.app
	# chmod +rwx build
	# chmod +rwx build/calc.app
	# @chmod +rwx build
	# @chmod +rwx build/calc.app
	# open build/calc.app
	mv build ~/Desktop/

uninstall:
	rm -rf ~/Desktop/build

dist:
	rm -rf ../Archive/
	mkdir ../Archive/
	cp -r ../src ../Archive/
	tar -C ../ -czvf Archive.tgz Archive/
	mv Archive.tgz ~/Desktop/
	rm -rf ../Archive/

gcov_report: clean
	$(CXX) $(CXX_FLAGS) $(LIB_SRC_MOD) $(LIB_SRC_CON) test.cc $(TEST_FLAGS) $(GCOVFLAGS) -o $@
	./$@
	lcov -t $@ -o rep.info -c -d . --ignore-errors mismatch
	genhtml -o report rep.info
	open ./report/index.html

dvi:
	open dvi.html

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(LIB_SRC_MOD) $(LIB_SRC_CON) $(LIB_SRC_VIE) \
	$(LIB_HDR_MOD) $(LIB_HDR_CON) $(LIB_HDR_VIE) test.cc
	rm .clang-format

clean:
	rm -rf *.a *.o .clang-format test *.out gcov_report* *.info report *.gcno tests.out.dSYM
	rm -rf View/calc.app
	rm -rf View/calc_autogen
	rm -rf View/CMakeCache.txt
	# rm -rf View/CMakeLists.txt
	rm -rf View/CMakeFiles
	rm -rf View/Makefile
	rm -rf View/cmake_install.cmake
	rm -rf View/.qmake.stash
	rm -rf View/*.o
	rm -rf View/moc_*
	rm -rf View/.qtc_clangd
	rm -rf ~/Desktop/Archive.tgz
	rm -rf tests_sanitiz*
	rm -rf *.gcda
	rm -rf build