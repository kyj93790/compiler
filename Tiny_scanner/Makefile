CC = gcc
TARGET = hw2_binary

all : $(TARGET)

$(TARGET) :
	bison -d yacc/tiny.y --yacc
	lex tiny.l
	$(CC) -c lex.yy.c
	$(CC) -c y.tab.c
	$(CC) -c main.c
	$(CC) -c util.c
	$(CC) -g -o $@ y.tab.o main.o util.o lex.yy.o -ll

clean :
	rm -f *.o
	rm -f lex.yy.*
	rm -f y.tab.*
	rm -f *_20191574.txt
	rm -f $(TARGET)