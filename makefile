parser: lex.yy.o parser.tab.o expression.o command.o function.o
	g++ -Wall -o $@ $^

lex.yy.o: lex.yy.c
	g++ -Wall -c -o $@ $<

parser.tab.o: parser.tab.cpp
	g++ -Wall -c -o $@ $<

lex.yy.c: lexer.l parser.tab.hpp
	flex $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

expression.o: expression.cpp expression.hpp
	g++ -Wall -c -o $@ $<

command.o: command.cpp command.hpp
	g++ -Wall -c -o $@ $<

function.o: function.cpp function.hpp
	g++ -Wall -c -o $@ $<

.PHONY:
	clean

clean:
	-rm -f *~ *.o parser *output *.tab.hpp *.tab.cpp *.c