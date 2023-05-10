all: clean test

test:
	g++ -Wall -Wextra -Werror -std=c++17 -lgtest test.cc -o test
	./test

clean:
	@rm -rf test

leaks: test
	CK_FORK=no leaks -atExit -- ./test


