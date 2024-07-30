CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -O0
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -Wno-error=unused-parameter

exec: bin/exec
tests: bin/tests

bin/exec : ./includes/utilities.hpp ./src/utilities.cc ./includes/illini_book.hpp ./src/illini_book.cc ./src/driver.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./src/utilities.cc ./src/illini_book.cc ./src/driver.cc -o ./bin/exec

obj/catch_main.o: ./tests/catch_main.cc
	$(CXX) $(CXX_FLAGS) -c ./tests/catch_main.cc -o $@

bin/tests : ./includes/utilities.hpp ./src/utilities.cc ./includes/illini_book.hpp ./src/illini_book.cc ./tests/tests.cc ./obj/catch_main.o
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./obj/catch_main.o ./src/utilities.cc ./src/illini_book.cc ./tests/tests.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
