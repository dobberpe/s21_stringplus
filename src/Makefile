CC = gcc
CFLAGS = -Wall -Werror -Wextra 
TFLAGS = -lcheck -lsubunit -lm
GFLAGS = -fprofile-arcs -ftest-coverage
LIB_NAME = s21_string.a
LIB_SRC = s21_string.c
LIB_OBJ = $(LIB_SRC:.c=.o)
TEST_SRC = $(wildcard ./tests/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(LIB_NAME) test

test: $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. -l:$(LIB_NAME) $(TFLAGS)
	rm -f $(TEST_OBJ)
	./test


gcov_report: clean
	gcc -o $(LIB_OBJ) -c $(GFLAGS) $(LIB_SRC)
	ar rcs $(LIB_NAME) $(LIB_OBJ)
	ranlib $(LIB_NAME)
	rm -f $(LIB_OBJ)
	$(CC) $(CFLAGS) -o gcov_r $(GFLAGS) $(TEST_SRC) -L. -l:$(LIB_NAME) $(TFLAGS)
	./gcov_r
	geninfo s21_string.gcda $(LIB_SRC) -o ./coverage.info
	genhtml coverage.info -o coverage_report
	open coverage_report/index.html


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(LIB_OBJ)
	ar rcs $(LIB_NAME) $(LIB_OBJ)
	ranlib $(LIB_NAME)
	rm -f $(LIB_OBJ)

clean:
	rm -f $(LIB_OBJ) $(LIB_NAME) $(TEST_OBJ) test gcov* coverage.info s21_string.c_pro* s21_string.g* coverage_report.html s21_string.c.gcov
	rm -rf coverage_report

re: clean all