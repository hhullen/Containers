MAIN_PROJ_NAME=Containers
# FUNCS= \
	lib$(SEP)hash_table$(SEP)*.cc \
	lib$(SEP)binary_tree$(SEP)*.cc
TEST_C=$(FUNCS) tests$(SEP)$(MAIN_PROJ_NAME)_tests.cc
EXECUTABLE=$(MAIN_PROJ_NAME)_tests.out
COMPILER=g++
STD=--std=c++17
CPP_FLAGS=-Werror -Wpedantic -Wshadow \
		  -Wconversion -Wdangling-else -Wnull-dereference -Wsign-conversion  \
		  --all-warnings --extra-warnings -Wdiv-by-zero -Wcomment -Wdeprecated \
		  -Winline -Wunused-variable -Wunused-value -Wformat-security  -Wdouble-promotion
TEST_FLAGS=-lgtest -pthread -lgtest_main
GCOV_FLAG=--coverage
EXTENSION=--extensions=cc
CLANG_FILE=.clang-format
CLANG_FILE_WAY=..$(SEP)materials$(SEP)linters$(SEP)$(CLANG_FILE)
CHECK_FILES= \
	lib$(SEP)*.h \
	$(FUNCS:.cc.h) \
	lib$(SEP)binary_tree$(SEP)*.cc \
	lib$(SEP)hash_table$(SEP)*.cc \
	$(FUNCS)
CPPCH_SETUP=--enable=warning,performance,portability  -v --language=c++ $(STD)
VALGRIND_SETUP=--tool=memcheck --leak-check=full --show-leak-kinds=all
TO_DELETE_FILES=*.o *.a *.out *.dSYM *.gch *.gcda *.gcno .DS_Store $(EXECUTABLE) \
				$(CLANG_FILE) *.info matrix_output.txt
TO_DELETE_FOLDERS=$(BUILD_DIR) report *.dSYM $(MAIN_PROJ_NAME)


#Crossplatform specs
SEP='\'
MAKEDIR=md
DELETE_FOLDER=RD /S/Q
DELETE_FILE=DEL /F
COPY=copy
OPEN=start
OS=$(shell uname)

ifeq ($(OS), Linux)
	OPEN=xdg-open
	MAKEDIR=mkdir -p
	SEP=/
	DELETE_FOLDER=rm -rf
	DELETE_FILE=rm -f
	COPY=cp
endif

ifeq ($(OS), Darwin)
	OPEN=open
	MAKEDIR=mkdir -p
	SEP=/
	DELETE_FOLDER=rm -rf
	DELETE_FILE=rm -f
	COPY=cp
endif

.PHONY: check lib tests clean valgrind leaks

all: check $(MAIN_PROJ_NAME).a tests

check:
	cppcheck $(CPPCH_SETUP) $(CHECK_FILES)
	$(COPY) $(CLANG_FILE_WAY) $(CLANG_FILE)
	clang-format -i --style=Google $(CHECK_FILES)
	clang-format -n --style=Google $(CHECK_FILES)

clean:
	$(DELETE_FOLDER) $(TO_DELETE_FOLDERS)
	$(DELETE_FILE) $(TO_DELETE_FILES)

tests: clean
	$(COMPILER) -g $(STD) $(CPP_FLAGS) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS) -I .
	.$(SEP)$(EXECUTABLE)

$(MAIN_PROJ_NAME).a:
	$(COMPILER) $(STD) -O3 -c $(FUNCS)
	ar rc lib$(MAIN_PROJ_NAME).a $(MAIN_PROJ_NAME).o

lib:
	$(MAKEDIR) $(MAIN_PROJ_NAME)
	$(COPY) lib$(SEP)* $(MAIN_PROJ_NAME)

valgrind: clean
	$(COMPILER) -g $(STD) $(CPP_FLAGS) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS) -I .
	CK_FORK=no valgrind $(VALGRIND_SETUP) .$(SEP)$(EXECUTABLE)

leaks: tests
	leaks -atExit -- .$(SEP)$(EXECUTABLE)
