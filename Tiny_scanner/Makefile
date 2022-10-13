CC = gcc
TARGET = hw1_20191574

all : $(TARGET)

$(TARGET) :
	$(CC) -c main.c
	$(CC) -c util.c
	lex tiny.l
	$(CC) -c lex.yy.c
	$(CC) -g -o $@ main.o util.o lex.yy.o -ll

clean :
	rm -f *.o
	rm -f $(TARGET)