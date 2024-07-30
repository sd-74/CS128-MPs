CXXFLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -pedantic -O0 -gdwarf-4
CXX=clang++

clean:
	rm -f bin/*

exec: ./src/driver.cc ./src/group.cc ./src/volunteer.cc ./includes/group.hpp ./includes/volunteer.hpp 
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/group.cc ./src/volunteer.cc -o bin/exec

tests: ./tests/tests.cc ./src/group.cc ./src/volunteer.cc ./includes/group.hpp ./includes/volunteer.hpp 
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/group.cc ./src/volunteer.cc -o bin/tests


src/%.cc: includes/%.hpp
	touch $@

.DEFAULT_GOAL := exec