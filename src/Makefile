CC = gcc
CFLAGS =
TFLAGS = -lcheck -lsubunit -lm
GFLAGS = -fprofile-arcs -ftest-coverage
LIB_NAME = s21_string.a
LIB_SRC = s21_string.c s21_sprintf.c
LIB_OBJ = $(LIB_SRC:.c=.o)
TEST_SRC = $(wildcard ./tests/*.c)
TEST_GCDA = $(LIB_SRC:.c=.gcda)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(LIB_NAME) test

test: $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. -l:$(LIB_NAME) $(TFLAGS)
	rm -f $(TEST_OBJ)
	./test


gcov_report: clean
	@command -v lcov >/dev/null 2>&1 || { echo >&2 "Error: lcov not found. Please install lcov."; exit 1; }
	gcc -o s21_string.o -c $(GFLAGS) s21_string.c
	gcc -o s21_sprintf.o -c $(GFLAGS) s21_sprintf.c
	ar rcs $(LIB_NAME) $(LIB_OBJ)
	ranlib $(LIB_NAME)
	rm -f $(LIB_OBJ)
	$(CC) $(CFLAGS) -o gcov_r $(GFLAGS) $(TEST_SRC) -L. -l:$(LIB_NAME) $(TFLAGS)
	./gcov_r
	geninfo $(TEST_GCDA) $(LIB_SRC) -o ./coverage.info
	genhtml coverage.info -o coverage_report
	rm -rf gcov_r* coverage.info *.gcda *.gcno tests/*.gcno
	open coverage_report/index.html
	endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(LIB_OBJ)
	ar rcs $(LIB_NAME) $(LIB_OBJ)
	ranlib $(LIB_NAME)
	rm -f $(LIB_OBJ)

clean:
	rm -f $(LIB_OBJ) $(LIB_NAME) $(TEST_OBJ) test gcov* coverage.info *.gcda *.gcno tests/*.gcno
	rm -rf coverage_report

re: clean all