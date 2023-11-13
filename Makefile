CPPFLAGS += -std=c++20 -W -fsanitize=address -static-libasan -O0 -Wall -Wno-unused-parameter -g -I include

.PHONY: default

default: bin/c_compiler

src/c90_parser.tab.cpp src/c90_parser.tab.hpp : src/c90_parser.y
	bison -v -d src/c90_parser.y -o src/c90_parser.tab.cpp

src/c90_lexer.yy.cpp : src/c90_lexer.flex src/c90_parser.tab.hpp
	flex -o src/c90_lexer.yy.cpp src/c90_lexer.flex

bin/c_compiler : src/cli.cpp src/compiler.cpp src/c90_parser.tab.o src/c90_lexer.yy.o src/c90_parser.tab.o
	@mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_compiler $^

clean :
	rm -rf bin/*
	rm -f src/c90_parser.output
	rm -f src/c90_parser.tab.hpp
	rm -f src/c90_parser.tab.cpp
	rm -f src/c90_parser.tab.o
	rm -f src/c90_lexer.yy.cpp
	rm -f src/c90_lexer.yy.o
