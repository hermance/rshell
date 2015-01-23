CFLAGS = -Wall -Werror -pedantic -ansi
all:bin
	g++ -o bin/rshell src/main.cpp
rshell:bin 
	g++ -o bin/rshell  src/main.cpp
bin:
	mkdir bin
