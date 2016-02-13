all: bin/rshell 

rshell: bin/rshell

bin/rshell: ./src/rshell.cpp | bin
	g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp -o ./bin/rshell
	
bin:
	mkdir bin

