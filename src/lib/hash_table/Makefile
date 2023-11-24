FLAGS=--all-warnings --extra-warnings -Werror -Wpedantic -Wshadow -Wdiv-by-zero -Wcomment -Wdeprecated -Wdouble-promotion -Wconversion -Wdangling-else -Wnull-dereference -Wunused-variable -Wunused-value -Wformat-security
TEST_FLAGS=-lgtest -pthread -lgtest_main
t:
	g++ -g --std=c++20 $(FLAGS) t.cc  && ./a.out

test:
	g++ -g --std=c++20 $(FLAGS) tests.cc $(TEST_FLAGS)  && ./a.out

clean:
	rm -rf *.out