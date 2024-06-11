CC=g++
CFLAGS=-std=c++17 -g -Wall -Wextra -Werror
GTEST_FLAGS=-lgtest -lgtest_main -pthread

SRC_FILES=$(wildcard */*.cc) $(wildcard */*/*.cc)
OBJ_FILES=$(SRC_FILES:.cc=.o)
TEST_EXEC=test

RBTree=RBTree/RedBlackTree.cc

all: $(TEST_EXEC)

$(TEST_EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TEST_EXEC) $(GTEST_FLAGS)
	./$(TEST_EXEC)

$(OBJ_FILES): %.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clang-check:
	cp ../materials/linters/.clang-format .
	clang-format -n */*.cc */*.h
	rm ./.clang-format

clang-formatting:
	cp ../materials/linters/.clang-format .
	clang-format -i */*.cc */*.h
	rm ./.clang-format

gcov_report: test
	$(CC) --coverage $(CFLAGS) Tests/*.cc $(RBTree) -o $^ $(GTEST_FLAGS)
	./$^
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info 
	$(OPEN_REPORT) report/index.html

clean:
	find . -name '*.gcda' -type f -delete
	find . -name '*.gcno' -type f -delete
	find . -name '*.info' -type f -delete
	rm -rf $(OBJ_FILES) $(TEST_EXEC) report

rebuild: clean all
