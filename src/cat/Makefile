GCC=gcc -Wall -Wextra -Werror

all:
	$(GCC) s21_cat.c delegates.c -o s21_cat

s21_cat:
	$(GCC) s21_cat.c delegates.c -o s21_cat

test:	
	sh test.sh > res.txt
clean:
	rm -rf 1 2 res.txt