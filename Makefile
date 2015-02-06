CFLAGS = -Wall -Werror -pedantic -ansi
all:bin ls
	g++ -o bin/rshell src/main.cpp
rshell:bin 
	g++ -o bin/rshell  src/main.cpp
ls:
	g++ -o bin/ls src/ls.cpp
bin:
	mkdir bin
