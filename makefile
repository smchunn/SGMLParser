
all : sgmlparser
	./sgmlParser

sgmlparser : sgmlParser.c sgmlParser.h
	gcc -Wall -O2 -fwrapv -Wfloat-equal -std=c17 sgmlParser.c -o sgmlParser

run : sgmlparser
	./sgmlParser

clean :
	rm -f sgmlParser
