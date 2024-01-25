# Based on https://stackoverflow.com/a/52036564 which is well worth reading!

CXXFLAGS += -std=c++20 -W -fsanitize=address -static-libasan -O0 -Wall -Wno-unused-parameter -rdynamic -g -I include

SOURCES := $(wildcard src/*.cpp)
DEPENDENCIES := $(patsubst %.cpp,%.d,$(SOURCES))

OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
OBJECTS += src/c90_parser.tab.o src/c90_lexer.yy.o

CXX := g++

.PHONY: default

default: bin/c_compiler

src/c90_parser.tab.cpp src/c90_parser.tab.hpp : src/c90_parser.y
	bison -v -d src/c90_parser.y -o src/c90_parser.tab.cpp

src/c90_lexer.yy.cpp : src/c90_lexer.flex src/c90_parser.tab.hpp
	flex -o src/c90_lexer.yy.cpp src/c90_lexer.flex

bin/c_compiler : $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(DEPENDENCIES)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

with_coverage : CXXFLAGS += --coverage
with_coverage : bin/c_compiler

coverage : coverage/index.html

coverage/index.html :
	@mkdir -p coverage
# somehow lexer and parser coverage info are available but not accurate. To exclude them use:
# lcov -c --no-external --exclude "`pwd`/src/lexer.*" --exclude "`pwd`/src/parser.*" -d . -o coverage/cov.info
	lcov -c --no-external -d . -o coverage/cov.info
	genhtml coverage/cov.info -o coverage
	@find . -name "*.gcda" -delete

clean :
	@rm -rf coverage
	@find . -name "*.o" -delete
	@rm -rf bin/*
	@rm -rf $(OBJECTS) $(DEPENDENCIES)
	@rm -f src/c90_parser.output
	@rm -f src/c90_parser.tab.hpp
	@rm -f src/c90_parser.tab.cpp
	@rm -f src/c90_parser.tab.o
	@rm -f src/c90_parser.tab.gcno
	@rm -f src/c90_lexer.yy.cpp
	@rm -f src/c90_lexer.yy.o
	@rm -f src/c90_lexer.yy.gcno
