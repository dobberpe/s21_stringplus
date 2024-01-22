CC = gcc
CFLAGS = -Wall -Werror -Wextra 
TFLAGS = -lcheck -lsubunit -lm
LIB_NAME = s21_string.a
LIB_SRC = s21_string.c
LIB_OBJ = $(LIB_SRC:.c=.o)
TEST_SRC = string_test.c
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(LIB_NAME) test

test: $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. -l:s21_string.a $(TFLAGS)

gcov_r:
	gcc -o $(LIB_OBJ) -c -fprofile-arcs -ftest-coverage $(LIB_SRC)
	ar rcs $(LIB_NAME) $(LIB_OBJ)
	$(CC) $(CFLAGS) -o gcov_r -fprofile-arcs -ftest-coverage $(TEST_SRC) -L. -l:s21_string.a $(TFLAGS)




%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(LIB_OBJ)
	ar rcs $(LIB_NAME) $(LIB_OBJ)

clean:
	rm -f $(LIB_OBJ) $(LIB_NAME) $(TEST_OBJ) test

re: clean all