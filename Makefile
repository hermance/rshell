CFLAGS = -Wall -Werror -pedantic -ansi
all:bin
	g++ -o bin/rshell src/main.cpp
rshell:bin 
	g++ -o bin/rshell  src/main.cpp
ls:bin
	g++ -o bin/ls src/ls.cpp
bin:
	mkdir bin
